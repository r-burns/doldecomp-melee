#ifndef MELEE_COMPAT_DOLPHIN_CARD_H
#define MELEE_COMPAT_DOLPHIN_CARD_H

#include_next <dolphin/card.h>

#ifndef MELEE_COMPAT_CARD_DECLS
#define MELEE_COMPAT_CARD_DECLS

// Aurora's CARD layer has no format support (it works against Dolphin .gci /
// .raw files, which are already formatted).
s32 CARDFormatAsync(s32 chan, CARDCallback callback);

// original dolphin SDK did not have the parameters for the game ID
#define CARDInit() CARDInit("GALE", "01")

#endif
#endif
