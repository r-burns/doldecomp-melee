#ifndef DOLPHIN_OS_OSFONT_H
#define DOLPHIN_OS_OSFONT_H

#include <Runtime/platform.h>

typedef enum {
    OS_FONT_ENCODE_CP1252,
    OS_FONT_ENCODE_SJIS,
} OSFontEncode;

u16 OSGetFontEncode(void);

#endif // DOLPHIN_OS_OSFONT_H
