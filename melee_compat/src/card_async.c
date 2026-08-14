// Deferred completion callbacks for the memory card.
//
// melee sets its "operation pending" flags after
// calling an async card function, because on
// hardware the completion arrives later from an EXI interrupt
//
// Aurora breaks that assumption in two different ways:
//
//   1. Most of its async calls do the work synchronously and invoke the
//      callback before returning. The callback therefore runs *before* the
//      the flag is set, meaning it may just deadlock because it's thinking
//      it's still busy
//
//   2. CARDMountAsync ignores its callback entirely and just returns
//      CARD_RESULT_READY

#include "compat_report.h"

// The prelude renames these, but we need the real ones
#undef CARDCheckAsync
#undef CARDCreateAsync
#undef CARDDeleteAsync
#undef CARDFormatAsync
#undef CARDMountAsync
#undef CARDReadAsync
#undef CARDRenameAsync
#undef CARDSetStatusAsync
#undef CARDWriteAsync

#include <dolphin/card.h>
#include <dolphin/os.h>

#define MAX_PENDING 8

typedef struct {
    CARDCallback cb;
    s32 chan;
    s32 result;
} CardPending;

static CardPending pending[MAX_PENDING];
static u32 pending_count;

static void card_defer(CARDCallback cb, s32 chan, s32 result)
{
    if (cb == NULL) {
        return;
    }
    if (pending_count >= MAX_PENDING) {
        OSReport("melee_pc: card completion queue overflow, dropping one\n");
        return;
    }
    pending[pending_count].cb = cb;
    pending[pending_count].chan = chan;
    pending[pending_count].result = result;
    pending_count++;
}

// Callbacks queue further card operations, so each entry is copied out before
// it runs and the queue is re-checked afterwards.
void melee_pc_card_drain(void)
{
    while (pending_count > 0) {
        CardPending p = pending[0];
        u32 i;

        pending_count--;
        for (i = 0; i < pending_count; i++) {
            pending[i] = pending[i + 1];
        }
        if (p.cb != NULL) {
            p.cb(p.chan, p.result);
        }
    }
}

// What aurora is given in place of the game's callback. Saved and restored
// around each call rather than simply assigned, so that a completion running
// from the drain can start another card operation without losing this one.
static CARDCallback tramp_target;
static bool tramp_fired;

static void card_trampoline(s32 chan, s32 result)
{
    tramp_fired = true;
    card_defer(tramp_target, chan, result);
}

#define CARD_WRAP(chan_expr, cb, call)                                        \
    CARDCallback saved_target = tramp_target;                                 \
    bool saved_fired = tramp_fired;                                           \
    s32 res;                                                                  \
    tramp_target = (cb);                                                      \
    tramp_fired = false;                                                      \
    res = (call);                                                             \
    if (!tramp_fired) {                                                       \
        /* aurora never invoked it (CARDMountAsync), so report it here. */    \
        card_defer((cb), (chan_expr), res);                                   \
    }                                                                         \
    tramp_target = saved_target;                                              \
    tramp_fired = saved_fired;                                                \
    return res

s32 melee_pc_card_read_async(const CARDFileInfo* fileInfo, void* addr,
                             s32 length, s32 offset, CARDCallback callback)
{
    CARD_WRAP(fileInfo->chan, callback,
              CARDReadAsync(fileInfo, addr, length, offset, card_trampoline));
}

s32 melee_pc_card_write_async(const CARDFileInfo* fileInfo, const void* addr,
                              s32 length, s32 offset, CARDCallback callback)
{
    CARD_WRAP(fileInfo->chan, callback,
              CARDWriteAsync(fileInfo, addr, length, offset, card_trampoline));
}

s32 melee_pc_card_mount_async(s32 chan, void* workArea,
                              CARDCallback detachCallback,
                              CARDCallback attachCallback)
{
    CARD_WRAP(chan, attachCallback,
              CARDMountAsync(chan, workArea, detachCallback,
                             card_trampoline));
}

s32 melee_pc_card_check_async(s32 chan, CARDCallback callback)
{
    CARD_WRAP(chan, callback, CARDCheckAsync(chan, card_trampoline));
}

s32 melee_pc_card_format_async(s32 chan, CARDCallback callback)
{
    CARD_WRAP(chan, callback, CARDFormatAsync(chan, card_trampoline));
}

s32 melee_pc_card_create_async(s32 chan, const char* fileName, u32 size,
                               CARDFileInfo* fileInfo, CARDCallback callback)
{
    CARD_WRAP(chan, callback,
              CARDCreateAsync(chan, fileName, size, fileInfo,
                              card_trampoline));
}

s32 melee_pc_card_delete_async(s32 chan, const char* fileName,
                               CARDCallback callback)
{
    CARD_WRAP(chan, callback,
              CARDDeleteAsync(chan, fileName, card_trampoline));
}

s32 melee_pc_card_rename_async(s32 chan, const char* oldName,
                               const char* newName, CARDCallback callback)
{
    CARD_WRAP(chan, callback,
              CARDRenameAsync(chan, oldName, newName, card_trampoline));
}

s32 melee_pc_card_set_status_async(s32 chan, s32 fileNo, const CARDStat* stat,
                                   CARDCallback callback)
{
    CARD_WRAP(chan, callback,
              CARDSetStatusAsync(chan, fileNo, stat, card_trampoline));
}
