#ifndef MELEE_COMPAT_DOLPHIN_TYPES_H
#define MELEE_COMPAT_DOLPHIN_TYPES_H

// aurora dolphin/types.h is missing ARRAY_SIZE

#include_next <dolphin/types.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#endif
