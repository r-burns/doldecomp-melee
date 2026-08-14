#ifndef RUNTIME_PLATFORM_H
#define RUNTIME_PLATFORM_H

#include <stdbool.h>       // IWYU pragma: export
#include <stddef.h>        // IWYU pragma: export
#include <dolphin/types.h> // IWYU pragma: export

/// @typedef bool
/// @note Dolphin's #BOOL macro is not supported.
/// @typedef BOOL
/// @deprecated Use #bool instead.
#undef BOOL

/// @def false
/// @note Dolphin's #FALSE macro is not supported.
/// @def FALSE
/// @deprecated Use #false instead.
#undef FALSE

/// @def true
/// @note Dolphin's #TRUE macro is not supported.
/// @def TRUE
/// @deprecated Use #true instead.
#undef TRUE

/// The underlying type of an @c enum, used as a placeholder
typedef int enum_t;

/// A @c void callback with no arguments.
typedef void (*Event)(void);

typedef bool (*Predicate)(void);

#if defined(__MWERKS__) && defined(__PPCGEKKO__)
#define MWERKS_GEKKO
#endif

#ifndef ATTRIBUTE_ALIGN
#if defined(__MWERKS__) || defined(__GNUC__)
#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
#elif defined(_MSC_VER)
#define ATTRIBUTE_ALIGN(num)
#else
#error unknown compiler
#endif
#endif

#ifndef SECTION_INIT
#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_INIT __declspec(section ".init")
#else
#define SECTION_INIT
#endif
#endif

#ifndef SECTION_CTORS
#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_CTORS __declspec(section ".ctors")
#else
#define SECTION_CTORS
#endif
#endif

#ifndef SECTION_DTORS
#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_DTORS __declspec(section ".dtors")
#else
#define SECTION_DTORS
#endif
#endif

#ifndef ATTRIBUTE_NORETURN
#if defined(__clang__) || defined(__GNUC__)
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
#define ATTRIBUTE_NORETURN
#endif
#endif

#ifndef ATTRIBUTE_RESTRICT
#if defined(__MWERKS__) && !defined(M2CTX)
#define ATTRIBUTE_RESTRICT __restrict
#else
#define ATTRIBUTE_RESTRICT
#endif
#endif

#ifndef AT_ADDRESS
#ifdef PERMUTER
#define AT_ADDRESS(x) = FIXEDADDR(x)
#elif defined(__MWERKS__) && !defined(M2CTX)
#define AT_ADDRESS(x) : (x)
#else
#define AT_ADDRESS(x)
#endif
#endif

#ifdef __PPCGEKKO__
#define qr0 0
#define qr1 1
#define qr2 2
#define qr3 3
#define qr4 4
#define qr5 5
#define qr6 6
#define qr7 7
#endif

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF
#define U32_MAX 0xFFFFFFFF
#define S8_MAX 0x7F
#define S16_MAX 0x7FFF
#define S32_MAX 0x7FFFFFFF
#define F32_MAX 3.4028235e38f

#define SQ(x) ((x) * (x))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#ifdef __cplusplus
#ifndef _Static_assert
#define _Static_assert static_assert
#endif
#endif
#ifdef M2CTX
#define STATIC_ASSERT(cond)
#elif defined(MELEE_PC)
// The PC build cannot satisfy these. They pin struct layouts to the GameCube
// ABI, but aurora deliberately redefines the opaque GX types (GXTexObj and
// friends) with different sizes for its PC backend, so any melee struct
// embedding one changes size
#define STATIC_ASSERT(cond)
#elif defined(__MWERKS__)
#define STATIC_ASSERT(cond)                                                   \
    struct {                                                                  \
        int x[1 - 2 * !(cond)];                                               \
    };
#else
#define STATIC_ASSERT(cond) _Static_assert((cond), "(" #cond ") failed")
#endif

#ifdef MELEE_PC
#include <melee_pc_dat_types.h> // IWYU pragma: export

/// @brief Reads or writes a 32-bit value that is stored big-endian, as
/// everything inside a DAT archive is. Identity on the GameCube, which is
/// big-endian already.
#define MELEE_PC_BE32(x) __builtin_bswap32(x)

/// @brief Byte-swaps a DAT archive header in place. Nothing elsewhere.
struct HSD_ArchiveHeader;
void melee_pc_archive_header_be(struct HSD_ArchiveHeader* h);
#define MELEE_PC_ARCHIVE_HEADER_BE(h) melee_pc_archive_header_be(h)

/// @brief Converts a structure read straight out of a DAT archive into host
/// layout: byte order, field offsets and struct size all differ from the
/// GameCube's. Idempotent, so nested loads that pass an already-converted
/// pointer are left alone. Expands to the pointer unchanged everywhere else.
void* melee_pc_dat_root(const void* p, int type);
#define MELEE_PC_DAT(T, p) ((p) = melee_pc_dat_root((p), DAT_T_##T))

/// @brief As #MELEE_PC_DAT, for a symbol that is a NULL-terminated *table* of
/// pointers rather than a single structure (LightList** and friends).
void* melee_pc_dat_root_ptrnull(const void* p, int type);
#define MELEE_PC_DAT_PTRNULL(T, p)                                            \
    ((p) = melee_pc_dat_root_ptrnull((p), DAT_T_##T))

/// @brief True when an address is NOT main RAM -- i.e. an ARAM or physical
/// address. On GameCube main RAM starts at 0x80000000, so anything below that
/// is not it. On PC, MEM1 is mapped below 2GB (so that pointers round-trip
/// through the game's signed 32-bit slots), which makes the literal comparison
/// classify every main-RAM address as ARAM. Ask the compat layer where MEM1
/// actually is instead.
bool melee_pc_in_mem1(const void* p);
#define MELEE_PC_IS_NOT_MAINRAM(a)                                            \
    (!melee_pc_in_mem1((const void*) (uintptr_t) (a)))
#define MELEE_PC_IS_MAINRAM(a)                                                \
    (melee_pc_in_mem1((const void*) (uintptr_t) (a)))

/// @brief 32-byte alignment for objects used as DMA destinations.
/// HSD_DevComRequest asserts `dest % 32 == 0` (devcom.c:411). On GameCube
/// these objects are 32-byte aligned by their fixed addresses; on PC the
/// compiler only aligns them to what the type needs. Expands to nothing
/// elsewhere, so the matching build's text is unchanged.
#define MELEE_PC_ALIGN32 ATTRIBUTE_ALIGN(32)

/// @brief Tells the PC build's relocating DAT loader that an archive's memory
/// is going away, so it can drop the structures it converted out of it.
/// Expands to nothing everywhere else.
void melee_pc_dat_forget(const void* base, u32 size);
#define MELEE_PC_ON_ARCHIVE_FREE(base, size)                                  \
    melee_pc_dat_forget((base), (size))
#else
/// Identity on the GameCube, which is big-endian already.
#define MELEE_PC_BE32(x) (x)
#define MELEE_PC_DAT(T, p)
#define MELEE_PC_DAT_PTRNULL(T, p)
#define MELEE_PC_ON_ARCHIVE_FREE(base, size) ((void) 0)
#define MELEE_PC_IS_NOT_MAINRAM(a) ((u32) (a) < 0x80000000U)
#define MELEE_PC_IS_MAINRAM(a) ((u32) (a) >= 0x80000000U)
#define MELEE_PC_ALIGN32
#endif

#define RETURN_IF(cond)                                                       \
    do {                                                                      \
        if ((cond)) {                                                         \
            return;                                                           \
        }                                                                     \
    } while (0)

#if defined(__MWERKS__) && !defined(M2CTX)
#define SDATA __declspec(section ".sdata")
#define DATA __declspec(section ".data")
#define WEAK __declspec(weak)
#else
#define SDATA
#define DATA
#define WEAK
#endif

#endif
