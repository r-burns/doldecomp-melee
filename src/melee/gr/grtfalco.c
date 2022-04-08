#include "grtfalco.h"

extern StageInfo stage_info;

struct {
    BOOL unk0;
    BOOL unk4;
    BOOL unk8;
    BOOL unkC;
}* lbl_804D6AF8;

static StageCallbacks lbl_803E8918[4] = {
    {
        lbl_80220984,
        lbl_802209B0,
        lbl_802209B8,
        lbl_802209BC,
    },
    {
        lbl_80220A50,
        lbl_80220AA0,
        lbl_80220AA8,
        lbl_80220AC8,
    },
    {
        lbl_802209C0,
        lbl_80220A10,
        lbl_80220A18,
        lbl_80220A4C,
        0xC0000000,
    }
};

StageData lbl_803E8974 = {
    0x0000002D,
    lbl_803E8918,
    "/GrTFc.dat",
    lbl_802207F4,
    func_802207F0,
    lbl_8022086C,
    lbl_80220870,
    lbl_80220894,
    lbl_80220ACC,
    lbl_80220B78,
    0x00000001,
};

static void func_802207F0()
{
}

static void lbl_802207F4(void)
{
    lbl_804D6AF8 = func_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    ;
    func_8022089C(0);
    func_8022089C(1);
    func_8022089C(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void lbl_8022086C()
{
}

static void lbl_80220870()
{
    func_801CAE04(0);
}

static s32 lbl_80220894()
{
    return 0;
}

static HSD_GObj* func_8022089C(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E8918[arg0];
    gobj = func_801C14D0(arg0);
    if (gobj != NULL) {
        Map* map = gobj->user_data;
        map->x8_callback = NULL;
        map->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            map->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            func_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 201, arg0);
    }
    return gobj;
}

static void lbl_80220984(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_802209B0()
{
    return 0;
}

static void lbl_802209B8()
{
}

static void lbl_802209BC()
{
}

static void lbl_802209C0(HSD_GObj* gobj)
{
    int unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_80220A10()
{
    return 0;
}

static void lbl_80220A18(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_80220A4C()
{
}

static void lbl_80220A50(HSD_GObj* gobj)
{
    int unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_80220AA0()
{
    return 0;
}

static void lbl_80220AA8(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void lbl_80220AC8()
{
}

static BOOL lbl_80220ACC(s32 arg0)
{
    s32 tmp;
    s32 tmp_2;

    if (arg0 != -1) {
        tmp = func_80056B6C(arg0);
        if (tmp != -1 && tmp == 0) {
            tmp_2 = func_80054C6C(arg0);
            if (tmp_2 == 1) {
                return lbl_804D6AF8->unk0;
            }
            if (tmp_2 == 2) {
                return lbl_804D6AF8->unk4;
            }
            if (tmp_2 == 4) {
                return lbl_804D6AF8->unk8;
            }
            if (tmp_2 == 8) {
                return lbl_804D6AF8->unkC;
            }
            return FALSE;
        }
    }
    return FALSE;
}

static BOOL lbl_80220B78()
{
    return TRUE;
}
