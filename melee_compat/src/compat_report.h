#ifndef MELEE_COMPAT_REPORT_H
#define MELEE_COMPAT_REPORT_H

#include <dolphin/os.h>

// Report the first call to an unimplemented entry point, then shut up
#define COMPAT_STUB()                                                         \
    do {                                                                      \
        static int _reported = 0;                                             \
        if (!_reported) {                                                     \
            _reported = 1;                                                    \
            OSReport("melee_compat: stub %s\n", __func__);                    \
        }                                                                     \
    } while (0)

#endif
