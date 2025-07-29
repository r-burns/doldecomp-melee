#include "synth.static.h"

#include <dolphin/os.h>
#include <sysdolphin/baselib/devcom.h>

static int HSD_Synth_804D6018 = -1;
static int HSD_Synth_804D6028[2] = { 0 };
extern s32 HSD_Synth_804C2A60[0x18];

static u8 HSD_Synth_804C2AC0[0x20];

void* HSD_AudioMalloc(size_t arg0)
{
    void* temp_r3;

    temp_r3 = OSAllocFromHeap(HSD_Synth_804D6018, arg0);
    if (temp_r3 == NULL) {
        OSReport("audio heap overflow.\n");
        __assert("synth.c", 0x29U, "p");
    }
    return temp_r3;
}

void HSD_AudioFree(void* arg0)
{
    OSFreeToHeap(HSD_Synth_804D6018, arg0);
}

/// #HSD_SynthSFXSampleLoadCallback

/// #HSD_SynthSFXHeaderLoadCallback

void HSD_SynthSFXLoadNewProc(void)
{
    s32 temp_r31;

    if (HSD_Synth_804D772C != 0) {
        temp_r31 = OSDisableInterrupts();
        HSD_Synth_804D6028[0] = HSD_DevComRequest(*HSD_Synth_804C2A60, 0U, (u32) HSD_Synth_804C2AC0, 0x20U, 0x21, 1, HSD_SynthSFXHeaderLoadCallback, NULL);
        OSRestoreInterrupts(temp_r31);
    }
}

/// #HSD_SynthSFXLoad

void HSD_Synth_80388B0C(void (*arg0)(void))
{
    while (HSD_Synth_804D772C != 0) {
        arg0();
    }
}

s32 HSD_Synth_80388B50(void)
{
    return HSD_Synth_804D772C - HSD_Synth_804D7738;
}

/// #HSD_Synth_80388B60

/// #HSD_Synth_80388CB0

/// #HSD_Synth_80388D30

/// #HSD_Synth_80388DC8

/// #HSD_Synth_80388E08

/// #HSD_SynthSFXGroupDataReaddressCallback

/// #HSD_SynthSFXGroupDataReaddress

/// #HSD_SynthSFXBankDeflag

void HSD_SynthSFXBankDeflagSync(void)
{
    while (HSD_Synth_804D773C) {
        continue;
    }
}

/// #HSD_Synth_80389094

/// #HSD_Synth_803890B4

/// #HSD_Synth_8038912C

/// #dropcallback

/// #HSD_Synth_80389334

/// #HSD_Synth_803896F0

/// #HSD_SynthSFXKeyOff

/// #HSD_SynthSFXStopRange

/// #HSD_SynthSFXPause

/// #HSD_SynthSFXResume

/// #HSD_SynthSFXCheck

/// #HSD_SynthSFXSetVolumeFade

/// #HSD_Synth_80389CC4

/// #HSD_SynthSFXSetMix

/// #HSD_SynthSFXUpdatePitch

/// #HSD_Synth_80389E2C

/// #HSD_Synth_80389F4C

/// #HSD_Synth_8038A000

/// #HSD_SynthSFXUpdateVolume

/// #HSD_SynthSFXUpdateMix

/// #HSD_SynthSFXUpdateAllVolume

void HSD_SynthSFXSetDriverInactivatedCallback(UNK_T arg0)
{
    driverInactivatedCallback = arg0;
}

void HSD_SynthSFXSetDriverMasterClockCallback(UNK_T arg0)
{
    driverMasterClockCallback = arg0;
}

void HSD_SynthSFXSetDriverPauseCallback(UNK_T arg0)
{
    driverPauseCallback = arg0;
}

/// #HSD_SynthCallback

void fn_8038AD60(void)
{
    HSD_Synth_804D776C = HSD_Synth_804D7768, HSD_Synth_804D7778 = 0;
}

/// #HSD_Synth_8038AD74

/// #HSD_Synth_8038ADD0

/// #HSD_Synth_8038B120

/// #HSD_SynthPStreamFirstHakoHeaderCallback

/// #HSD_SynthPStreamHeaderCallback

/// #HSD_Synth_8038B5AC

/// #HSD_SynthStreamSetVolume

/// #HSD_SynthInit
