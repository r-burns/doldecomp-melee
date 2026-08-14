// Out-of-line definitions for the tree's header `inline` functions.
//
// mwcc emits one shared definition for a plain `inline` function in a header.
// C99 says the opposite: an inline definition provides no external definition,
// so every call from a TU that did not inline it is left undefined at link
// time.

#include <melee/ft/inlines.h>
#include <melee/gm/inlines.h>
#include <melee/vi/vi.h>

#include <baselib/jobj.h>
#include <baselib/lobj.h>

#include <math_ppc.h>

// ctype.h and sqrtf are not listed here: melee_compat's replacements for those
// two headers make them `static inline`, so each TU keeps its own copy and no
// external definition is wanted.

extern float sqrtf_accurate(float x);

extern u8 HSD_LObjGetPriority(HSD_LObj* lobj);
extern void HSD_JObjSetupMatrix(HSD_JObj* jobj);
extern s32 fn_801A7FB4_inline(void);
extern s32 fn_801A7FB4_inline2(void);
extern CommandInfo* getCmdScript(Fighter* fp);
extern void vi_RunCamera(HSD_GObj* gobj, u8 erase_colors[4], u64 prio);
