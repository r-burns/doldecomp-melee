#include <Runtime/platform.h>

#include <dolphin/os/OSFont.h>

#include <dolphin/vi/vi.h>

static u16 FontEncode = -1;

u16 OSGetFontEncode(void)
{
    if (FontEncode <= 1) {
        return FontEncode;
    }

    switch (*(u32*) 0x800000CC) {
    case VI_TV_FMT_NTSC:
        FontEncode = VI_DTV_STATUS & 2 ? OS_FONT_ENCODE_SJIS
                                       : OS_FONT_ENCODE_CP1252;
        break;
    case VI_TV_FMT_PAL:
    case VI_TV_FMT_MPAL:
    case VI_TV_FMT_DEBUG:
    default:
        FontEncode = OS_FONT_ENCODE_CP1252;
    }

    return FontEncode;
}
