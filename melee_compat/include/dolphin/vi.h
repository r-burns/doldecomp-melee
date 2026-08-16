#ifndef MELEE_COMPAT_DOLPHIN_VI_H
#define MELEE_COMPAT_DOLPHIN_VI_H

#include_next <dolphin/vi.h>

#ifndef MELEE_COMPAT_VI_DECLS
#define MELEE_COMPAT_VI_DECLS

// Rounds a framebuffer width up to the hardware's stride granularity.
// Not declared by aurora's vi.h.
u32 VIPadFrameBufferWidth(u32 width);

#endif
#endif
