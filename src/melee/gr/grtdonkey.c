#include "grtdonkey.h"
#include "stage.h"

static StageCallbacks lbl_803E8790[4] = {
    {
        lbl_802203B4,
        lbl_802203E0,
        lbl_802203E8,
        lbl_802203EC,
    }, {
        lbl_80220480,
        lbl_802204D0,
        lbl_802204D8,
        lbl_802204F8,
    }, {
        lbl_802203F0,
        lbl_80220440,
        lbl_80220448,
        lbl_8022047C,
        0xC0000000,
    },
};

StageData lbl_803E87EC = {
    0x0000002B,
    lbl_803E8790,
    "/GrTDk.dat",
    lbl_8022022C,
    func_80220228,
    lbl_8022029C,
    lbl_802202A0,
    lbl_802202C4,
    lbl_802204FC,
    lbl_80220504,
    0x00000001,
};

static void func_80220228()
{
}

static void lbl_8022022C(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_802202CC(0);
    func_802202CC(1);
    func_802202CC(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void lbl_8022029C()
{
}

static void lbl_802202A0(void)
{
    func_801CAE04(0);
}

static s32 lbl_802202C4(void)
{
    return 0;
}

static HSD_GObj* func_802202CC(int id)
{
    HSD_GObj* gobj;
    Map* gp;
    StageCallbacks* cb = &lbl_803E8790[id];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 195, id);
    }
    return gobj;
}

static void lbl_802203B4(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 lbl_802203E0(void)
{
    return 0;
}

static void lbl_802203E8(HSD_GObj*)
{
}

static void lbl_802203EC(void)
{
}

static void lbl_802203F0(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_80220440()
{
    return 0;
}

static void lbl_80220448(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_8022047C()
{
}

static void lbl_80220480(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_802204D0()
{
    return 0;
}

static void lbl_802204D8(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void lbl_802204F8()
{
}

static BOOL lbl_802204FC(s32)
{
    return FALSE;
}

static BOOL lbl_80220504(Vec*, s32, struct _HSD_JObj*)
{
    return TRUE;
}
