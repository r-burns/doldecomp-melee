#include "grtfox.h"

extern StageInfo stage_info;

struct {
    BOOL unk0;
    BOOL unk4;
    BOOL unk8;
    BOOL unkC;
}* lbl_804D6B00;

static StageCallbacks lbl_803E89D8[4] = {
    {
        lbl_80220D14,
        lbl_80220D40,
        lbl_80220D48,
        lbl_80220D4C,
    },
    {
        lbl_80220DE0,
        lbl_80220E30,
        lbl_80220E38,
        lbl_80220E58,
    },
    {
        lbl_80220D50,
        lbl_80220DA0,
        lbl_80220DA8,
        lbl_80220DDC,
        0xC0000000,
    },
};

StageData lbl_803E8A34 = {
    0x0000002E,
    lbl_803E89D8,
    "/GrTFx.dat",
    lbl_80220B84,
    func_80220B80,
    lbl_80220BFC,
    lbl_80220C00,
    lbl_80220C24,
    lbl_80220E5C,
    lbl_80220F08,
    0x00000001,
};

static void func_80220B80()
{
}

static void lbl_80220B84(void)
{
    lbl_804D6B00 = func_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_80220C2C(0);
    func_80220C2C(1);
    func_80220C2C(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void lbl_80220BFC()
{
}

static void lbl_80220C00(void)
{
    func_801CAE04(0);
}

static s32 lbl_80220C24(void)
{
    return 0;
}

static HSD_GObj* func_80220C2C(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E89D8[arg0];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 203, arg0);
    }
    return gobj;
}

static void lbl_80220D14(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_80220D40(void)
{
    return 0;
}

static void lbl_80220D48()
{
}

static void lbl_80220D4C()
{
}

static void lbl_80220D50(HSD_GObj* gobj)
{
    int unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_80220DA0(void)
{
    return 0;
}

static void lbl_80220DA8(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_80220DDC()
{
}

static void lbl_80220DE0(HSD_GObj* gobj)
{
    int unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_80220E30(void)
{
    return 0;
}

static void lbl_80220E38(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void lbl_80220E58()
{
}

static BOOL lbl_80220E5C(s32 arg0)
{
    s32 tmp;
    s32 result;

    if (arg0 != -1) {
        tmp = func_80056B6C(arg0);
        if (tmp != -1 && tmp == 1) {
            result = func_80054C6C(arg0);
            if (result == 1) {
                return lbl_804D6B00->unk0;
            }
            if (result == 2) {
                return lbl_804D6B00->unk4;
            }
            if (result == 4) {
                return lbl_804D6B00->unk8;
            }
            if (result == 8) {
                return lbl_804D6B00->unkC;
            }
            return FALSE;
        }
    }
    return FALSE;
}

static BOOL lbl_80220F08()
{
    return TRUE;
}
