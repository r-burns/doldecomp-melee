#include "stage.h"
#include <sysdolphin/baselib/gobj.h>

HSD_GObj* func_8021F8E4(int id);
BOOL lbl_8021FB50(s32 x, HSD_GObj* gobj);

void func_8021FBE8();
extern void lbl_8021F9CC();
extern s32 lbl_8021F9F8();
extern void lbl_8021FA00();
extern void lbl_8021FA04();
extern void lbl_8021FAD4();
extern s32 lbl_8021FB24();
extern void lbl_8021FB2C();
extern void lbl_8021FB4C();
extern void lbl_8021FA34();
extern s32 lbl_8021FA94();
extern void lbl_8021FA9C();
extern void lbl_8021FAD0();

static StageCallbacks lbl_803E8548[4] = {
    {
        lbl_8021F9CC,
        lbl_8021F9F8,
        lbl_8021FA00,
        lbl_8021FA04,
    }, {
        lbl_8021FAD4,
        lbl_8021FB24,
        lbl_8021FB2C,
        lbl_8021FB4C,
    }, {
        lbl_8021FA34,
        lbl_8021FA94,
        lbl_8021FA9C,
        lbl_8021FAD0,
        0xC0000000
    },
};

void lbl_8021F844(void);
void func_8021F840();
void lbl_8021F8B4();
void lbl_8021F8B8();
s32 lbl_8021F8DC();
BOOL lbl_8021FC50();
BOOL lbl_8021FC58(Vec*, s32, struct _HSD_JObj*);

StageData lbl_803E85A4 = {
    0x00000028,
    lbl_803E8548,
    "/GrTMr.dat",
    lbl_8021F844,
    func_8021F840,
    lbl_8021F8B4,
    lbl_8021F8B8,
    lbl_8021F8DC,
    lbl_8021FC50,
    lbl_8021FC58,
    0x00000001,
};

static void func_8021F840()
{
}

static void lbl_8021F844(void)
{
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_8021F8E4(0);
    func_8021F8E4(1);
    func_8021F8E4(2);
    func_801C39C0();
    func_801C3BB4();
    func_801C4210();
    func_801C42AC();
}

static void lbl_8021F8B4()
{
}

static void lbl_8021F8B8(void)
{
    func_801CAE04(0);
}

static s32 lbl_8021F8DC(void)
{
    return 0;
}

static HSD_GObj* func_8021F8E4(int id)
{
    HSD_GObj* gobj;
    Map* gp;
    StageCallbacks* cb = &lbl_803E8548[id];
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 205, id);
    }
    return gobj;
}

static void lbl_8021F9CC(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    func_801C8138(gobj, gp->map_id, 0);
}

static s32 lbl_8021F9F8(void)
{
    return 0;
}

static void lbl_8021FA00(HSD_GObj*)
{
}

static void lbl_8021FA04(void)
{
}

static void lbl_8021FA08(HSD_GObj* gobj)
{
    func_800C07F8(gobj, 6, &lbl_8021FB50);
}

static void lbl_8021FA34(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* gp = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, gp->map_id);
    func_801C8138(gobj, gp->map_id, 0);
    func_801C10B8(gobj, lbl_8021FA08);
}

static s32 lbl_8021FA94()
{
    return 0;
}

static void lbl_8021FA9C(HSD_GObj* gobj)
{
    func_800115F4();
    func_801C2FE0(gobj);
}

static void lbl_8021FAD0()
{
}

static void lbl_8021FAD4(HSD_GObj* gobj)
{
    u32 unused[2];
    Map* map = gobj->user_data;
    func_801C2ED0(gobj->hsd_obj, map->map_id);
    func_801C8138(gobj, map->map_id, 0);
}

static s32 lbl_8021FB24()
{
    return FALSE;
}

static void lbl_8021FB2C(HSD_GObj* gobj)
{
    func_801C2FE0(gobj);
}

static void lbl_8021FB4C()
{
}

#ifdef NON_MATCHING
f32 func_80086B80(HSD_GObj*);

BOOL lbl_8021FB50(s32 x, HSD_GObj* gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    f32 temp_f1;
    f32 scale;
    u32 unused[1];

    scale = -120.0f * func_801C0498();
    func_80086644(gobj, &sp20);
    func_80086684(gobj, &sp14);
    if (sp20.y < scale && sp14.y > scale) {
        temp_f1 = func_80086B80(gobj) / 10.0f;
        sp20.y = scale;
        func_8021FBE8(&sp20, temp_f1);
        func_801C53EC(0x77A10);
    }
    return FALSE;
}
#else
extern void func_80086644();
extern void func_80086684();
extern void func_80086B80();
extern void func_801C53EC();
extern void func_8021FBE8();
const f32 lbl_804DBCB0 = -120;
asm BOOL lbl_8021FB50(s32 x, HSD_GObj* gobj)
{
    nofralloc
/* 8021FB50 0021C730  7C 08 02 A6 */	mflr r0
/* 8021FB54 0021C734  90 01 00 04 */	stw r0, 4(r1)
/* 8021FB58 0021C738  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8021FB5C 0021C73C  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 8021FB60 0021C740  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8021FB64 0021C744  7C 9F 23 78 */	mr r31, r4
/* 8021FB68 0021C748  4B FA 09 31 */	bl func_801C0498
/* 8021FB6C 0021C74C  C0 02 C2 D0 */	lfs f0, lbl_804DBCB0
/* 8021FB70 0021C750  38 7F 00 00 */	addi r3, r31, 0
/* 8021FB74 0021C754  38 81 00 20 */	addi r4, r1, 0x20
/* 8021FB78 0021C758  EF E0 00 72 */	fmuls f31, f0, f1
/* 8021FB7C 0021C75C  4B E6 6A C9 */	bl func_80086644
/* 8021FB80 0021C760  38 7F 00 00 */	addi r3, r31, 0
/* 8021FB84 0021C764  38 81 00 14 */	addi r4, r1, 0x14
/* 8021FB88 0021C768  4B E6 6A FD */	bl func_80086684
/* 8021FB8C 0021C76C  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 8021FB90 0021C770  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 8021FB94 0021C774  40 80 00 38 */	bge lbl_8021FBCC
/* 8021FB98 0021C778  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 8021FB9C 0021C77C  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 8021FBA0 0021C780  40 81 00 2C */	ble lbl_8021FBCC
/* 8021FBA4 0021C784  7F E3 FB 78 */	mr r3, r31
/* 8021FBA8 0021C788  4B E6 6F D9 */	bl func_80086B80
/* 8021FBAC 0021C78C  C0 02 C2 D4 */	lfs f0, 10.0f
/* 8021FBB0 0021C790  38 61 00 20 */	addi r3, r1, 0x20
/* 8021FBB4 0021C794  EC 21 00 24 */	fdivs f1, f1, f0
/* 8021FBB8 0021C798  D3 E1 00 24 */	stfs f31, 0x24(r1)
/* 8021FBBC 0021C79C  48 00 00 2D */	bl func_8021FBE8
/* 8021FBC0 0021C7A0  3C 60 00 07 */	lis r3, 0x00077A10@ha
/* 8021FBC4 0021C7A4  38 63 7A 10 */	addi r3, r3, 0x00077A10@l
/* 8021FBC8 0021C7A8  4B FA 58 25 */	bl func_801C53EC
lbl_8021FBCC:
/* 8021FBCC 0021C7AC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8021FBD0 0021C7B0  38 60 00 00 */	li r3, 0
/* 8021FBD4 0021C7B4  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 8021FBD8 0021C7B8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8021FBDC 0021C7BC  38 21 00 40 */	addi r1, r1, 0x40
/* 8021FBE0 0021C7C0  7C 08 03 A6 */	mtlr r0
/* 8021FBE4 0021C7C4  4E 80 00 20 */	blr 
}
#pragma peephole on
#endif

extern void func_801C96F8();
asm void func_8021FBE8()
{
    nofralloc
/* 8021FBE8 0021C7C8  7C 08 02 A6 */	mflr r0
/* 8021FBEC 0021C7CC  38 A3 00 00 */	addi r5, r3, 0
/* 8021FBF0 0021C7D0  90 01 00 04 */	stw r0, 4(r1)
/* 8021FBF4 0021C7D4  38 60 75 30 */	li r3, 0x7530
/* 8021FBF8 0021C7D8  38 80 00 1E */	li r4, 0x1e
/* 8021FBFC 0021C7DC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8021FC00 0021C7E0  DB E1 00 10 */	stfd f31, 0x10(r1)
/* 8021FC04 0021C7E4  FF E0 08 90 */	fmr f31, f1
/* 8021FC08 0021C7E8  4B FA 9A F1 */	bl func_801C96F8
/* 8021FC0C 0021C7EC  28 03 00 00 */	cmplwi r3, 0
/* 8021FC10 0021C7F0  41 82 00 2C */	beq lbl_8021FC3C
/* 8021FC14 0021C7F4  80 63 00 54 */	lwz r3, 0x54(r3)
/* 8021FC18 0021C7F8  C0 03 00 24 */	lfs f0, 0x24(r3)
/* 8021FC1C 0021C7FC  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8021FC20 0021C800  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8021FC24 0021C804  C0 03 00 28 */	lfs f0, 0x28(r3)
/* 8021FC28 0021C808  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8021FC2C 0021C80C  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 8021FC30 0021C810  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8021FC34 0021C814  EC 00 07 F2 */	fmuls f0, f0, f31
/* 8021FC38 0021C818  D0 03 00 2C */	stfs f0, 0x2c(r3)
lbl_8021FC3C:
/* 8021FC3C 0021C81C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8021FC40 0021C820  CB E1 00 10 */	lfd f31, 0x10(r1)
/* 8021FC44 0021C824  38 21 00 18 */	addi r1, r1, 0x18
/* 8021FC48 0021C828  7C 08 03 A6 */	mtlr r0
/* 8021FC4C 0021C82C  4E 80 00 20 */	blr 
}
#pragma peephole on

BOOL lbl_8021FC50()
{
    return FALSE;
}

BOOL lbl_8021FC58()
{
    return TRUE;
}
