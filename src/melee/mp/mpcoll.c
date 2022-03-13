#include <dolphin/types.h>
#include <melee/ft/fighter.h>

extern s32 lbl_804D4A08;

extern s32 func_80086960(HSD_GObj*);
extern u8 func_80086BE0(HSD_GObj*);
extern s32 func_800874BC(HSD_GObj*);

s32 lbl_804D64AC;
s32 lbl_804D64A8;
s32 lbl_804D64A4;
s32 lbl_804D64A0;
s32 lbl_804D649C;
s32 lbl_804D6498;
s32 lbl_804D6494;
s32 lbl_804D6490;
s32 lbl_804D648C;
s32 lbl_804D6488;


void func_80041C78(void)
{
    lbl_804D64A0 = 0;
    lbl_804D64A4 = 0;
    lbl_804D64A8 = 0;
}

/* static */ void func_80041C8C(CollData* cd)
{
    u32 unused[2];

    lbl_804D64A0 = 0;
    lbl_804D64A4 = 0;
    if (lbl_804D4A08 >= 3) {
        if (!(cd->topN_Curr.x < 45000.0f) || !(cd->topN_Curr.x > -45000.0f) ||
            !(cd->topN_Curr.y < 45000.0f) || !(cd->topN_Curr.y > -45000.0f)) {

            if (func_80086960(cd->gobj) != 0) {
                OSReport("%s:%d: Error: mpCollPrev() pos(%f,%f) player=%d ms=%d\n",
                    "mpcoll.c", 203, cd->topN_Curr.x, cd->topN_Curr.y,
                    func_80086BE0(cd->gobj), func_800874BC(cd->gobj));
            } else {
                OSReport("%s:%d: Error: mpCollPrev() pos(%f,%f) gobj_id=%d\n",
                    "mpcoll.c", 212, cd->gobj->classifier,
                    cd->topN_Curr.x, cd->topN_Curr.y
                    );
                if (cd->gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(cd->gobj));
                }
            }
            __assert("mpcoll.c", 228, "0");
        }
    }
    cd->topN_Proj = cd->topN_Curr;
}

inline void clamp_above(f32* value, f32 min)
{
    if (*value < min) {
        *value = min;
    }
}

inline void clamp_below(f32* value, f32 max)
{
    if (*value > max) {
        *value = max;
    }
}

/* static */ void func_80041DD0(CollData* cd, u8 flags)
{
    f32 arg1, arg2, arg3, arg4;

    arg1 = cd->xA4_ecbCurrCorrect.left.x + cd->topN_Curr.x;
    clamp_below(&arg1, cd->xC4_ecbPrev.left.x + cd->topN_CurrCorrect.x);

    arg3 = cd->xA4_ecbCurrCorrect.right.x + cd->topN_Curr.x;
    clamp_above(&arg3, cd->xC4_ecbPrev.right.x + cd->topN_CurrCorrect.x);

    arg2 = cd->xA4_ecbCurrCorrect.bottom.y + cd->topN_Curr.y;
    clamp_below(&arg2, cd->xC4_ecbPrev.bottom.y + cd->topN_CurrCorrect.y);

    arg4 = cd->xA4_ecbCurrCorrect.top.y + cd->topN_Curr.y;
    clamp_above(&arg4, cd->xC4_ecbPrev.top.y + cd->topN_CurrCorrect.y);

    if (flags & 0b100) {
        f32 x54 = cd->x54;
        f32 tmp = 0.5f * cd->x5C;
        f32 offset;

        arg3 += x54;
        arg1 -= x54;

        clamp_below(&arg2, cd->x58 - tmp + cd->topN_Curr.y);
        clamp_below(&arg2, cd->x58 - tmp + cd->topN_CurrCorrect.y);

        offset = cd->x58 + tmp;
        clamp_above(&arg4, cd->topN_Curr.y + offset);
        clamp_above(&arg4, cd->topN_CurrCorrect.y + offset);
    }

    func_800588D0(arg1, arg2, arg3, arg4);
}

// NOTE: these must be put here!
// otherwise their order in sda2 will be wrong :(
const u32 lbl_804D7F9C = 0xFF7FFFFF;
const u32 lbl_804D7FA0 = 0x7F7FFFFF;

// CollDataInit
void func_80041EE4(CollData* cd)
{
    cd->gobj = NULL;
    cd->x34_flags.b0 = 1;
    cd->x34_flags.b6 = 0;
    cd->x34_flags.b7 = 0;
    cd->x35_flags.b0 = 1;
    cd->x34_flags.b1234 = 0;
    cd->x134_envFlags = 0;
    cd->x130_flags = 0;
    cd->topN_CurrCorrect = cd->topN_Curr;
    cd->topN_Prev = cd->topN_Curr;
    cd->topN_Proj = cd->topN_Curr;
    cd->x3C = -1;
    cd->x40 = -1;
    cd->x44 = -1;
    cd->x14C_groundIndex = -1;
    cd->ground_info = 0;
    cd->x154_groundNormal.x = 0.0f;
    cd->x154_groundNormal.y = 1.0f;
    cd->x154_groundNormal.z = 0.0f;
    cd->ceil_index = -1;
    cd->ceil_unk = 0;
    cd->ceil_slope.x = 0.0f;
    cd->ceil_slope.y = -1.0f;
    cd->ceil_slope.z = 0.0f;
    cd->x174_leftwall_index = -1;
    cd->leftwall_unk = 0;
    cd->leftwall_slope.x = 0.0f;
    cd->leftwall_slope.y = 1.0f;
    cd->leftwall_slope.z = 0.0f;
    cd->x160_rightwall_index = -1;
    cd->rightwall_unk = 0;
    cd->rightwall_slope.x = 0.0f;
    cd->rightwall_slope.y = -1.0f;
    cd->rightwall_slope.z = 0.0f;
    cd->x38 = lbl_804D64AC;
    cd->x50 = 0.0f;
    cd->x48 = -1;
    cd->x4C = -1;
    cd->x54 = 0.0f;
    cd->x58 = 0.0f;
    cd->x5C = 0.0f;
    func_8000C160(&cd->xA4_ecbCurrCorrect, sizeof(Ecb));
    func_8000C160(&cd->xC4_ecbPrev, sizeof(Ecb));
    func_8000C160(&cd->xE4_ecbProj, sizeof(Ecb));
    func_8000C160(&cd->x104, 11 * 4);
    func_8000C160(&cd->x84_ecbCurr, sizeof(Ecb));
    func_8000C160(&cd->x64_ecbUnk, sizeof(Ecb));
}

void func_80042078(CollData* cd, HSD_GObj* gobj,
        s32 arg1, void* arg2, void* arg3, void* arg4,
        void* arg5, void* arg6, void* arg7, f32 arg9)
{
    cd->gobj = gobj;
    cd->x104 = 1;
    cd->type1.x108 = arg1;
    cd->type1.x10C[0] = arg2;
    cd->type1.x10C[1] = arg3;
    cd->type1.x10C[2] = arg4;
    cd->type1.x10C[3] = arg5;
    cd->type1.x10C[4] = arg6;
    cd->type1.x10C[5] = arg7;
    cd->type1.x124 = arg9;
    cd->type1.x128 = 10.0f;
    cd->type1.x12C = 10.0f;
    if (cd->x34_flags.b0) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 8.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 4.0f;
        cd->xA4_ecbCurrCorrect.right.y = 4.0f;
        cd->xA4_ecbCurrCorrect.left.x = -4.0f;
        cd->xA4_ecbCurrCorrect.left.y = 4.0f;
        cd->xA4_ecbCurrCorrect = cd->xA4_ecbCurrCorrect;
        cd->xC4_ecbPrev = cd->xA4_ecbCurrCorrect;
        cd->xE4_ecbProj = cd->xA4_ecbCurrCorrect;
        cd->x64_ecbUnk  = cd->xA4_ecbCurrCorrect;
        cd->x84_ecbCurr = cd->xA4_ecbCurrCorrect;
    }
    cd->x36 = -1;
    cd->x50 = 0.0f;
}

void func_8004220C(CollData* cd, HSD_GObj* gobj, f32 arg1, f32 arg2, f32 arg3, f32 arg4)
{
    cd->gobj = gobj;
    cd->x104 = 2;
    cd->type2.x108 = arg1;
    cd->type2.x10C = arg2;
    cd->type2.x110 = arg3;
    cd->type2.x114 = arg4;
    cd->type2.x118 = 0.0f;
    if (cd->x34_flags.b0) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 8.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 4.0f;
        cd->xA4_ecbCurrCorrect.right.y = 4.0f;
        cd->xA4_ecbCurrCorrect.left.x = -4.0f;
        cd->xA4_ecbCurrCorrect.left.y = 4.0f;
        cd->xC4_ecbPrev = cd->xA4_ecbCurrCorrect;
        cd->xE4_ecbProj = cd->xA4_ecbCurrCorrect;
        cd->x64_ecbUnk = cd->xA4_ecbCurrCorrect;
        cd->x84_ecbCurr = cd->xA4_ecbCurrCorrect;
    }
    cd->x36 = -1;
}

void func_80042374(CollData* cd, f32 arg1, f32 arg2, f32 arg3)
{
    cd->x54 = arg1;
    cd->x58 = arg2;
    cd->x5C = arg3;
}

inline f32 fabsf(f32 x)
{
    if (x < 0.0f) {
        return -x;
    }
    return x;
}

/* static */ void func_80042384(CollData* cd)
{
    f32 tmp, tmp2;

    if (fabsf(cd->x84_ecbCurr.top.y - cd->x84_ecbCurr.bottom.y) < 1.0f) {
        cd->x84_ecbCurr.top.y += 1.0f;
        tmp = 0.5f * (cd->x84_ecbCurr.top.y + cd->x84_ecbCurr.bottom.y);
        cd->x84_ecbCurr.left.y = tmp;
        cd->x84_ecbCurr.right.y = tmp;
    }
    if (cd->x84_ecbCurr.top.y < 1.0f) {
        cd->x84_ecbCurr.top.y = 1.0f;
    }
    if (cd->x84_ecbCurr.left.x > -1.0f) {
        cd->x84_ecbCurr.left.x = -1.0f;
    }
    if (cd->x84_ecbCurr.right.x < 1.0f) {
        cd->x84_ecbCurr.right.x = 1.0f;
    }
    if (cd->x84_ecbCurr.top.y < cd->x84_ecbCurr.bottom.y) {
        cd->x84_ecbCurr.top.y = 1.0f + cd->x84_ecbCurr.bottom.y;
    }
    if (cd->x84_ecbCurr.right.y > cd->x84_ecbCurr.top.y ||
        cd->x84_ecbCurr.right.y < cd->x84_ecbCurr.bottom.y)
    {
        tmp = 0.5f * (cd->x84_ecbCurr.top.y + cd->x84_ecbCurr.bottom.y);
        cd->x84_ecbCurr.left.y = tmp;
        cd->x84_ecbCurr.right.y = tmp;
    }
    tmp = cd->x84_ecbCurr.top.y;
    tmp2 = cd->x84_ecbCurr.right.y;
    if (tmp - tmp2 < 0.001f ||
        tmp2 - cd->x84_ecbCurr.bottom.y < 0.001f)
    {
        cd->x84_ecbCurr.right.y = 0.5f * (tmp + cd->x84_ecbCurr.bottom.y);
    }
    tmp = cd->x84_ecbCurr.top.y;
    tmp2 = cd->x84_ecbCurr.left.y;
    if (tmp - tmp2 < 0.001f ||
        tmp2 - cd->x84_ecbCurr.bottom.y < 0.001f)
    {
        cd->x84_ecbCurr.left.y = 0.5f * (tmp + cd->x84_ecbCurr.bottom.y);
    }
}

inline void update_min_max(f32* min, f32* max, f32 val)
{
    if (*min > val) {
        *min = val;
    } else if (*max < val) {
        *max = val;
    }
}

/* static */ void func_800424DC(CollData* cd, u32 flags)
{
    Vec3 vec;
    f32 left_x, bottom_y;
    f32 right_x, top_y;
    f32 dx, dy;

    f32 phi_f1, phi_f2;
    f32 mid_y;
    f32 tmpval;

    if (cd->x130_flags & 0b100000) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 0.0f;
        cd->xA4_ecbCurrCorrect.right.y = 0.0f;
        cd->xA4_ecbCurrCorrect.left.x = 0.0f;
        cd->xA4_ecbCurrCorrect.left.y = 0.0f;
        cd->x130_flags &= ~0b100000;
    }
    cd->xE4_ecbProj = cd->xA4_ecbCurrCorrect;

    // Loop through all collision data joints,
    // expanding the ECB to contain them all
    {
        f32 temp_x = cd->topN_Curr.x;
        f32 temp_y = cd->topN_Curr.y;
        func_8000B1CC(cd->type1.x10C[0], NULL, &vec);
        left_x = right_x = vec.x - temp_x;
        bottom_y = top_y = vec.y - temp_y;

        #define EXPAND_ECB_FOR(joint) \
        func_8000B1CC(joint, NULL, &vec);\
        dx = vec.x - temp_x;\
        dy = vec.y - temp_y;\
        update_min_max(&left_x, &right_x, dx);\
        update_min_max(&bottom_y, &top_y, dy);

        EXPAND_ECB_FOR(cd->type1.x10C[1]);
        EXPAND_ECB_FOR(cd->type1.x10C[2]);
        EXPAND_ECB_FOR(cd->type1.x10C[3]);
        EXPAND_ECB_FOR(cd->type1.x10C[4]);
        EXPAND_ECB_FOR(cd->type1.x10C[5]);
    }

    if (!(flags & 0b100)) {
        left_x -= 2.0f;
        right_x += 2.0f;
        bottom_y -= 2.0f;
        top_y += 2.0f;
    }

    phi_f1 = 4.0f > cd->type1.x12C ? 4.0f : cd->type1.x12C;
    phi_f2 = fabsf(right_x - left_x);

    if (phi_f2 < phi_f1) {
        right_x = 0.5f * phi_f2;
        left_x = -right_x;
    }

    phi_f1 = 4.0f > cd->type1.x128 ? 4.0f : cd->type1.x128;
    phi_f2 = fabsf(top_y - bottom_y);

    if (phi_f2 < phi_f1) {
        tmpval = 0.5f * phi_f2;
        mid_y = 0.5f * (top_y + bottom_y);
        top_y = mid_y + tmpval;
        bottom_y = mid_y - tmpval;
    }

    if (flags & 0b1000) {
        left_x = -1.0f;
        right_x = +1.0f;
    } else {
        right_x = right_x < 2.0f ? 2.0f : right_x;
        left_x = left_x > -2.0f ? -2.0f : left_x;
    }

    if (flags & 1) {
        bottom_y = 0.0f;
        if (flags & 0b10000) {
            top_y = 2.0f;
        }
    } else {
        if (bottom_y < 0.0f) {
            bottom_y = 0.0f;
        }
        if (flags & 0b10000) {
            mid_y = 0.5f * (bottom_y + top_y);
            bottom_y = mid_y - 1.0f;
            top_y = mid_y + 1.0f;
            if (bottom_y < 0.0f) {
                bottom_y = 0.0f;
                top_y = 2.0f;
            }
        }
    }

    cd->x84_ecbCurr.top.x = 0.0f;
    cd->x84_ecbCurr.top.y = top_y;
    cd->x84_ecbCurr.bottom.x = 0.0f;
    cd->x84_ecbCurr.bottom.y = bottom_y;
    cd->x84_ecbCurr.right.x = right_x;
    cd->x84_ecbCurr.right.y = cd->type1.x124 + 0.5f * (bottom_y + top_y);
    cd->x84_ecbCurr.left.x = left_x;
    cd->x84_ecbCurr.left.y = cd->type1.x124 + 0.5f * (bottom_y + top_y);
    cd->x34_flags.b0 = 0;
}
