#include "grtclink.h"

extern StageInfo stage_info;

static StageCallbacks lbl_803E86D0[4] = {
    {
        lbl_802200D0,
        lbl_802200FC,
        lbl_80220104,
        lbl_80220108,
    },
    {
        lbl_8022019C,
        lbl_802201EC,
        lbl_802201F4,
        lbl_80220214,
    },
    {
        lbl_8022010C,
        lbl_8022015C,
        lbl_80220164,
        lbl_80220198,
        0xC0000000,
    },
};

StageData lbl_803E872C = {
    0x0000002A,
    lbl_803E86D0,
    "/GrTCl.dat",
    lbl_8021FF48,
    func_8021FF44,
    lbl_8021FFB8,
    lbl_8021FFBC,
    lbl_8021FFE0,
    lbl_80220218,
    lbl_80220220,
    0x00000001,
};

static void func_8021FF44()
{
}

static void lbl_8021FF48()
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_8021FFE8(0);
    func_8021FFE8(1);
    func_8021FFE8(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void lbl_8021FFB8()
{
}

static void lbl_8021FFBC()
{
    func_801CAE04(0);
}

static s32 lbl_8021FFE0()
{
    return 0;
}

static HSD_GObj* func_8021FFE8(s32 arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &lbl_803E86D0[arg0];
    gobj = func_801C14D0(arg0);
    if (gobj != NULL) {
        Map* map;
        map = gobj->user_data;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, arg0);
    }
    return gobj;
}

static void lbl_802200D0(HSD_GObj* gobj)
{
    Map* map = gobj->user_data;
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_802200FC()
{
    return 0;
}

static void lbl_80220104()
{
}

static void lbl_80220108()
{
}

static void lbl_8022010C(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_8022015C()
{
    return 0;
}

static void lbl_80220164(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_80220198()
{
}

static void lbl_8022019C(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_802201EC()
{
    return 0;
}

static void lbl_802201F4(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void lbl_80220214()
{
}

static BOOL lbl_80220218(s32)
{
    return FALSE;
}

static BOOL lbl_80220220(Vec*, s32, struct _HSD_JObj*)
{
    return TRUE;
}
