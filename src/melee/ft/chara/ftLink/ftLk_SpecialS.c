#include <platform.h>
#include "ft/forward.h"
#include <baselib/forward.h>

#include "ftLk_SpecialS.h"

#include "ftLk_Init.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <math.h>
#include <placeholder.h>
#include <trigf.h>

typedef enum cmd_var_idx {
    cmd_unk0_bool,
    cmd_specials2_anim_bool,
    cmd_unk2,
    cmd_unk3,
} cmd_var_idx;

/* 0EBF2C */ static void on21EC(HSD_GObj* gobj);
/* 0EC0C4 */ static float calcAnglePos(HSD_GObj* gobj, Vec3* pos, float dist);
/* 0EC210 */ static void onAccessory4(HSD_GObj* gobj);

void on21EC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fabs_inline(fp->input.lstick.x) >= p_ftCommonData->x3C &&
        fp->x673 < p_ftCommonData->x40 + p_ftCommonData->x44)
    {
        fp->x2070.x2072_b4 = true;
        fp->fv.lk.x4 = true;
    } else {
        fp->fv.lk.x4 = false;
    }
}

bool ftLk_SepcialS_Get2219b5(HSD_GObj* gobj)
{
    return GET_FIGHTER(gobj)->x2219_b5;
}

bool ftLk_SpecialS_Is2071b0_5to13(HSD_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->x2070.x2071_b0_3) {
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        return true;
    default:
        return false;
    }
}

bool ftLk_SpecialS_Is2071b0_1to13(HSD_GObj* gobj)
{
    switch (GET_FIGHTER(gobj)->x2070.x2071_b0_3) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        return true;
    default:
        return false;
    }
}

void ftLk_SpecialS_RemoveBoomerang0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.lk.used_boomerang = false;
    fp->fv.lk.boomerang_gobj = NULL;
    ftLk_Init_BoomerangExists(gobj);
}

void ftLk_SpecialS_RemoveBoomerang1(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.lk.boomerang_gobj != NULL) {
        it_802A07B4(fp->fv.lk.boomerang_gobj);
        fp->fv.lk.used_boomerang = false;
        fp->fv.lk.boomerang_gobj = NULL;
        ftLk_Init_BoomerangExists(gobj);
    }
}

/**
 * @returns Some angle.
 * @param[out] pos Some offset based on the returned angle,
 *                 #Fighter::facing_dir, and @p dist.
 */
float calcAnglePos(HSD_GObj* gobj, Vec3* pos, float dist)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    float angle = 0;
    ftLk_DatAttrs* da = fp->dat_attrs;
    float lstick_y = fp->input.lstick.y;
    float da_x18_mul_x1C = da->x18 * da->x1C;
    if (fabs_inline(lstick_y) > da->x14) {
        float lstick_x = fp->input.lstick.x;
        if (lstick_x < 0) {
            lstick_x = -lstick_x;
        }
        angle = atan2f(lstick_y, lstick_x);
        if (angle > da_x18_mul_x1C) {
            angle = da_x18_mul_x1C;
        } else {
            float neg_da_x18_mul_x1C = -da_x18_mul_x1C;
            if (angle < neg_da_x18_mul_x1C) {
                angle = neg_da_x18_mul_x1C;
            }
        }
    }
    pos->x = fp->facing_dir * (dist * cosf(angle));
    pos->y = fp->facing_dir * (dist * sinf(angle));
    pos->z = 0;
    if (fp->facing_dir == -1) {
        if (angle < 0) {
            angle = -M_PI - angle;
        } else {
            angle = +M_PI - angle;
        }
    }
    if (angle < 0) {
        angle += 2 * M_PI;
    }
    return angle;
}

void onAccessory4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLk_DatAttrs* da = fp->dat_attrs;
    if (ftCheckThrowB0(fp)) {
        Vec3 pos;
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                    NULL, &pos);
        {
            HSD_GObj* boomerang_gobj =
                it_802A013C(fp->facing_dir, gobj, &pos,
                            ftParts_8007500C(fp, FtPart_LThumbNb), da->x2C);
            fp->x1984_heldItemSpec = boomerang_gobj;
            fp->fv.lk.boomerang_gobj = boomerang_gobj;
            if (boomerang_gobj != NULL) {
                fp->fv.lk.used_boomerang = true;
                fp->cb.x21E8_callback_OnDeath3 = ftLk_800EAF38;
                fp->cb.x21DC_callback_OnTakeDamage = ftLk_800EAF58;
            }
        }
    }
    if (fp->cmd_vars[cmd_unk0_bool] && fp->fv.lk.boomerang_gobj != NULL &&
        it_8029FDBC(fp->fv.lk.boomerang_gobj))
    {
        Vec3 pos;
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif
        calcAnglePos(gobj, &pos, fp->fv.lk.x4 ? da->x20 : da->x24);
        it_802A0534(fp->fv.lk.boomerang_gobj, &pos);
        fp->cmd_vars[cmd_unk0_bool] = false;
        fp->cmd_vars[cmd_specials2_anim_bool] = false;
    }
}

static void doEnter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags.flags = 0;
    fp->cmd_vars[cmd_unk0_bool] = false;
    fp->cb.x21EC_callback = on21EC;
    if (fp->fv.lk.used_boomerang) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS1Empty, Ft_MF_None,
                                  NULL, 0, 1, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS1, Ft_MF_None, NULL, 0,
                                  1, 0);
    }
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = onAccessory4;
}

void ftLk_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags.flags = 0;
    fp->cmd_vars[cmd_unk0_bool] = false;
    fp->cb.x21EC_callback = on21EC;
    if (fp->fv.lk.used_boomerang) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS1Empty, Ft_MF_None,
                                  NULL, 0, 1, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS1, Ft_MF_None, NULL, 0,
                                  1, 0);
    }
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = onAccessory4;
}

/// @todo Share code with #ftLk_SpecialS_Enter. A simple inline won't work.
void ftLk_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags.flags = 0;
    fp->cmd_vars[cmd_unk0_bool] = 0;
    fp->cb.x21EC_callback = on21EC;
    if (fp->fv.lk.used_boomerang) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirS1Empty, Ft_MF_None,
                                  NULL, 0, 1, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirS1, Ft_MF_None, NULL,
                                  0, 1, 0);
    }
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = onAccessory4;
}

void ftLk_SpecialS2_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirS2, Ft_MF_None, NULL,
                                  0, 1, 0);
    } else {
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS2, Ft_MF_None, NULL, 0,
                                  1, 0);
    }
    fp->cb.x21DC_callback_OnTakeDamage = ftLk_800EAF58;
    ftAnim_8006EBA4(gobj);
}

void ftLk_SpecialS1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

static void doS2Anim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[cmd_specials2_anim_bool]) {
        if (fp->fv.lk.boomerang_gobj != NULL) {
            it_802A07B4(fp->fv.lk.boomerang_gobj);
        }
        fp->cmd_vars[cmd_specials2_anim_bool] = false;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
    }
}

void ftLk_SpecialS2_Anim(HSD_GObj* gobj)
{
    doS2Anim(gobj, ft_8008A2BC);
}

void ftLk_SpecialS1Empty_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftLk_SpecialAirS1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftLk_SpecialAirS2_Anim(HSD_GObj* gobj)
{
    doS2Anim(gobj, ft_800CC730);
}

void ftLk_SpecialAirS1Empty_Anim(HSD_GObj* gobj)
{
    ftLk_SpecialAirS1_Anim(gobj);
}

static inline bool checkBoomerangSomething(HSD_GObj* gobj)
{
    if (ft_80096540(gobj)) {
        return true;
    } else if (ftCo_Attack100_CheckInput(gobj)) {
        return true;
    } else if (ft_800D6824(gobj)) {
        return true;
    } else if (ft_800D68C0(gobj)) {
        return true;
    } else if (ft_80091A4C(gobj)) {
        return true;
    } else if (ftCo_Jump_CheckInput(gobj)) {
        return true;
    } else if (ftCo_Dash_CheckInput(gobj)) {
        return true;
    } else {
        return false;
    }
}

void ftLk_SpecialS2_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkBoomerangSomething(gobj) && fp->fv.lk.boomerang_gobj != NULL) {
        it_802A07B4(fp->fv.lk.boomerang_gobj);
    }
}

static bool checkAirBoomerangSomething(HSD_GObj* gobj)
{
    if (ft_8009665C(gobj)) {
        return true;
    } else if (ft_800CB870(gobj)) {
        return true;
    } else {
        return false;
    }
}

void ftLk_SpecialAirS2_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (checkAirBoomerangSomething(gobj) && fp->fv.lk.boomerang_gobj != NULL) {
        it_802A07B4(fp->fv.lk.boomerang_gobj);
    }
}

void ftLk_SpecialS1_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialS2_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialS1Empty_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftLk_SpecialAirS1_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftLk_SpecialAirS2_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftLk_SpecialAirS1Empty_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

static FtMotionId const coll_mf = Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                                  Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
                                  Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
                                  Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftLk_SpecialS1_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirS1, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
        fp->cb.x21BC_callback_Accessory4 = onAccessory4;
    }
}

void ftLk_SpecialS2_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082708(gobj)) {
        if (fp->fv.lk.boomerang_gobj != NULL) {
            it_802A07B4(fp->fv.lk.boomerang_gobj);
        }
        ft_800CC730(gobj);
    }
}

/// @todo Share code with #ftLk_SpecialS1_Coll.
void ftLk_SpecialS1Empty_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialAirS1Empty, coll_mf,
                                  NULL, fp->cur_anim_frame, 1, 0);
    }
}

void ftLk_SpecialAirS1_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS1, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
        fp->cb.x21BC_callback_Accessory4 = onAccessory4;
    }
}

void ftLk_SpecialAirS2_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj)) {
        if (fp->fv.lk.boomerang_gobj != NULL) {
            it_802A07B4(fp->fv.lk.boomerang_gobj);
        }
        ft_800D5BF8(gobj);
    }
}

void ftLk_SpecialAirS1Empty_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftLk_MS_SpecialS1Empty, coll_mf, NULL,
                                  fp->cur_anim_frame, 1, 0);
    }
}