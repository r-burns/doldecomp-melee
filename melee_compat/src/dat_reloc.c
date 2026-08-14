// Relocating DAT loader.
//
// A DAT archive is a raw GameCube memory image. Reading it with host structs
// breaks shit
//
//   * endianness
//   * field offsets (4-byte pointers shift everything after them)
//   * struct size  (so array indexing has the wrong stride)
//
// to convert it, we walk it field by field using the
// generated GameCube/host layout tables, byte-swap each scalar, and rebuild it
// at host offsets in freshly allocated memory.
//
// Pointer fields are followed and converted recursively. Results are memoised
// on (GameCube address, type), which both preserves sharing, two DObjs
// referencing one MObj still share it afterwards, and terminates the cycles
// that HSD scene graphs are full of.
//
// The layout tables come from tools/gen_dat_layouts.py, which extracts both
// ABIs from the real headers with clang. They are never hand-maintained.
//
// NOTE: pointers to types with no descriptor (char*, and the raw vertex/index
// blobs) are widened in place rather than converted. That is correct -- the
// pointee has no struct layout to fix, but it only works because MEM1 is
// mapped in the low 2GB, so a 32-bit DAT pointer is already a valid host
// address. See AllocMEM1 in the aurora patch.

#include "compat_report.h"

#include <string.h>

#include <melee_pc_dat_types.h>
#include <melee_pc_gx.h>

// The converter uses more memory than was available on the GC, so we have to use the
// normal memory allocator for this
void* malloc(size_t size);
void free(void* p);

#define ARENA_CHUNK (1u << 20)

typedef struct ArenaChunk {
    struct ArenaChunk* next;
    size_t used;
    size_t cap;
    u8 data[1];
} ArenaChunk;

static ArenaChunk* arena;

static void* arena_alloc(size_t size)
{
    ArenaChunk* c;

    size = (size + 15) & ~(size_t) 15;

    if (arena == NULL || arena->used + size > arena->cap) {
        size_t cap = size > ARENA_CHUNK ? size : ARENA_CHUNK;
        c = malloc(sizeof(ArenaChunk) + cap);
        if (c == NULL) {
            return NULL;
        }
        c->next = arena;
        c->used = 0;
        c->cap = cap;
        arena = c;
    }

    c = arena;
    {
        void* p = c->data + c->used;
        c->used += size;
        return p;
    }
}

static void arena_free_all(void)
{
    while (arena != NULL) {
        ArenaChunk* next = arena->next;
        free(arena);
        arena = next;
    }
}

typedef enum {
    DAT_END,
    DAT_U8,
    DAT_U16,
    DAT_U32,
    DAT_U64,
    DAT_PTR,
    // Pointer to an array of structs, terminated when the element field at
    // aux equals aux2.
    DAT_ARR_SENTINEL,
    // Pointer to an array of structs; length is the field at gc offset aux,
    // which is aux2 bytes wide.
    DAT_ARR_COUNT,
    // As above, but an array of pointers rather than of structs.
    DAT_ARR_PTRCOUNT,
    // Pointer to a NULL-terminated array of pointers. We need to keep the terminator
    // otherwise melee will hang!!
    DAT_ARR_PTRNULL,
    // Several fields share this offset. Only the discriminant says which is
    // live, and that is type-specific game logic, so a hand-written converter
    // is needed, see dat_union_hooks.
    DAT_UNION,
} DatKind;

typedef struct DatField {
    u16 gc_off;
    u16 host_off;
    u8 kind;
    s8 type; // DatTypeId of the value pointed to, or DAT_T_NONE
    u16 aux;
    u16 aux2;
} DatField;

typedef struct DatType {
    const char* name;
    u16 gc_size;
    u16 host_size;
    const DatField* fields;
    u8 has_union;
} DatType;

// Fills in the union arms of one structure. Returning false means "I do not
// know which arm is live", which is a panic rather than a guess.
typedef bool (*DatUnionHook)(const u8* gc, u8* host);

#include "dat_layouts.inc"

// --- memo table -----------------------------------------------------------
//
// Open addressing. Sized generously and never grown: a scene's descriptor
// graph is thousands of nodes, not millions, and running out is a loud failure
// rather than a silent wrong answer.

#define MEMO_CAP 65536 // power of two

typedef struct {
    const void* gc;
    void* host;
    int type;
} MemoEntry;

static MemoEntry memo[MEMO_CAP];
static u32 memo_count;

static u32 memo_hash(const void* gc, int type)
{
    uintptr_t h = (uintptr_t) gc;
    h ^= (uintptr_t) type * 0x9E3779B1u;
    h ^= h >> 16;
    return (u32) h & (MEMO_CAP - 1);
}

static void** memo_slot(const void* gc, int type)
{
    u32 i = memo_hash(gc, type);
    u32 probes = 0;

    for (;;) {
        if (memo[i].gc == NULL) {
            if (++memo_count > MEMO_CAP / 2) {
                OSPanic(__FILE__, __LINE__,
                        "melee_pc: DAT memo table full (%u entries)",
                        memo_count);
            }
            memo[i].gc = gc;
            memo[i].type = type;
            return &memo[i].host;
        }
        if (memo[i].gc == gc && memo[i].type == type) {
            return &memo[i].host;
        }
        i = (i + 1) & (MEMO_CAP - 1);
        if (++probes >= MEMO_CAP) {
            OSPanic(__FILE__, __LINE__, "melee_pc: DAT memo table wedged");
        }
    }
}

// --- big-endian scalar reads ----------------------------------------------

static u16 rd16(const void* p)
{
    u16 v;
    memcpy(&v, p, sizeof(v));
    return __builtin_bswap16(v);
}

static u32 rd32(const void* p)
{
    u32 v;
    memcpy(&v, p, sizeof(v));
    return __builtin_bswap32(v);
}

static u64 rd64(const void* p)
{
    u64 v;
    memcpy(&v, p, sizeof(v));
    return __builtin_bswap64(v);
}

// --- conversion -----------------------------------------------------------

void* melee_pc_dat_convert(const void* gc, int type);
static void convert_fields(const u8* gc, u8* host, const DatType* ty);
static const DatUnionHook dat_union_hooks[DAT_T_COUNT];

// Reads a scalar of the width the descriptor gives that field.
static u32 read_scalar(const u8* p, u8 kind)
{
    switch (kind) {
    case DAT_U8:
        return *p;
    case DAT_U16:
        return rd16(p);
    default:
        return rd32(p);
    }
}

// The width of a field, looked up in its own type's descriptor -- so a
// sentinel tag is read as whatever the header says it is, with no second
// source of truth to drift.
static u8 kind_at(const DatType* ty, u16 gc_off)
{
    const DatField* f;
    for (f = ty->fields; f->kind != DAT_END; f++) {
        if (f->gc_off == gc_off) {
            return f->kind;
        }
    }
    return DAT_U32;
}

// Converts `count` consecutive elements. The host array is strided by *host*
// size, which is the whole reason indexing was wrong before.
static void* convert_array(const u8* gc, int type, u32 count)
{
    const DatType* ty = &dat_types[type];
    void** slot;
    u8* host;
    u32 i;

    if (count == 0) {
        return NULL;
    }

    // Keyed separately from the single-struct conversion of the same address:
    // one element is not the same object as the array starting there.
    slot = memo_slot(gc, type | 0x100);
    if (*slot != NULL) {
        return *slot;
    }

    host = arena_alloc((size_t) count * ty->host_size);
    if (host == NULL) {
        OSPanic(__FILE__, __LINE__, "melee_pc: out of memory converting %s[%u]",
                ty->name, count);
    }
    memset(host, 0, (size_t) count * ty->host_size);
    *slot = host;

    for (i = 0; i < count; i++) {
        convert_fields(gc + (size_t) i * ty->gc_size,
                       host + (size_t) i * ty->host_size, ty);
    }
    return host;
}

static void convert_fields(const u8* gc, u8* host, const DatType* ty)
{
    const DatField* f;

    for (f = ty->fields; f->kind != DAT_END; f++) {
        const u8* src = gc + f->gc_off;
        u8* dst = host + f->host_off;

        switch (f->kind) {
        case DAT_U8:
            *dst = *src;
            break;
        case DAT_U16: {
            u16 v = rd16(src);
            memcpy(dst, &v, sizeof(v));
            break;
        }
        case DAT_U32: {
            // Also covers f32 and enums: swapping the 32 bits is right
            // regardless of how they are interpreted.
            u32 v = rd32(src);
            memcpy(dst, &v, sizeof(v));
            break;
        }
        case DAT_U64: {
            u64 v = rd64(src);
            memcpy(dst, &v, sizeof(v));
            break;
        }
        case DAT_PTR: {
            u32 gcptr = rd32(src);
            void* p;
            if (gcptr == 0) {
                p = NULL;
            } else if (f->type == DAT_T_NONE) {
                // No descriptor: nothing to relayout, so the address stands.
                p = (void*) (uintptr_t) gcptr;
            } else {
                p = melee_pc_dat_convert((const void*) (uintptr_t) gcptr,
                                         f->type);
            }
            memcpy(dst, &p, sizeof(p));
            break;
        }
        case DAT_ARR_SENTINEL: {
            u32 gcptr = rd32(src);
            const DatType* et = &dat_types[f->type];
            u8 tagk = kind_at(et, f->aux);
            const u8* e = (const u8*) (uintptr_t) gcptr;
            u32 n = 0;
            void* p;
            if (gcptr != 0) {
                while (read_scalar(e + n * et->gc_size + f->aux, tagk) !=
                       f->aux2) {
                    n++;
                }
                // The terminator element is copied too: callers walk up to and
                // including it, and stop on the tag themselves.
                n++;
            }
            p = gcptr ? convert_array(e, f->type, n) : NULL;
            memcpy(dst, &p, sizeof(p));
            break;
        }
        case DAT_ARR_COUNT: {
            u32 gcptr = rd32(src);
            u32 n = read_scalar(gc + f->aux, f->aux2 == 2 ? DAT_U16 : DAT_U32);
            void* p = gcptr ? convert_array((const u8*) (uintptr_t) gcptr,
                                            f->type, n)
                            : NULL;
            memcpy(dst, &p, sizeof(p));
            break;
        }
        case DAT_ARR_PTRNULL: {
            u32 gcptr = rd32(src);
            void** p = NULL;
            if (gcptr != 0) {
                const u8* tbl = (const u8*) (uintptr_t) gcptr;
                u32 n = 0;
                u32 i;
                while (rd32(tbl + n * 4) != 0) {
                    n++;
                }
                // One extra slot, left NULL: the game's loops stop on it.
                p = arena_alloc((size_t) (n + 1) * sizeof(void*));
                if (p == NULL) {
                    OSPanic(__FILE__, __LINE__,
                            "melee_pc: out of memory converting %s[]",
                            dat_types[f->type].name);
                }
                for (i = 0; i < n; i++) {
                    p[i] = melee_pc_dat_convert(
                        (const void*) (uintptr_t) rd32(tbl + i * 4), f->type);
                }
                p[n] = NULL;
            }
            memcpy(dst, &p, sizeof(p));
            break;
        }
        case DAT_ARR_PTRCOUNT: {
            u32 gcptr = rd32(src);
            u32 n = read_scalar(gc + f->aux, f->aux2 == 2 ? DAT_U16 : DAT_U32);
            void** p = NULL;
            if (gcptr != 0 && n != 0) {
                const u8* tbl = (const u8*) (uintptr_t) gcptr;
                u32 i;
                p = arena_alloc((size_t) n * sizeof(void*));
                if (p == NULL) {
                    OSPanic(__FILE__, __LINE__,
                            "melee_pc: out of memory converting pointer table");
                }
                for (i = 0; i < n; i++) {
                    u32 ep = rd32(tbl + i * 4);
                    p[i] = ep ? melee_pc_dat_convert(
                                    (const void*) (uintptr_t) ep, f->type)
                              : NULL;
                }
            }
            memcpy(dst, &p, sizeof(p));
            break;
        }
        case DAT_UNION:
            // Handled by the type's hook, after the plain fields are in place
            // so the discriminant is readable.
            break;
        default:
            break;
        }
    }
}

void* melee_pc_dat_convert(const void* gc, int type)
{
    const DatType* ty;
    void** slot;
    void* host;

    if (gc == NULL) {
        return NULL;
    }

    // Everything inside an archive points within the archive, so a "pointer"
    // that does not land in MEM1 is not one: either the field is a union arm
    // that is not live, or the descriptor does not match this data.
    if (!melee_pc_in_mem1(gc)) {
        static int reported;
        if (reported < 20) {
            reported++;
            OSReport("melee_pc: DAT %s: pointer %p is outside MEM1, not "
                     "following it\n",
                     dat_types[type].name, gc);
        }
        return NULL;
    }
    if (type < 0 || type >= DAT_T_COUNT) {
        OSPanic(__FILE__, __LINE__, "melee_pc: bad DAT type id %d", type);
    }

    slot = memo_slot(gc, type);
    if (*slot != NULL) {
        return *slot;
    }

    ty = &dat_types[type];
    host = arena_alloc(ty->host_size);
    if (host == NULL) {
        OSPanic(__FILE__, __LINE__, "melee_pc: out of memory converting %s",
                ty->name);
    }
    memset(host, 0, ty->host_size);

    // Published before recursing, so a cycle back to this node resolves to the
    // (still being filled in) host copy rather than looping forever.
    *slot = host;

    convert_fields(gc, host, ty);

    if (ty->has_union) {
        DatUnionHook hook = dat_union_hooks[type];
        if (hook == NULL || !hook(gc, host)) {
            OSPanic(__FILE__, __LINE__,
                    "melee_pc: %s has a union with no converter -- add a hook "
                    "in dat_reloc.c (guessing the arm would corrupt silently)",
                    ty->name);
        }
    }

    return host;
}

// --- union hooks ----------------------------------------------------------
//
// One per type whose descriptor carries a DAT_UNION. Each reads the
// discriminant out of the *GameCube* bytes and converts only the live arm.
// A type with a union and no hook panics.

// Reads a big-endian u32 from the GameCube copy.
#define GC_U32(off) rd32(gc + (off))
#define GC_U16(off) rd16(gc + (off))

// Stores a converted pointer at a host offset.
static void put_ptr(u8* host, u16 off, void* p)
{
    memcpy(host + off, &p, sizeof(p));
}

// Converts the GameCube pointer at `gc_off` as `type` and stores it.
static void conv_arm(const u8* gc, u8* host, u16 gc_off, u16 host_off,
                     int type)
{
    u32 v = rd32(gc + gc_off);
    put_ptr(host, host_off,
            v ? melee_pc_dat_convert((const void*) (uintptr_t) v, type)
              : NULL);
}

// The POBJ_ENVELOPE arm is two levels deep, which no DatField kind expresses:
// it is HSD_EnvelopeDesc**, a NULL-terminated table of pointers, and each
// entry points at an *array* of HSD_EnvelopeDesc terminated by a joint == NULL
// element. loadEnvelopeDesc() (pobj.c:206) walks both:
//
//     while (*edesc_p) { ... while (edesc->joint) { ... edesc++; } edesc_p++; }
//
// Converting the arm as a single descriptor, as this used to, left the inner
// arrays in GameCube layout -- 8 bytes per element instead of 16, big-endian
// joint pointers -- so the inner walk ran off into whatever followed.
static void* conv_envelope_array(u32 gcptr)
{
    const DatType* et = &dat_types[DAT_T_HSD_EnvelopeDesc];
    const u8* e = (const u8*) (uintptr_t) gcptr;
    u32 n = 0;

    if (gcptr == 0) {
        return NULL;
    }
    // joint is at offset 0 and terminates the array.
    while (rd32(e + n * et->gc_size) != 0) {
        n++;
    }
    n++; // keep the terminator: the game's loop stops on it
    return convert_array(e, DAT_T_HSD_EnvelopeDesc, n);
}

static void conv_envelope_table(const u8* gc, u8* host, u16 goff, u16 hoff)
{
    u32 tbl = rd32(gc + goff);
    void** p = NULL;

    if (tbl != 0) {
        const u8* t = (const u8*) (uintptr_t) tbl;
        u32 n = 0, i;

        while (rd32(t + n * 4) != 0) {
            n++;
        }
        p = arena_alloc((size_t) (n + 1) * sizeof(void*));
        if (p == NULL) {
            OSPanic(__FILE__, __LINE__,
                    "melee_pc: out of memory converting envelope table");
        }
        for (i = 0; i < n; i++) {
            p[i] = conv_envelope_array(rd32(t + i * 4));
        }
        p[n] = NULL;
    }
    put_ptr(host, hoff, p);
}

// HSD_PObjDesc @20: joint | shape_set | envelope_p.
// pobj_type(o) is (flags & 0x3000); see forward.h.
static bool pobjdesc_union(const u8* gc, u8* host)
{
    const DatType* ty = &dat_types[DAT_T_HSD_PObjDesc];
    const DatField* f;
    u16 goff = 0, hoff = 0;
    u16 flags;

    for (f = ty->fields; f->kind != DAT_END; f++) {
        if (f->kind == DAT_UNION) {
            goff = f->gc_off;
            hoff = f->host_off;
        }
    }
    if (goff == 0) {
        return false;
    }

    flags = (u16) GC_U16(12); // HSD_PObjDesc::flags
    switch (flags & 0x3000) {
    case 1 << 12: // POBJ_SHAPEANIM
        conv_arm(gc, host, goff, hoff, DAT_T_HSD_ShapeSetDesc);
        return true;
    case 2 << 12: // POBJ_ENVELOPE -- HSD_EnvelopeDesc**, see above
        conv_envelope_table(gc, host, goff, hoff);
        return true;
    case 0 << 12: // POBJ_SKIN: the arm is a HSD_Joint back-reference
        conv_arm(gc, host, goff, hoff, DAT_T_HSD_Joint);
        return true;
    default:
        return false;
    }
}

// HSD_Joint @16: dobjdesc | spline | ptcl.
// jobj.c:641 picks with union_type_spline()/union_type_ptcl(), which test
// JOBJ_SPLINE (1 << 14) and JOBJ_PTCL (1 << 5) in flags.
static bool joint_union(const u8* gc, u8* host)
{
    u32 flags = GC_U32(4);

    if (flags & (1u << 14)) {
        // HSD_Spline is a runtime type with no descriptor; the address stands.
        put_ptr(host, 32, (void*) (uintptr_t) GC_U32(16));
    } else if (flags & (1u << 5)) {
        // A DAT-resident singly-linked list: 8 bytes on GameCube, 16 on host,
        // so it genuinely needs converting rather than widening.
        conv_arm(gc, host, 16, 32, DAT_T_HSD_SList);
    } else {
        conv_arm(gc, host, 16, 32, DAT_T_HSD_DObjDesc);
    }
    return true;
}

// HSD_RObjDesc @8: i | exp | bcexp | ik_hint | joint | limit.
// robj.c:615 switches on (flags & ROBJ_TYPE_MASK); constants in robj.h.
static bool robjdesc_union(const u8* gc, u8* host)
{
    u32 flags = GC_U32(4);

    switch (flags & 0x70000000u) {
    case 0x00000000u: // REFTYPE_EXP
        conv_arm(gc, host, 8, 16, DAT_T_HSD_ExpDesc);
        return true;
    case 0x10000000u: // REFTYPE_JOBJ
        conv_arm(gc, host, 8, 16, DAT_T_HSD_Joint);
        return true;
    case 0x20000000u: { // REFTYPE_LIMIT -- an f32, not a pointer
        u32 v = GC_U32(8);
        memcpy(host + 16, &v, sizeof(v));
        return true;
    }
    case 0x30000000u: // REFTYPE_BYTECODE
        conv_arm(gc, host, 8, 16, DAT_T_HSD_ByteCodeExpDesc);
        return true;
    case 0x40000000u: // REFTYPE_IKHINT
        conv_arm(gc, host, 8, 16, DAT_T_HSD_IKHintDesc);
        return true;
    default:
        return false;
    }
}

// HSD_LightDesc @24: p | shininess | point | spot | attn.
// lobj.c:958 switches on (flags & LOBJ_TYPE_MASK), then on attnflags to
// choose between the attenuation struct and the type-specific one.
static bool lightdesc_union(const u8* gc, u8* host)
{
    u16 flags = (u16) GC_U16(8);
    u16 attnflags = (u16) GC_U16(10);

    switch (flags & 3u) { // LOBJ_TYPE_MASK = LOBJ_INFINITE | LOBJ_FLAGS_B1
    case 2u: // LOBJ_POINT
        conv_arm(gc, host, 24, 40,
                 (attnflags & 1u) ? DAT_T_HSD_LightAttn
                                  : DAT_T_HSD_LightPointDesc);
        return true;
    case 3u: // LOBJ_SPOT
        conv_arm(gc, host, 24, 40,
                 attnflags != 0 ? DAT_T_HSD_LightAttn
                                : DAT_T_HSD_LightSpotDesc);
        return true;
    case 0u: // LOBJ_AMBIENT
    case 1u: // LOBJ_INFINITE
        // Neither reads the union (lobj.c:959-963). Carry the raw address so
        // nothing is silently zeroed, but do not follow it.
        put_ptr(host, 40, (void*) (uintptr_t) GC_U32(24));
        return true;
    default:
        return false;
    }
}

static const DatUnionHook dat_union_hooks[DAT_T_COUNT] = {
    [DAT_T_HSD_PObjDesc] = pobjdesc_union,
    [DAT_T_HSD_Joint] = joint_union,
    [DAT_T_HSD_RObjDesc] = robjdesc_union,
    [DAT_T_HSD_LightDesc] = lightdesc_union,
};

// The entry point the HSD_*LoadDesc functions call through MELEE_PC_DAT().
//
// Idempotent, which is the whole reason it exists: nested loads pass pointers
// that have already been converted (dobj.c:181 does
// `HSD_DObjLoadDesc(desc->next)` on an already-converted desc), and converting
// twice would read host-layout bytes as GameCube data.
//
// DAT archives live in MEM1; converted copies come from the arena, far above
// it. So the test is a range check, and it fails safe -- anything that is not
// DAT data passes straight through.
void* melee_pc_dat_root(const void* p, int type)
{
    if (p == NULL || !melee_pc_in_mem1(p)) {
        return (void*) p;
    }
    return melee_pc_dat_convert(p, type);
}

// Converts a NULL-terminated table of pointers, as a root.
//
// Some symbols are fetched from an archive as an *array* of pointers rather
// than a single structure -- "ScTitle_scene_lights" is a LightList**, walked
// as `while (*list != NULL) { ... list++; }` (lbspdisplay.c:71). The table
// itself needs widening from 4-byte to 8-byte slots as well as each element
// converting, so it cannot go through melee_pc_dat_root().
//
// Memoised on the table address so repeated roots share one host copy, using
// the same trick as the array kinds: type | 0x100 keys the table itself apart
// from an element that happens to start at the same address.
void* melee_pc_dat_root_ptrnull(const void* p, int type)
{
    const u8* t;
    void** host;
    void** slot;
    u32 n = 0;
    u32 i;

    if (p == NULL || !melee_pc_in_mem1(p)) {
        return (void*) p;
    }

    slot = (void**) memo_slot(p, type | 0x100);
    if (*slot != NULL) {
        return *slot;
    }

    t = (const u8*) p;
    while (rd32(t + n * 4) != 0) {
        n++;
    }

    host = arena_alloc((size_t) (n + 1) * sizeof(void*));
    if (host == NULL) {
        OSPanic(__FILE__, __LINE__,
                "melee_pc: out of memory converting %s*[] root",
                dat_types[type].name);
    }
    *slot = host;

    for (i = 0; i < n; i++) {
        host[i] = melee_pc_dat_convert((const void*) (uintptr_t) rd32(t + i * 4),
                                       type);
    }
    host[n] = NULL;
    return host;
}

void melee_pc_dat_reset(void)
{
    memset(memo, 0, sizeof(memo));
    memo_count = 0;
    arena_free_all();
}

// Called when one archive is freed (lbArchive_80016EFC). The memo is keyed on
// GameCube address, so entries pointing into that archive must go: the game
// reuses the memory, and a stale entry would hand back a conversion of an
// object that no longer exists. Without this the failure appears on the
// *second* scene load, which makes me lose wahtever little faith i had left
void melee_pc_dat_forget(const void* base, u32 size)
{
    static MemoEntry saved[MEMO_CAP];
    const u8* lo = base;
    const u8* hi = lo + size;
    u32 kept = 0;
    u32 i;

    if (base == NULL || size == 0) {
        return;
    }

    for (i = 0; i < MEMO_CAP; i++) {
        const u8* g = memo[i].gc;
        if (g != NULL && !(g >= lo && g < hi)) {
            saved[kept++] = memo[i];
        }
    }

    memset(memo, 0, sizeof(memo));
    memo_count = 0;
    for (i = 0; i < kept; i++) {
        void** slot = memo_slot(saved[i].gc, saved[i].type);
        *slot = saved[i].host;
    }
}

static int selftest_sentinel_array(void)
{
    static const u8 gc[24 * 3] = {
        // [0] attr = 9 (GX_VA_POS), stride 12
        0,0,0,9,  0,0,0,1,  0,0,0,1,  0,0,0,4,  0, 0, 0,12,  0,0,0,0,
        // [1] attr = 10 (GX_VA_NRM), stride 6
        0,0,0,10, 0,0,0,1,  0,0,0,0,  0,0,0,3,  0, 0, 0, 6,  0,0,0,0,
        // [2] attr = 0xFF (GX_VA_NULL) terminator
        0,0,0,0xFF, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0, 0, 0, 0,  0,0,0,0,
    };
    const DatType* ty = &dat_types[DAT_T_HSD_VtxDescList];
    const u8* arr = convert_array(gc, DAT_T_HSD_VtxDescList, 3);
    int fails = 0;
    u32 a0, a1, a2;
    u16 s0, s1;

    // Host stride, not GameCube stride -- indexing by the wrong one is exactly
    // the bug this whole exercise exists to fix.
    memcpy(&a0, arr + 0 * ty->host_size, 4);
    memcpy(&a1, arr + 1 * ty->host_size, 4);
    memcpy(&a2, arr + 2 * ty->host_size, 4);
    memcpy(&s0, arr + 0 * ty->host_size + 18, 2);
    memcpy(&s1, arr + 1 * ty->host_size + 18, 2);

    if (a0 != 9 || a1 != 10 || a2 != 0xFF) {
        OSReport("dat selftest: array attrs = %u/%u/%u, want 9/10/255\n",
                 a0, a1, a2);
        fails++;
    }
    if (s0 != 12 || s1 != 6) {
        OSReport("dat selftest: array strides = %u/%u, want 12/6\n", s0, s1);
        fails++;
    }
    return fails;
}

int melee_pc_dat_selftest(void)
{
    static const u8 gc[24] = {
        0x00, 0x00, 0x00, 0x09, // attr        @0
        0x00, 0x00, 0x00, 0x01, // attr_type   @4
        0x00, 0x00, 0x00, 0x01, // comp_cnt    @8
        0x00, 0x00, 0x00, 0x04, // comp_type   @12
        0x07,                   // frac        @16
        0x00,                   // (pad)
        0x00, 0x0C,             // stride      @18
        0x00, 0xAB, 0xCD, 0xEF, // vertex      @20
    };
    const DatType* ty = &dat_types[DAT_T_HSD_VtxDescList];
    const u8* host;
    int fails = 0;

    // The descriptors below are static data, not archive data, so the MEM1
    // bounds check has to stand down for the duration.
    melee_pc_mem1_allow_all();

    if (ty->gc_size != 24 || ty->host_size != 32) {
        OSReport("dat selftest: unexpected sizes gc=%u host=%u\n",
                 ty->gc_size, ty->host_size);
        fails++;
    }

    host = melee_pc_dat_convert(gc, DAT_T_HSD_VtxDescList);

#define CHECK(what, got, want)                                                \
    do {                                                                      \
        if ((unsigned long) (got) != (unsigned long) (want)) {                \
            OSReport("dat selftest: %s = %lu, want %lu\n", what,              \
                     (unsigned long) (got), (unsigned long) (want));          \
            fails++;                                                          \
        }                                                                     \
    } while (0)

    CHECK("attr", *(const u32*) (host + 0), 9);
    CHECK("attr_type", *(const u32*) (host + 4), 1);
    CHECK("comp_cnt", *(const u32*) (host + 8), 1);
    CHECK("comp_type", *(const u32*) (host + 12), 4);
    CHECK("frac", *(const u8*) (host + 16), 7);
    CHECK("stride", *(const u16*) (host + 18), 0x000C);
    CHECK("vertex", *(const uintptr_t*) (host + 24), 0x00ABCDEFu);
#undef CHECK

    // Same input must memoise to the same output.
    if (melee_pc_dat_convert(gc, DAT_T_HSD_VtxDescList) != (const void*) host) {
        OSReport("dat selftest: memoisation returned a different pointer\n");
        fails++;
    }

    fails += selftest_sentinel_array();

    // Every type carrying a union must have a hook
    {
        int i;
        for (i = 0; i < DAT_T_COUNT; i++) {
            if (dat_types[i].has_union && dat_union_hooks[i] == NULL) {
                OSReport("dat selftest: %s has a union but no hook\n",
                         dat_types[i].name);
                fails++;
            }
        }
    }

    OSReport("dat selftest: %s (%d failure(s))\n", fails ? "FAIL" : "ok",
             fails);
    return fails;
}

// archive header which is of course in big endian

#include <baselib/archive.h>

void melee_pc_archive_header_be(struct HSD_ArchiveHeader* h)
{
    h->file_size = __builtin_bswap32(h->file_size);
    h->data_size = __builtin_bswap32(h->data_size);
    h->nb_reloc = __builtin_bswap32(h->nb_reloc);
    h->nb_public = __builtin_bswap32(h->nb_public);
    h->nb_extern = __builtin_bswap32(h->nb_extern);
}
