#ifndef MELEE_COMPAT_DOLPHIN_GX_H
#define MELEE_COMPAT_DOLPHIN_GX_H

#include_next <dolphin/gx.h>

#ifndef MELEE_COMPAT_GX_DECLS
#define MELEE_COMPAT_GX_DECLS

// The GC SDK defines this as an alias of GX_CA_KONST; aurora omits it.
#ifndef GX_CA_ONE
#define GX_CA_ONE GX_CA_KONST
#endif

void GXSetTevClampMode(int tev_stage, int mode);
void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, f32 projmtx[4][4]);
void GXWaitDrawDone(void);
void GXMatrixIndex1u8(u8 index);

#endif
#endif
