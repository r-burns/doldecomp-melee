#ifndef _vi_h_
#define _vi_h_

#include <Runtime/platform.h>

typedef enum {
    VI_TV_FMT_NTSC,
    VI_TV_FMT_PAL,
    VI_TV_FMT_MPAL,
    VI_TV_FMT_DEBUG,
} ViTvFormat;

extern vu16 VI_DTV_STATUS AT_ADDRESS(0xCC00206E);

s32 VIGetTvFormat(void);
void VIConfigure(s32);
void VIFlush(void);
void VISetNextFrameBuffer(s32);
void VIWaitForRetrace(void);
void VIInit(void);

#endif
