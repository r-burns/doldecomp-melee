#include "devcom.h"

#include <baselib/debug.h>
#include <baselib/synth.h>

#define DEVCOMDEST_SBUF 2
#define DEVCOM_BUF_SIZE 0x4000

static ARQRequest devComARQR[2][2];
static HSD_DevCom* devComStatus[4];
static HSD_DevCom* HSD_DevCom_804C6330[4];
static u8 HSD_DevCom_804C6330_bufs[2][DEVCOM_BUF_SIZE];
static DVDFileInfo info;

static HSD_DevCom* HSD_DevCom_804D77F0; // next devcom
static u8 aramstate;
static HSD_DevCom* HSD_DevCom_804D7808;
static u8 devComRelayBufFlag[2];
static u8 HSD_DevCom_804D77F5;
static u8 HSD_DevCom_804D77F6;
static HSD_DevCom* HSD_DevCom_804D77F8;
static int HSD_DevCom_804D7804;

static int HSD_DevCom_804D6050 = 4;

bool HSD_DevComIsBusy(int idx)
{
    return (bool) devComStatus[idx];
}

void HSD_DevComUnlink(HSD_DevCom* dc)
{
    HSD_DevCom* curr;
    bool enabled = OSDisableInterrupts();
    int i = dc->dcReq & 3;

    if (devComStatus[i] == dc) {
        devComStatus[i] = dc->next;
        if (HSD_DevCom_804C6330[i] == dc) {
            HSD_DevCom_804C6330[i] = 0;
        }
        goto cleanup;
    }

    for (curr = devComStatus[i]; curr->next != NULL; curr = curr->next) {
        if (curr->next == dc) {
            curr->next = dc->next;
            if (HSD_DevCom_804C6330[i] == dc) {
                HSD_DevCom_804C6330[i] = curr;
            }
            OSRestoreInterrupts(enabled);
            return;
        }
    }
    HSD_ASSERT(0x6E, 0);

cleanup:
    OSRestoreInterrupts(enabled);
}

void HSD_DevComStdCallback(ARQRequest* request)
{
    int i;

    if (request == &devComARQR[0][0]) {
        i = 0;
    } else if (request == &devComARQR[1][0]) {
        i = 1;
    } else {
        HSD_ASSERT(0xA5, 0);
    }
    aramstate = 0;
    devComRelayBufFlag[i] = 0;
    HSD_DevComDVDWakeUp();
    HSD_DevComARAMWakeUp();
}

static inline void HSD_DevComARAMCallback_inline(void)
{
    HSD_DevCom* temp_r30 = HSD_DevCom_804D7808;
    bool temp_r3 = OSDisableInterrupts();
    temp_r30->next = HSD_DevCom_804D77F0;
    HSD_DevCom_804D77F0 = temp_r30;
    OSRestoreInterrupts(temp_r3);
}

void HSD_DevComARAMCallback(ARQRequest* arg0)
{
    int var_r0;
    void* var_r5;

    if (HSD_DevCom_804D7808->type == 0x1A) {
        if (arg0 == &devComARQR[0][0]) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
        var_r5 = HSD_DevCom_804C6330_bufs[var_r0];
    } else {
        var_r5 = NULL;
    }

    if (HSD_DevCom_804D7808->callback != NULL) {
        HSD_DevCom_804D7808->callback((void*)
            HSD_DevCom_804D7808->dcReq, (int) HSD_DevCom_804D7808->args,
            var_r5, HSD_DevCom_804D7808->cancelflag);
    }

    HSD_DevComUnlink(HSD_DevCom_804D7808);
    HSD_DevComARAMCallback_inline();
    HSD_DevComStdCallback(arg0);
}

/// #HSD_DevComARAMWakeUp

static char assert_msg_1[] = "dvdDC->size <= DEVCOM_BUF_SIZE";
static char assert_msg_2[] = "dvdDC->callback";

/// #HSD_DevComDVDStdCallback

/// #HSD_DevComDVDARAMEndCallback

void HSD_DevComDVDMemCallback(s32 arg0, DVDFileInfo* arg1)
{
    HSD_DevCom* temp_r31;
    s32 temp_r3_2;

    if (arg0 == -1) {
        HSD_DevCom_804D7804 = 1;
    }
    if ((u32) HSD_DevCom_804D77F8->size > 0x80000U) {
        HSD_DevCom_804D77F8->src += 0x80000;
        HSD_DevCom_804D77F8->dest += 0x80000;
        HSD_DevCom_804D77F8->size += 0xFFF80000;
        HSD_DevCom_804D77F5 = 0;
        HSD_DevComDVDWakeUp();
        return;
    }
    if ((HSD_DevCom_804D77F8->callback != NULL) && ((s32) HSD_DevCom_804D7804 == 0)) {
        HSD_DevCom_804D77F8->callback((void* ) HSD_DevCom_804D77F8->dcReq, (s32) HSD_DevCom_804D77F8->args, NULL, (s32) HSD_DevCom_804D77F8->cancelflag);
    }
    HSD_DevComUnlink(HSD_DevCom_804D77F8);
    temp_r31 = HSD_DevCom_804D77F8;
    temp_r3_2 = OSDisableInterrupts();
    temp_r31->next = HSD_DevCom_804D77F0;
    HSD_DevCom_804D77F0 = temp_r31;
    OSRestoreInterrupts(temp_r3_2);
    HSD_DevCom_804D77F5 = 0;
    HSD_DevComDVDWakeUp();
}

/// #HSD_DevComDVDCallback

void HSD_DevComDVDWakeUp(void)
{
    HSD_DevCom* temp_r0;
    HSD_DevCom** var_r29;
    s32 temp_r30;
    s32 var_ctr;
    s32 var_r28;
    int var_r4;
    u32 var_r5;
    u32 var_r5_2;
    u8* var_r3;
    void (*temp_r12)(void*, int, void*, int);
    int i;

    temp_r30 = OSDisableInterrupts();
    if ((u8) HSD_DevCom_804D77F5 != 0) {
        OSRestoreInterrupts(temp_r30);
        return;
    }
    var_r28 = 0;
    var_r29 = devComStatus;
loop_3:
    temp_r0 = *var_r29;
    HSD_DevCom_804D77F8 = temp_r0;
    if (temp_r0 != NULL) {
        if (HSD_DevCom_804D77F8->cancelflag != 0) {
            if (HSD_DevCom_804D77F8->callback != NULL) {
                HSD_DevCom_804D77F8->callback((void* ) HSD_DevCom_804D77F8->dcReq, (s32) HSD_DevCom_804D77F8->args, NULL, 1);
            }
            HSD_DevComUnlink(HSD_DevCom_804D77F8);
            OSRestoreInterrupts(temp_r30);
            HSD_DevComDVDWakeUp();
            return;
        }
        DVDFastOpen(HSD_DevCom_804D77F8->file, &info);
        if ((u16) HSD_DevCom_804D77F8->type == 0x21) {
            var_r5 = HSD_DevCom_804D77F8->size;
            if (var_r5 < 0x80000U) {

            } else {
                var_r5 = 0x80000;
            }
            DVDReadAsyncPrio(&info, (void* ) HSD_DevCom_804D77F8->dest, (s32) var_r5, (s32) HSD_DevCom_804D77F8->src, HSD_DevComDVDMemCallback, 2);
            HSD_DevCom_804D77F5 = 1;
            OSRestoreInterrupts(temp_r30);
            return;
        }
        var_ctr = 2;
        var_r4 = 0;
        var_r3 = &devComRelayBufFlag[0];
loop_14:
        if ((u8) *var_r3 == 0) {
            devComRelayBufFlag[var_r4] = 1;
        } else {
            var_r3 += 1;
            var_r4 += 1;
            var_ctr -= 1;
            if (var_ctr == 0) {
                var_r4 = -1;
            } else {
                goto loop_14;
            }
        }
        if (var_r4 >= 0) {
            HSD_DevCom_804D77F6 = var_r4;
            var_r5_2 = HSD_DevCom_804D77F8->size;
            if (var_r5_2 < 0x4000U) {

            } else {
                var_r5_2 = 0x4000;
            }
            DVDReadAsyncPrio(&info,
                    HSD_DevCom_804C6330_bufs[var_r4],
                    //&devComARQR + (var_r4 << 0xE) + 0xA0,
                    (s32) var_r5_2, (s32) HSD_DevCom_804D77F8->src, HSD_DevComDVDCallback, 2);
            HSD_DevCom_804D77F5 = 1;
            OSRestoreInterrupts(temp_r30);
            return;
        }
        goto block_23;
    }
block_23:
    var_r28 += 1;
    var_r29 += 1;
    if (var_r28 >= 3) {
        OSRestoreInterrupts(temp_r30);
        return;
    }
    goto loop_3;
}

static inline int HSD_DevComGetDestType(int type)
{
    return type & 7;
}

#define INIT_N_DEVCOMS 16

static inline void DevComLinkNext(HSD_DevCom* dc)
{
    int i;
    for (i = 1; i < INIT_N_DEVCOMS-1; i++) {
        dc[i].next = &dc[i] + 1;
    }
    dc[i].next = NULL;
}

int HSD_DevComRequest(int file, u32 src, u32 dest, size_t size, int type,
                      int pri, HSD_DevComCallback callback, void* args)
{
    bool enabled;
    HSD_DevCom* dc;
    int result;

    enabled = OSDisableInterrupts();

    if ((dc = HSD_DevCom_804D77F0)) {
        HSD_DevCom_804D77F0 = dc->next;
        OSRestoreInterrupts(enabled);
    } else {
        dc = HSD_AudioMalloc(sizeof(HSD_DevCom) * INIT_N_DEVCOMS);
        DevComLinkNext(dc);

        HSD_DevCom_804D77F0 = &dc[1];
        OSRestoreInterrupts(enabled);
    }

    HSD_ASSERT(0x1ED, dc);
    HSD_ASSERT(0x1EE,
        !(HSD_DevComGetDestType(type) == DEVCOMDEST_SBUF
            && size > DEVCOM_BUF_SIZE));

    HSD_ASSERT(0x1EF, src % 32 == 0);
    HSD_ASSERT(0x1F0, dest % 32 == 0);
    HSD_ASSERT(0x1F1, size % 32 == 0);
    HSD_ASSERT(0x1F2, size != 0);

    pri = (type & 0x38) == 0x20 ? pri : 3;

    dc->file = file;
    dc->src = src;
    dc->dest = dest;
    dc->size = size;
    dc->type = type;
    dc->cancelflag = 0;
    dc->callback = callback;
    dc->args = args;

    enabled = OSDisableInterrupts();
    result = HSD_DevCom_804D6050 + pri;
    dc->dcReq = result;
    HSD_DevCom_804D6050 += 4;
    if (HSD_DevCom_804C6330[pri] != NULL) {
        HSD_DevCom_804C6330[pri]->next = dc;
    }
    HSD_DevCom_804C6330[pri] = dc;
    dc->next = NULL;
    if (devComStatus[pri] == NULL) {
        devComStatus[pri] = dc;
        HSD_DevComDVDWakeUp();
        HSD_DevComARAMWakeUp();
    }
    OSRestoreInterrupts(enabled);

    return result;
}

/// #HSD_DevComCancelEx
