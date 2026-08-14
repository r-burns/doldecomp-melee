#ifndef MELEE_COMPAT_DOLPHIN_PAD_H
#define MELEE_COMPAT_DOLPHIN_PAD_H

// Aurora's <dolphin/pad.h> declares the PAD API but not the special button masks
// matches extern/dolphin/include/dolphin/pad.h.

#include_next <dolphin/pad.h>

#ifndef PAD_STICK_UP
#define PAD_STICK_UP (1 << 16)
#define PAD_STICK_DOWN (1 << 17)
#define PAD_STICK_LEFT (1 << 18)
#define PAD_STICK_RIGHT (1 << 19)
#endif

#ifndef PAD_SUBSTICK_UP
#define PAD_SUBSTICK_UP (1 << 20)
#define PAD_SUBSTICK_DOWN (1 << 21)
#define PAD_SUBSTICK_LEFT (1 << 22)
#define PAD_SUBSTICK_RIGHT (1 << 23)
#endif

#ifndef PAD_TRIGGER_LR
#define PAD_TRIGGER_LR (1 << 31)
#endif

#ifndef PAD_CONFIRM
#define PAD_CONFIRM (1ULL << 32)
#define PAD_CANCEL (1ULL << 33)
#define PAD_LR_START (1ULL << 34)
#define PAD_LRA_START (1ULL << 35)
#define PAD_ANY_UP (1ULL << 36)
#define PAD_ANY_DOWN (1ULL << 37)
#define PAD_ANY_LEFT (1ULL << 38)
#define PAD_ANY_RIGHT (1ULL << 39)
#endif


// Not declared by aurora's pad.h.
void PADSetSamplingRate(u32 msec);

#endif
