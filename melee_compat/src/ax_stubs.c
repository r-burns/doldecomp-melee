// AX (audio mixer) stubs
//
// Aurora has no AX implementation. Voices are handed out from a fixed pool so
// the game's bookkeeping works, but nothing is mixed or played yet

#include "compat_report.h"

#include <string.h>

#include <dolphin/ax.h>

#define AX_MAX_VOICES 64

static AXVPB voices[AX_MAX_VOICES];
static u8 voice_in_use[AX_MAX_VOICES];

void AXInit(void)
{
    COMPAT_STUB();
    memset(voices, 0, sizeof(voices));
    memset(voice_in_use, 0, sizeof(voice_in_use));
}

void AXQuit(void) {}

AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void*), u32 userContext)
{
    int i;
    (void) callback;
    for (i = 0; i < AX_MAX_VOICES; i++) {
        if (!voice_in_use[i]) {
            voice_in_use[i] = 1;
            memset(&voices[i], 0, sizeof(voices[i]));
            voices[i].priority = priority;
            voices[i].userContext = userContext;
            return &voices[i];
        }
    }
    return NULL;
}

void AXFreeVoice(AXVPB* p)
{
    if (p != NULL) {
        voice_in_use[p - voices] = 0;
    }
}

void AXSetVoicePriority(AXVPB* p, u32 priority)
{
    if (p != NULL) {
        p->priority = priority;
    }
}

// aurora declares the parameter unprototyped; (void) is compatible with that
// and keeps -Werror=strict-prototypes happy.
void AXRegisterCallback(void (*callback)(void)) { (void) callback; }
void AXRegisterAuxACallback(void (*cb)(void*, void*), void* ctx) { (void) cb; (void) ctx; }
void AXRegisterAuxBCallback(void (*cb)(void*, void*), void* ctx) { (void) cb; (void) ctx; }

void AXSetVoiceState(AXVPB* p, u16 state) { (void) p; (void) state; }
void AXSetVoiceType(AXVPB* p, u16 type) { (void) p; (void) type; }
void AXSetVoiceMix(AXVPB* p, AXPBMIX* mix) { (void) p; (void) mix; }
void AXSetVoiceItdOn(AXVPB* p) { (void) p; }
void AXSetVoiceItdTarget(AXVPB* p, u16 l, u16 r) { (void) p; (void) l; (void) r; }
void AXSetVoiceVe(AXVPB* p, AXPBVE* ve) { (void) p; (void) ve; }
void AXSetVoiceVeDelta(AXVPB* p, s16 delta) { (void) p; (void) delta; }
void AXSetVoiceAddr(AXVPB* p, AXPBADDR* addr) { (void) p; (void) addr; }
void AXSetVoiceLoop(AXVPB* p, u16 loop) { (void) p; (void) loop; }
void AXSetVoiceLoopAddr(AXVPB* p, u32 addr) { (void) p; (void) addr; }
void AXSetVoiceEndAddr(AXVPB* p, u32 addr) { (void) p; (void) addr; }
void AXSetVoiceCurrentAddr(AXVPB* p, u32 addr) { (void) p; (void) addr; }
void AXSetVoiceAdpcm(AXVPB* p, AXPBADPCM* a) { (void) p; (void) a; }
void AXSetVoiceAdpcmLoop(AXVPB* p, AXPBADPCMLOOP* a) { (void) p; (void) a; }
void AXSetVoiceSrc(AXVPB* p, AXPBSRC* s) { (void) p; (void) s; }
void AXSetVoiceSrcType(AXVPB* p, u32 type) { (void) p; (void) type; }
void AXSetVoiceSrcRatio(AXVPB* p, float ratio) { (void) p; (void) ratio; }
