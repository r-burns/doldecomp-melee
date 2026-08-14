// ARAM (auxiliary RAM) emulation
//
// GC had 16 MiB of ARAM reached only by DMA, there is no PC
// equivalent, so ARAM is backed by an ordinary allocation and the ARQ DMA
// queue becomes a synchronous memcpy, either way it should bef ast enough.
// Addresses handed back to the game are offsets into that block,
// matching how the hardware addressed ARAM.

#include "compat_report.h"

#include <string.h>

#include <dolphin/ar.h>

#define ARAM_SIZE (16 * 1024 * 1024)

// Statically reserved rather than malloc'd: MSL's stdlib.h, ARAM was always
// resident on the real hardware anyway.
static u8 aram_base[ARAM_SIZE];
static u32 aram_top;

u32 ARInit(u32* stack_index_addr, u32 num_entries)
{
    (void) stack_index_addr;
    (void) num_entries;
    aram_top = 0;
    return aram_top;
}

u32 ARGetSize(void) { return ARAM_SIZE; }

u32 ARAlloc(u32 length)
{
    u32 addr = aram_top;
    length = (length + 31) & ~31u;
    if (addr + length > ARAM_SIZE) {
        OSPanic(__FILE__, __LINE__, "melee_compat: out of ARAM");
    }
    aram_top = addr + length;
    return addr;
}

u32 ARFree(u32* length)
{
    if (length != NULL) {
        *length = 0;
    }
    aram_top = 0;
    return 0;
}

// aurora declares ARGetBaseAddress as returning u32; the emulated block is
// addressed from offset 0, so that is what callers get.
u32 ARGetBaseAddress(void) { return 0; }

// Completion callbacks are deferred, not run inline.
//
// On hardware the ARQ callback arrives later, from a DMA interrupt, so callers
// finish updating their own state first

#define ARQ_PENDING_MAX 64

typedef struct {
    ARQCallback cb;
    ARQRequest* req;
} ArqPending;

static ArqPending arq_pending[ARQ_PENDING_MAX];
static u32 arq_pending_count;

// Drained once per frame from the aurora frame pump, and again before each new
// request so a chain of transfers can make progress without waiting on a
// frame. HSD_DevComRequest queues and returns rather than blocking, so nothing
// deadlocks waiting for one of these.
unsigned long melee_pc_dbg_arq_posted;
unsigned long melee_pc_dbg_arq_done;

unsigned long melee_pc_arq_pending(void) { return arq_pending_count; }

// Bounded nesting rather than none. An ARQ callback runs melee's DevCom chain,
// which spins waiting for a *later* ARQ completion, so a drain that refuses to
// re-enter deadlocks there. Nesting is safe here specifically because the entry
// is popped before its callback runs: a nested drain can only ever see work
// the outer one has not claimed, and every level makes progress.
// The cap is just for safety, to prevent deadlocks.
#define ARQ_MAX_DEPTH 16

void melee_pc_arq_drain(void)
{
    static int depth;

    if (depth >= ARQ_MAX_DEPTH) {
        return;
    }
    depth++;
    while (arq_pending_count > 0) {
        // Taken before the callback runs: callbacks post further requests.
        ArqPending p = arq_pending[0];
        u32 i;
        arq_pending_count--;
        for (i = 0; i < arq_pending_count; i++) {
            arq_pending[i] = arq_pending[i + 1];
        }
        melee_pc_dbg_arq_done++;
        if (p.cb != NULL) {
            p.cb((uintptr_t) p.req);
        }
    }
    depth--;
}

static void arq_defer(ARQCallback cb, ARQRequest* req)
{
    melee_pc_dbg_arq_posted++;
    if (cb == NULL) {
        return;
    }
    if (arq_pending_count >= ARQ_PENDING_MAX) {
        OSPanic(__FILE__, __LINE__, "melee_pc: ARQ completion queue full");
    }
    arq_pending[arq_pending_count].cb = cb;
    arq_pending[arq_pending_count].req = req;
    arq_pending_count++;
}

void ARQInit(void) { arq_pending_count = 0; }

// Converts ARQ offset to a real address
static void* aram_resolve(uintptr_t addr)
{
    if (addr < ARAM_SIZE) {
        return aram_base + addr;
    }
    return (void*) addr;
}

void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority,
                    uintptr_t source, uintptr_t dest, u32 length,
                    ARQCallback callback)
{
    // Let anything already finished report in first.
    melee_pc_arq_drain();

    request->owner = owner;
    request->type = type;
    request->priority = priority;
    request->source = (u32) source;
    request->dest = (u32) dest;
    request->length = length;
    request->callback = callback;

    // ARAM_DIR_MRAM_TO_ARAM writes into the emulated block; the other
    // direction reads out of it.
    if (type == ARAM_DIR_MRAM_TO_ARAM) {
        memcpy(aram_resolve(dest), (const void*) source, length);
    } else {
        memcpy((void*) dest, aram_resolve(source), length);
    }

    arq_defer(callback, request);
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
{
    if (type == ARAM_DIR_MRAM_TO_ARAM) {
        memcpy(aram_resolve(aram_addr), (const void*) mainmem_addr, length);
    } else {
        memcpy((void*) mainmem_addr, aram_resolve(aram_addr), length);
    }
}
