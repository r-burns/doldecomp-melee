#include "lbmemory.h"

#include <platform.h>

#include <placeholder.h>
#include <baselib/debug.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/ar.h>

struct Allocator {
    void* x0_arenaLo;
    void* x4_arenaHi;
    Handle x8[0x83];
    Handle* x62C_free_mem;
    s32 x630_num_allocs;
    s32 x634_max_num_allocs;
    struct AllocUnkInternal {
        struct AllocUnkInternal* next;
        u32 x4, x8, xC;
    } x638[6];
    Handle* x698_free_heap;
    Handle* x69C;
    struct AlarmStruct {
        OSAlarm x0;
        u8* x28;
        u8* x2C;
        u32 size;
        u32 x34;
        int x38;
        void (*x3C)();
    } x6A0;
    void* x6E0;
    void* x6E4;
    void (*x6E8)(void*);
    u8 x6EC[0x6F0 - 0x6EC];
};

static void lbMemory_80015320(u32 arg0, Handle* arg1, u32 arg2, bool cancelflag);

/* 015320 */ //static void lbMemory_80015320(int, Handle*, int, int);

// lbMemory_804318B0
static struct Allocator g_alloc;
STATIC_ASSERT(sizeof(g_alloc) == 0x6F0);

// might need to change to take lvalue instead of pointer if codegen is bad
#define PUSH_HANDLE(list, handle)                                             \
    do {                                                                      \
        handle->x0_next = *list;                                              \
        *list = handle;                                                       \
    } while (0)
#define POP_HANDLE(list, handle)                                              \
    do {                                                                      \
        handle = *list;                                                       \
        *list = handle->x0_next;                                              \
    } while (0)

// pops handle from freelist and sets the popped regions's bounds
static inline Handle* new_handle(void* arenaLo, void* arenaHi)
{
    Handle* h;
    if (g_alloc.x698_free_heap == NULL) {
        __assert(__FILE__, 0x7BU, "_p(free_heap)");
    }
    // assert_arena_in_bounds(arenaLo, arenaHi);

    if (((u32) arenaLo < 0x80000000U) && ((u32) arenaHi < 0x80000000U)) {
        int ok = 0;
        if (((u32) arenaLo >= (u32) g_alloc.x0_arenaLo) &&
            ((u32) arenaHi <= (u32) g_alloc.x4_arenaHi))
        {
            ok = 1;
        }
        if (ok == 0) {
            __assert(__FILE__, 0x80U,
                     "(u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= "
                     "(u32)_p(a_arenaHi)");
        }
    }

    POP_HANDLE(&g_alloc.x698_free_heap, h);
    h->x0_next = NULL;
    h->x4_lo = arenaLo;
    h->x8_hi = arenaHi;
    h[1].x0_next = NULL;
    return h;
}

Handle* lbMemory_80014E24(void* arenaLo, void* arenaHi)
{
    return new_handle(arenaLo, arenaHi);
}

// moves a list of handles into x62C
// then pushes the head to free_heap
// why does it start at handle->xC_prev?
void lbMemory_80014EEC(Handle* handle)
{
    Handle* iter;
    Handle* tmp_next;
    if (handle == NULL) {
        __assert(__FILE__, 0x95U, "handle");
    }
    for (iter = handle[1].x0_next; iter != NULL;) {
        tmp_next = iter->x0_next;
        PUSH_HANDLE(&g_alloc.x62C_free_mem, iter);
        iter = tmp_next;
        g_alloc.x630_num_allocs -= 1;
    }
    PUSH_HANDLE(&g_alloc.x698_free_heap, handle);
}

u32 lbMemory_80014F7C(Handle* h)
{
    u32 r4 = (u32) h->x4_lo;
    Handle* iter = h + 1;
    u32 sum = 0;

loop:
    iter = iter->x0_next;
    sum += (u32) (iter != NULL ? iter->x4_lo : h->x8_hi) - r4;
    if (iter != NULL) {
        r4 = (u32) iter->x4_lo + (u32) iter->x8_hi;
        goto loop;
    }
    return sum;
}

// malloc
Handle* lbMemory_80014FC8(Handle* arg0, u32 size)
{
    Handle* memp_candidate;
    Handle* iter;
    u32 aligned_size;
    u32 leftover;
    u32 available_space;
    u32 least_leftover;
    void* start;
    void* end;
    void* lo;

    least_leftover = 0x40000000;
    if (g_alloc.x62C_free_mem == NULL) {
        __assert(__FILE__, 0xCC, "_p(free_mem)");
    }
    start = arg0->x4_lo;
    // 32 byte alignment
    aligned_size = (size + 0x1F) & 0xFFFFFFE0;
    iter = arg0 + 1;
    memp_candidate = NULL;

    while (1) {
        // iter = var_r5->x0_next;
        // we look at iter each iteration,
        // until the last iteration, we check arg0
        end = (iter->x0_next != NULL) ? iter->x0_next->x4_lo : arg0->x8_hi;
        available_space = (u32) end - (u32) start;
        if (available_space >= aligned_size) {
            leftover = available_space - aligned_size;
            if (leftover <= least_leftover) {
                least_leftover = leftover;
                lo = start;
                memp_candidate = iter;
            }
        }
        if (iter->x0_next == NULL) {
            break;
        } else {
            iter = iter->x0_next;
            start = (void*) ((u32) iter->x4_lo + (u32) iter->x8_hi);
        }
    }
    if (memp_candidate == NULL) {
        // oom
        __assert(__FILE__, 0xE9, "memp_kouho");
    }
    {
        Handle* result;
        POP_HANDLE(&g_alloc.x62C_free_mem, result);

        result->x8_hi = (void*) aligned_size;
        result->x4_lo = lo;
        result->x0_next = memp_candidate->x0_next;
        memp_candidate->x0_next = result;

        g_alloc.x630_num_allocs += 1;
        if (g_alloc.x630_num_allocs > g_alloc.x634_max_num_allocs) {
            g_alloc.x634_max_num_allocs = g_alloc.x630_num_allocs;
        }
        return result;
    }
}

/// @todo Should be `__FILE__`
extern char* filename;

// 100% except for literal relocations
void lbMemory_800150F0(Handle* h, void* arg1)
{
    Handle* handle = h[1].x0_next;
    Handle* r6 = h + 1;

    while (handle != NULL) {
        if (handle->x4_lo == arg1) {
            r6->x0_next = handle->x0_next;
            PUSH_HANDLE(&g_alloc.x62C_free_mem, handle);
            g_alloc.x630_num_allocs -= 1;
            return;
        }
        r6 = handle;
        handle = handle->x0_next;
    }
    OSReport("[LbMem] Error: lbMemFreeToHeap %x.\n", arg1);
    HSD_ASSERT(283, 0);
}

void fn_80015184(OSAlarm* alarm, OSContext* context)
{
    struct AlarmStruct* temp_r3;
    u32 temp_r3_2;
    u32 temp_r6;
    u32 var_r30;

    temp_r3 = &g_alloc.x6A0;
    if (temp_r3->size == 0) {
        __assert("lbmemory.c", 0x127, "p->size");
    }
    temp_r6 = temp_r3->x34;
    temp_r3_2 = temp_r3->size - temp_r6;
    var_r30 = temp_r3_2;
    if (temp_r3_2 > 0x19000) {
        var_r30 = 0x19000;
    }
    memcpy(temp_r3->x2C + temp_r6, temp_r3->x28 + temp_r6, var_r30);
    temp_r3->x34 += var_r30;
    if (temp_r3->x34 == temp_r3->size) {
        temp_r3->size = 0;
        temp_r3->x3C(0, temp_r3->x38, 0, 0);
    } else {
        OSCreateAlarm(&temp_r3->x0);
        OSSetAlarm(&temp_r3->x0, OSMillisecondsToTicks(3), fn_80015184);
    }
}

u32 lbMemory_8001529C(Handle* h, void* arg1, u32 arg2)
{
    void* lo;
    Handle* iter;
    void** r7;

    g_alloc.x6E8 = arg1;
    g_alloc.x6E0 = (void*) arg2;
    g_alloc.x6E4 = h->x4_lo;

    r7 = &g_alloc.x6E4;

    for (iter = h[1].x0_next; iter != NULL; iter = iter->x0_next) {
        lo = iter->x4_lo;
        if (lo != *r7) {
            lbMemory_80015320(0, iter, 0, 0);
            return 1;
        }
        *r7 = (void*) ((u32) lo + (u32) iter->x8_hi);
    }
    return 0;
}

static check_p(struct AlarmStruct* p)
{
    HSD_ASSERT(0x14F, !p->size);
}

void lbMemory_80015320(u32 arg0, Handle* arg1, u32 arg2, bool cancelflag)
{
    void* temp_r31;
    struct AlarmStruct* temp_r30;
    u32 temp_r26;
    void* temp_r29;
    s32 temp_r28;
    u32* temp_r25;
    void* temp_r25_2;

    temp_r25 = (void*) &g_alloc.x6E4;
    temp_r29 = (void*) g_alloc.x6E4;
    if (cancelflag != 0) {
        __assert(__FILE__, 0x188U, "!cancelflag");
    }
    if (arg1 != 0) {
        if ((temp_r31 = arg1->x4_lo) != temp_r29) {
            arg1->x4_lo = temp_r29;
            *temp_r25 = (uintptr_t) arg1->x4_lo + (uintptr_t) arg1->x8_hi;
            if ((uintptr_t) arg1->x4_lo < 0x80000000) {
                HSD_DevComRequest(0, temp_r31, temp_r29,
                        ((uintptr_t) arg1->x8_hi + 0x1F) & 0xFFFFFFE0,
                        0x1B, 1, lbMemory_80015320, arg1->x0_next);
                return;
            }
            temp_r30 = &g_alloc.x6A0;
            temp_r25_2 = arg1->x0_next;
            temp_r26 = ((uintptr_t) arg1->x8_hi + 0x1F) & 0xFFFFFFE0;
            temp_r28 = OSDisableInterrupts();
            check_p(temp_r30);
            temp_r30->x28 = temp_r31;
            temp_r30->x2C = temp_r29;
            temp_r30->size = temp_r26;
            temp_r30->x34 = 0;
            temp_r30->x38 = (uintptr_t) temp_r25_2;
            temp_r30->x3C = lbMemory_80015320;
            OSRestoreInterrupts(temp_r28);
            OSCreateAlarm(&temp_r30->x0);
            OSSetAlarm(&temp_r30->x0, OSMillisecondsToTicks(3), fn_80015184);
            return;
        }
        *temp_r25 = (uintptr_t) temp_r31 + (uintptr_t) arg1->x8_hi;
        lbMemory_80015320(NULL, arg1->x0_next, NULL, 0);
        return;
    }
    g_alloc.x6E8(g_alloc.x6E0);
}

// getArenaBounds
void lbMemory_800154BC(uintptr_t* arenaLo, uintptr_t* arenaHi)
{
    *arenaLo = (uintptr_t) g_alloc.x0_arenaLo;
    *arenaHi = (uintptr_t) g_alloc.x4_arenaHi;
}

// same as lbMemory_80014E24, but sets to x69C to the popped handle
Handle* lbMemory_800154D4(void* arenaLo, void* arenaHi)
{
    g_alloc.x69C = new_handle(arenaLo, arenaHi);
    return g_alloc.x69C;
}

void lbMemory_800155A4(void)
{
    Handle* handle = g_alloc.x69C;
    Handle* iter;

    Handle** r5;

    HSD_ASSERT(149, handle);
    r5 = &g_alloc.x62C_free_mem;
    for (iter = handle[1].x0_next; iter != NULL;) {
        Handle* tmp_next = iter->x0_next;
        PUSH_HANDLE(r5, iter);
        iter = tmp_next;
        g_alloc.x630_num_allocs -= 1;
    }
    PUSH_HANDLE(&g_alloc.x698_free_heap, handle);
    g_alloc.x69C = NULL;
}

void lbMemory_8001564C(void)
{
    u32 sp14;
    int i;

    g_alloc.x0_arenaLo = (void*) ARAlloc(0x20);
    ARFree(&sp14);
    g_alloc.x4_arenaHi = (void*) (ARGetSize() > 0x1000000 ? 0x1000000 : ARGetSize());
    g_alloc.x62C_free_mem = (void*) g_alloc.x8;

    for (i = 0; i < 0x82; i++) {
        g_alloc.x8[i].x0_next = (void*) &g_alloc.x8[i + 1];
    }
    g_alloc.x8[i].x0_next = NULL;

    g_alloc.x634_max_num_allocs = 0;
    g_alloc.x630_num_allocs = 0;

    g_alloc.x698_free_heap = (void*) &g_alloc.x638[0];
    for (i = 0; i < 5; i++) {
        g_alloc.x638[i].next = &g_alloc.x638[i + 1];
    }
    g_alloc.x638[i].next = NULL;

    g_alloc.x69C = NULL;

    g_alloc.x69C = lbMemory_80014E24(g_alloc.x0_arenaLo, g_alloc.x4_arenaHi);
    g_alloc.x6A0.size = 0;
}
