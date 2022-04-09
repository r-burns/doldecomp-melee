#include "grtdrmario.h"

#include <melee/gr/stage.h>

static StageCallbacks lbl_803E8850[4] = {
    {
        lbl_80220698,
        lbl_802206C4,
        lbl_802206CC,
        lbl_802206D0,
    }, {
        lbl_80220764,
        lbl_802207B4,
        lbl_802207BC,
        lbl_802207DC,
    }, {
        lbl_802206D4,
        lbl_80220724,
        lbl_8022072C,
        lbl_80220760,
        0xC0000000,
    }
};

StageData lbl_803E88AC = {
    0x0000002C,
    lbl_803E8850,
    "/GrTDr.dat",
    lbl_80220510,
    func_8022050C,
    lbl_80220580,
    lbl_80220584,
    lbl_802205A8,
    lbl_802207E0,
    lbl_802207E8,
    0x00000001,
};

static void func_8022050C()
{
}

static void lbl_80220510(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_802205B0(0);
    func_802205B0(1);
    func_802205B0(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}


static void lbl_80220580()
{
}

static void lbl_80220584(void)
{
    func_801CAE04(0);
}

static s32 lbl_802205A8(void)
{
    return 0;
}

static HSD_GObj* func_802205B0(int id)
{
    Map* gp;
    HSD_GObj* gobj;
    StageCallbacks* cb = &lbl_803E8850[id];
    gobj = func_801C14D0(id);
    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, func_801C5DB0, 3, 0);
        if (cb->callback3 != NULL) {
            gp->x1C_callback = cb->callback3;
        }
        if (cb->callback0 != NULL) {
            cb->callback0(gobj);
        }
        if (cb->callback2 != NULL) {
            func_8038FD54(gobj, cb->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grtdrmario.c", 204, id);
    }
    return gobj;
}

static void lbl_80220698(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 lbl_802206C4(void)
{
    return 0;
}

static void lbl_802206CC(HSD_GObj*)
{
}

static void lbl_802206D0(void)
{
}

static void lbl_802206D4(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* gp = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 lbl_80220724()
{
    return 0;
}

static void lbl_8022072C(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_80220760()
{
}

static void lbl_80220764(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_802207B4()
{
    return 0;
}

static void lbl_802207BC(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void lbl_802207DC()
{
}

static BOOL lbl_802207E0()
{
    return FALSE;
}

static BOOL lbl_802207E8()
{
    return TRUE;
}
