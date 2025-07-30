#include <platform.h>

#include <melee/gm/types.h>
#include <melee/gr/types.h>
#include <melee/it/items/types.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/memory.h>

#include <dolphin/os.h>
#undef NOT_IMPLEMENTED
#define NOT_IMPLEMENTED \
    OSPanic(__FILE__, __LINE__, "Function is not implemented!")

int gmMainLib_8015F600()
{
    return 0;
}

int HSD_Synth_804D6018[2];

u8 lbl_80433710[0x20000];
void lbAudioAx_8002838C(void) {
    ARInit(lbl_80433710 + 0x514, 0x10U);
    ARQInit();
    AIInit(0);
}

UNK_T mnGallery_804A0B90[4];

// related to character unlocks?
bool fn_80164B48() { return false; }

void gm_80172898() {} // trophy message?
bool gm_80173754() { return true; } // unlocked message?

void hsd_80392E80(void) {}

void gm_801B14A0();
void gm_801B14DC();
void gm_801B1514();
void gm_801B154C();

void gm_801B1588();
void gm_801B15C8();
void gm_801B1648();
void gm_801B1688();


u8 HSD_SObjLib_804D7960[8];

void HSD_SObjLib_803A4740(HSD_Obj*);

GObjFunc HSD_SObjLib_8040C3A0[] = {
    HSD_SObjLib_803A4740,
};

GObjFuncs HSD_SObjLib_8040C3A4 = {
    0, 1, HSD_SObjLib_8040C3A0,
};

u8 gm_804807B0[0x5000];
u8 gm_8047C020[0x5000];
u8 gm_8047E2A4[0x5000];
u8 gm_80480530[0x5000];
u8 gm_80480668[0x5000];
u8 gm_804D6860[0x5000];

void gm_801B16A8();
void gm_801B16C8();

void gm_801BFA6C();

void gm_801BFCFC();
void gm_801A6308();

u8 un_804A1F48[0x50];

void gm_801BFABC();
void gm_801A6254();

void gm_801B087C();
void gm_801B089C();

u8 gm_804D6878[0x5000];

void gm_801B3500();
void gm_801B3A34();
void gm_801B3B40();
void gm_801B3D44();
void gm_801B3D84();
void gm_801B3DD8();
void gm_801B3E44();
void gm_801B3F18();
void gm_80470708();
void gm_80470850();

UNK_T gm_8047086C[0x200];
UNK_T gm_80472AF8[0x200];
UNK_T gm_804D68D0[0x200];
UNK_T gm_80490880[0x200];
UNK_T gm_8047086C[0x200];
UNK_T gm_80472AF8[0x200];
UNK_T gm_804D68D0[0x200];
UNK_T gm_80490880[0x200];
UNK_T gm_8047086C[0x200];
UNK_T gm_80472AF8[0x200];
UNK_T gm_804D68D0[0x200];
UNK_T gm_80490880[0x200];

void lbAudioAx_8002835C() {}
void lbAudioAx_80024030() {}
void lbAudioAx_8002392C() {}

void gm_801677C0() {}

int lbAudioAx_80026F2C() { return 0; }
int lbAudioAx_8002702C() { return 0; }
int lbAudioAx_80027168() { return 0; }
int lbAudioAx_80027DF8() { return 0; }
int lbAudioAx_80027648() { return 0; }

void hsd_803AAA48() {}

void* it_804D6D28;
UNK_T it_803F7E28[100] = { 0 };
UNK_T it_803F7D60[100] = { 0 };
UNK_T it_803F7CF8[100] = { 0 };
UNK_T it_803F7CA0[100] = { 0 };
UNK_T it_803F7C70[100] = { 0 };
UNK_T it_803F7C40[100] = { 0 };
UNK_T it_803F7C10[100] = { 0 };
UNK_T it_803F7BC0[100] = { 0 };
UNK_T it_803F7B58[100] = { 0 };
UNK_T it_803F7B08[100] = { 0 };
UNK_T it_803F7AD8[100] = { 0 };
UNK_T it_803F7A98[100] = { 0 };
UNK_T it_803F7A48[100] = { 0 };
UNK_T it_803F8BD8[100] = { 0 };
UNK_T it_803F94A0[100] = { 0 };
UNK_T it_803F7190[100] = { 0 };
UNK_T it_803F6F40[100] = { 0 };
UNK_T it_803F6B70[100] = { 0 };
UNK_T it_803F7760[100] = { 0 };
UNK_T it_803F6A28[100] = { 0 };
UNK_T it_803F6CA8[100] = { 0 };

UNK_T it_803B8570[200] = { 0 };
UNK_T it_803B857C[200] = { 0 };
UNK_T it_803F6C58[200] = { 0 };
UNK_T it_803F6F50[200] = { 0 };
UNK_T it_803F70A8[200] = { 0 };
UNK_T it_803F71D8[200] = { 0 };
UNK_T it_803F7288[200] = { 0 };
UNK_T it_803F75D0[200] = { 0 };
UNK_T it_803F7668[200] = { 0 };
UNK_T it_803F79C0[200] = { 0 };
UNK_T it_803F79E0[200] = { 0 };
UNK_T it_803F9378[200] = { 0 };
UNK_T it_803F9388[200] = { 0 };
UNK_T it_803F93A8[200] = { 0 };
UNK_T it_803F7A28[200] = { 0 };
UNK_T it_803F7968[200] = { 0 };
UNK_T it_803F78F8[200] = { 0 };
UNK_T it_803F78E8[200] = { 0 };
UNK_T it_803F78D8[200] = { 0 };
UNK_T it_803F7898[200] = { 0 };
UNK_T it_803F76B8[200] = { 0 };
UNK_T it_803F7750[200] = { 0 };
UNK_T it_803F7740[200] = { 0 };
UNK_T it_803F76F8[200] = { 0 };
UNK_T it_803F76A8[200] = { 0 };
UNK_T it_803F7558[200] = { 0 };
UNK_T it_803F6C68[200] = { 0 };
UNK_T it_803F7438[200] = { 0 };
UNK_T it_803F73A8[200] = { 0 };
UNK_T it_803F7340[200] = { 0 };
UNK_T it_803F7220[200] = { 0 };
UNK_T it_803F7118[200] = { 0 };
UNK_T it_803F70F8[200] = { 0 };
UNK_T it_803F70C8[200] = { 0 };
UNK_T it_803F6C08[200] = { 0 };
UNK_T it_803F6BC8[200] = { 0 };
UNK_T it_803F6B60[200] = { 0 };
UNK_T it_803F6B28[200] = { 0 };
UNK_T it_803F6998[200] = { 0 };
UNK_T it_803F6920[200] = { 0 };
UNK_T it_803F6888[200] = { 0 };
UNK_T it_803F6798[200] = { 0 };
UNK_T it_803F8E90[200] = { 0 };
UNK_T it_803B85A8[200] = { 0 };
UNK_T it_803F8320[200] = { 0 };
UNK_T it_803F8468[200] = { 0 };
UNK_T it_803F86C8[200] = { 0 };
UNK_T it_803F88C0[200] = { 0 };
UNK_T it_803F8940[200] = { 0 };
UNK_T it_803F89C8[200] = { 0 };
UNK_T it_803F8A88[200] = { 0 };
UNK_T it_803F8B48[200] = { 0 };
UNK_T it_803F8DE8[200] = { 0 };
UNK_T it_803F8EB0[200] = { 0 };
UNK_T it_803F8FD0[200] = { 0 };
UNK_T it_803F9000[200] = { 0 };
UNK_T it_803F90D0[200] = { 0 };
UNK_T it_803F91D0[200] = { 0 };
UNK_T it_803F9260[200] = { 0 };
UNK_T it_803F9328[200] = { 0 };
UNK_T it_803F5FF0[200] = { 0 };
UNK_T it_803F6310[200] = { 0 };
UNK_T it_803F5F90[200] = { 0 };
UNK_T it_803F5F40[200] = { 0 };
UNK_T it_803F5EA8[200] = { 0 };
UNK_T it_803F5E00[200] = { 0 };
UNK_T it_803F5DB0[200] = { 0 };
UNK_T it_803F5D28[200] = { 0 };
UNK_T it_803F5C48[200] = { 0 };
UNK_T it_803F5BA8[200] = { 0 };
UNK_T it_803F5740[200] = { 0 };
UNK_T it_803F56C8[200] = { 0 };
UNK_T it_803F55D0[200] = { 0 };
UNK_T it_803F54D8[200] = { 0 };
UNK_T it_803F63C0[200] = { 0 };
UNK_T it_803F59F8[200] = { 0 };
UNK_T it_803F6728[200] = { 0 };
UNK_T it_803F82A0[200] = { 0 };
UNK_T it_803F8200[200] = { 0 };
UNK_T it_803F8180[200] = { 0 };
UNK_T it_803F7FB8[200] = { 0 };
UNK_T it_803F7F48[200] = { 0 };
UNK_T it_803F7D90[200] = { 0 };
UNK_T it_803F7C00[200] = { 0 };
UNK_T it_803F7BB0[200] = { 0 };
UNK_T it_803F7B48[200] = { 0 };


StageData grTe_803E5764;
StageData grPushOn_803E7B10;
StageData grFigureGet_803E7D34;
StageData grBb_Route_803E617C;
StageData grZe_Route_803E5E0C;
StageData grSh_Route_803E5988;
StageData grNKr_803E584C;
StageData grOk_803E65E8;
StageData grOy_803E650C;
StageData grOp_803E6748;
StageData grFz_803E7A00;
StageData grI2_803E4C00;
StageData grI1_803E4950;
StageData grIm_803E4800;
StageData grFs_803E3D94;
StageData grOt_803E2858;
StageData grBb_803E2D20;
StageData grMc_803E33DC;
StageData grPu_803E6A3C;
StageData grPs_803E1334;
StageData grVe_803E54CC;
StageData grCn_803E1F08;
StageData grGr_803E76D0;
StageData grYt_803E51CC;
StageData grKr_803E4D0C;
StageData grZe_803E1B2C;
StageData grGb_803E3F6C;
StageData grGd_803E52E0;
StageData grKg_803E1800;
StageData grRc_803E4ECC;
StageData grCs_803E11A4;
StageData grHeal_803E84C4;
StageData grHr_803E821C;

Article** it_804D6D24;
Article** it_804D6D38;
Article** it_804D6D30;
s8 it_804D6D00;

CameraDebugMode cm_80453004;
HSD_ObjAllocData HSD_PSAppSrt_804D10B0;

void mpColl_80052A98() { NOT_IMPLEMENTED; }
void mpColl_800528CC() { NOT_IMPLEMENTED; }

u32 it_804D6D10;
s32 it_804D6D0C;
u32 it_804D6D14;

Article* it_804A0F60[30];
ItemStateTable it_803F7AC8[100];
ItemStateTable it_803F82F0[100];
ItemStateTable it_803F82B0[100];
ItemStateTable it_803F6640[100];

void Ground_801C28CC(void) { NOT_IMPLEMENTED; }
void Ground_801C34AC(void) { NOT_IMPLEMENTED; }
void Ground_801C20E0(void) { NOT_IMPLEMENTED; }
void ftCo_ItemScrew_Enter() { NOT_IMPLEMENTED; }

UNK_T it_803F6630[0x100];
UNK_T it_803F6568[0x100];
UNK_T it_803F6680[0x100];
UNK_T it_803F6530[0x100];
UNK_T it_803F6488[0x100];
UNK_T it_803F61B0[0x100];
UNK_T it_803F58E0[0x100];
UNK_T it_803F5850[0x100];
UNK_T it_8028428C[0x100];
UNK_T it_802841B4[0x100];
UNK_T it_8028428C[0x100];
UNK_T it_803F8270[0x100];
UNK_T it_803F8190[0x100];
UNK_T it_803F8128[0x100];
UNK_T it_803F7F58[0x100];
UNK_T it_803F7EE8[0x100];

void plAttack_8003759C() {}
void pl_80040DDC() {}
void pl_80041524() {}
void pl_800418F4() {}

void lbRefract_800222A4() {}
void lb_8000FA94() {}

void* lbHeap_80015BD0(int x, int size)
{
    return HSD_MemAlloc(size);
}

void* HSD_AudioMalloc(int size)
{
    return HSD_MemAlloc(size);
}

void HSD_DevComARAMWakeUp(void) {}

// might be needed to load trophy data?
void un_8031C2CC(void) { }

void it_8026D018() {}
void lbAudioAx_8002785C() {}
void mpLib_8004D288() {}
void grMaterial_801C95C4() {}
void grAnime_801C8138() {}
void mpLib_80055E9C() {}
void mpLib_80057424() {}
void grAnime_801C7FF8() {}
void grAnime_801C8098() {}
void grAnime_801C7980() {}
void Camera_8002B3D4() {}
void un_80321900() {}
void lbBgFlash_80021A18() {}
void lbAudioAx_80023F28() {}
void ifStatus_802F665C() {} // hud create?
void ifTime_802F446C() {} // hud timer?
void ifStatus_802F6EA4() {} // exclamation state change?
void fn_8016A4C8() {} // adventure mode spawn think?
void fn_8016758C(void) {}
void grMaterial_801C9698() {}
void fn_800301D0() {} // draw camera/ecb develop boxes?
void fn_80171DC4() {}
void fn_800587FC() {} // calculate range of lines?
void lb_800115F4() {} // wind decay think?
void lbAudioAx_800236DC() {}
void lb_80011E24() {}
void gm_801BF128() {}
HSD_MObj* ft_804D6588;
HSD_Joint* ft_8045A1E0[6];
float ftYs_Init_804D9A64 = 20;
float ftYs_Init_804D9A5C = 1;
float ftYs_Init_804D9A60 = 0;
float ftYs_Init_804D9A38 = 0;
UNK_T ftNn_Init_MotionStateTable[0x200];
UNK_T ftKp_Init_MotionStateTable[0x200];
UNK_T ftKb_Init_MotionStateTable[0x200];
void lbHeap_80015F3C() {}
void lbDvd_80018F68() {}
void lbArq_80014D2C() {}
void hsd_803B2374() {}
void lbMthp_8001F87C() {}
void lbMthp_8001F800() {}
void lbAudioAx_80028690() {}
void lbDvd_80018254() {}
void gm_801BF3F8() {} // menu title load demo
