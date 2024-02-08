.include "macros.inc"

.section .text  # 0x80037590 - 0x80037B28

.global plAttack_80037590
plAttack_80037590:
/* 80037590 00034170  38 00 00 01 */	li r0, 1
/* 80037594 00034174  B0 0D AD E0 */	sth r0, .L_804D6480@sda21(r13)
/* 80037598 00034178  4E 80 00 20 */	blr

.global plAttack_8003759C
plAttack_8003759C:
/* 8003759C 0003417C  7C 08 02 A6 */	mflr r0
/* 800375A0 00034180  90 01 00 04 */	stw r0, 4(r1)
/* 800375A4 00034184  94 21 FF F8 */	stwu r1, -8(r1)
/* 800375A8 00034188  4B FF EC 2D */	bl Player_GetTotalAttackCountPtr
/* 800375AC 0003418C  38 00 00 02 */	li r0, 2
/* 800375B0 00034190  39 60 00 00 */	li r11, 0
/* 800375B4 00034194  7C 09 03 A6 */	mtctr r0
/* 800375B8 00034198  39 83 00 00 */	addi r12, r3, 0
/* 800375BC 0003419C  39 4B 00 00 */	addi r10, r11, 0
/* 800375C0 000341A0  39 2B 00 00 */	addi r9, r11, 0
/* 800375C4 000341A4  39 0B 00 00 */	addi r8, r11, 0
/* 800375C8 000341A8  38 EB 00 00 */	addi r7, r11, 0
/* 800375CC 000341AC  38 CB 00 00 */	addi r6, r11, 0
/* 800375D0 000341B0  38 AB 00 00 */	addi r5, r11, 0
/* 800375D4 000341B4  38 8B 00 00 */	addi r4, r11, 0
/* 800375D8 000341B8  38 0B 00 00 */	addi r0, r11, 0
.L_800375DC:
/* 800375DC 000341BC  91 4C 00 04 */	stw r10, 4(r12)
/* 800375E0 000341C0  39 6B 00 30 */	addi r11, r11, 0x30
/* 800375E4 000341C4  91 2C 00 08 */	stw r9, 8(r12)
/* 800375E8 000341C8  91 0C 00 0C */	stw r8, 0xc(r12)
/* 800375EC 000341CC  90 EC 00 10 */	stw r7, 0x10(r12)
/* 800375F0 000341D0  90 CC 00 14 */	stw r6, 0x14(r12)
/* 800375F4 000341D4  90 AC 00 18 */	stw r5, 0x18(r12)
/* 800375F8 000341D8  90 8C 00 1C */	stw r4, 0x1c(r12)
/* 800375FC 000341DC  90 0C 00 20 */	stw r0, 0x20(r12)
/* 80037600 000341E0  91 4C 00 24 */	stw r10, 0x24(r12)
/* 80037604 000341E4  91 2C 00 28 */	stw r9, 0x28(r12)
/* 80037608 000341E8  91 0C 00 2C */	stw r8, 0x2c(r12)
/* 8003760C 000341EC  90 EC 00 30 */	stw r7, 0x30(r12)
/* 80037610 000341F0  90 CC 00 34 */	stw r6, 0x34(r12)
/* 80037614 000341F4  90 AC 00 38 */	stw r5, 0x38(r12)
/* 80037618 000341F8  90 8C 00 3C */	stw r4, 0x3c(r12)
/* 8003761C 000341FC  90 0C 00 40 */	stw r0, 0x40(r12)
/* 80037620 00034200  91 4C 00 44 */	stw r10, 0x44(r12)
/* 80037624 00034204  91 2C 00 48 */	stw r9, 0x48(r12)
/* 80037628 00034208  91 0C 00 4C */	stw r8, 0x4c(r12)
/* 8003762C 0003420C  90 EC 00 50 */	stw r7, 0x50(r12)
/* 80037630 00034210  90 CC 00 54 */	stw r6, 0x54(r12)
/* 80037634 00034214  90 AC 00 58 */	stw r5, 0x58(r12)
/* 80037638 00034218  90 8C 00 5C */	stw r4, 0x5c(r12)
/* 8003763C 0003421C  90 0C 00 60 */	stw r0, 0x60(r12)
/* 80037640 00034220  91 4C 00 64 */	stw r10, 0x64(r12)
/* 80037644 00034224  91 2C 00 68 */	stw r9, 0x68(r12)
/* 80037648 00034228  91 0C 00 6C */	stw r8, 0x6c(r12)
/* 8003764C 0003422C  90 EC 00 70 */	stw r7, 0x70(r12)
/* 80037650 00034230  90 CC 00 74 */	stw r6, 0x74(r12)
/* 80037654 00034234  90 AC 00 78 */	stw r5, 0x78(r12)
/* 80037658 00034238  90 8C 00 7C */	stw r4, 0x7c(r12)
/* 8003765C 0003423C  90 0C 00 80 */	stw r0, 0x80(r12)
/* 80037660 00034240  91 4C 00 84 */	stw r10, 0x84(r12)
/* 80037664 00034244  91 2C 00 88 */	stw r9, 0x88(r12)
/* 80037668 00034248  91 0C 00 8C */	stw r8, 0x8c(r12)
/* 8003766C 0003424C  90 EC 00 90 */	stw r7, 0x90(r12)
/* 80037670 00034250  90 CC 00 94 */	stw r6, 0x94(r12)
/* 80037674 00034254  90 AC 00 98 */	stw r5, 0x98(r12)
/* 80037678 00034258  90 8C 00 9C */	stw r4, 0x9c(r12)
/* 8003767C 0003425C  90 0C 00 A0 */	stw r0, 0xa0(r12)
/* 80037680 00034260  91 4C 00 A4 */	stw r10, 0xa4(r12)
/* 80037684 00034264  91 2C 00 A8 */	stw r9, 0xa8(r12)
/* 80037688 00034268  91 0C 00 AC */	stw r8, 0xac(r12)
/* 8003768C 0003426C  90 EC 00 B0 */	stw r7, 0xb0(r12)
/* 80037690 00034270  90 CC 00 B4 */	stw r6, 0xb4(r12)
/* 80037694 00034274  90 AC 00 B8 */	stw r5, 0xb8(r12)
/* 80037698 00034278  90 8C 00 BC */	stw r4, 0xbc(r12)
/* 8003769C 0003427C  94 0C 00 C0 */	stwu r0, 0xc0(r12)
/* 800376A0 00034280  42 00 FF 3C */	bdnz .L_800375DC
/* 800376A4 00034284  48 00 04 30 */	b .L_80037AD4
.L_800376A8:
/* 800376A8 00034288  20 0B 00 64 */	subfic r0, r11, 0x64
/* 800376AC 0003428C  2C 0B 00 64 */	cmpwi r11, 0x64
/* 800376B0 00034290  7C 09 03 A6 */	mtctr r0
/* 800376B4 00034294  38 00 00 00 */	li r0, 0
/* 800376B8 00034298  40 80 00 0C */	bge .L_800376C4
.L_800376BC:
/* 800376BC 0003429C  94 04 00 04 */	stwu r0, 4(r4)
/* 800376C0 000342A0  42 00 FF FC */	bdnz .L_800376BC
.L_800376C4:
/* 800376C4 000342A4  38 80 00 00 */	li r4, 0
/* 800376C8 000342A8  90 83 00 00 */	stw r4, 0(r3)
/* 800376CC 000342AC  38 00 00 02 */	li r0, 2
/* 800376D0 000342B0  7C 09 03 A6 */	mtctr r0
/* 800376D4 000342B4  38 A4 00 00 */	addi r5, r4, 0
/* 800376D8 000342B8  90 83 01 94 */	stw r4, 0x194(r3)
/* 800376DC 000342BC  7C 66 1B 78 */	mr r6, r3
/* 800376E0 000342C0  90 83 01 98 */	stw r4, 0x198(r3)
/* 800376E4 000342C4  90 83 01 9C */	stw r4, 0x19c(r3)
/* 800376E8 000342C8  90 83 01 A0 */	stw r4, 0x1a0(r3)
/* 800376EC 000342CC  90 83 01 A4 */	stw r4, 0x1a4(r3)
/* 800376F0 000342D0  90 83 01 A8 */	stw r4, 0x1a8(r3)
.L_800376F4:
/* 800376F4 000342D4  90 86 01 B0 */	stw r4, 0x1b0(r6)
/* 800376F8 000342D8  38 A5 00 30 */	addi r5, r5, 0x30
/* 800376FC 000342DC  90 86 01 B4 */	stw r4, 0x1b4(r6)
/* 80037700 000342E0  90 86 01 B8 */	stw r4, 0x1b8(r6)
/* 80037704 000342E4  90 86 01 BC */	stw r4, 0x1bc(r6)
/* 80037708 000342E8  90 86 01 C0 */	stw r4, 0x1c0(r6)
/* 8003770C 000342EC  90 86 01 C4 */	stw r4, 0x1c4(r6)
/* 80037710 000342F0  90 86 01 C8 */	stw r4, 0x1c8(r6)
/* 80037714 000342F4  90 86 01 CC */	stw r4, 0x1cc(r6)
/* 80037718 000342F8  90 86 01 D0 */	stw r4, 0x1d0(r6)
/* 8003771C 000342FC  90 86 01 D4 */	stw r4, 0x1d4(r6)
/* 80037720 00034300  90 86 01 D8 */	stw r4, 0x1d8(r6)
/* 80037724 00034304  90 86 01 DC */	stw r4, 0x1dc(r6)
/* 80037728 00034308  90 86 01 E0 */	stw r4, 0x1e0(r6)
/* 8003772C 0003430C  90 86 01 E4 */	stw r4, 0x1e4(r6)
/* 80037730 00034310  90 86 01 E8 */	stw r4, 0x1e8(r6)
/* 80037734 00034314  90 86 01 EC */	stw r4, 0x1ec(r6)
/* 80037738 00034318  90 86 01 F0 */	stw r4, 0x1f0(r6)
/* 8003773C 0003431C  90 86 01 F4 */	stw r4, 0x1f4(r6)
/* 80037740 00034320  90 86 01 F8 */	stw r4, 0x1f8(r6)
/* 80037744 00034324  90 86 01 FC */	stw r4, 0x1fc(r6)
/* 80037748 00034328  90 86 02 00 */	stw r4, 0x200(r6)
/* 8003774C 0003432C  90 86 02 04 */	stw r4, 0x204(r6)
/* 80037750 00034330  90 86 02 08 */	stw r4, 0x208(r6)
/* 80037754 00034334  90 86 02 0C */	stw r4, 0x20c(r6)
/* 80037758 00034338  90 86 02 10 */	stw r4, 0x210(r6)
/* 8003775C 0003433C  90 86 02 14 */	stw r4, 0x214(r6)
/* 80037760 00034340  90 86 02 18 */	stw r4, 0x218(r6)
/* 80037764 00034344  90 86 02 1C */	stw r4, 0x21c(r6)
/* 80037768 00034348  90 86 02 20 */	stw r4, 0x220(r6)
/* 8003776C 0003434C  90 86 02 24 */	stw r4, 0x224(r6)
/* 80037770 00034350  90 86 02 28 */	stw r4, 0x228(r6)
/* 80037774 00034354  90 86 02 2C */	stw r4, 0x22c(r6)
/* 80037778 00034358  90 86 02 30 */	stw r4, 0x230(r6)
/* 8003777C 0003435C  90 86 02 34 */	stw r4, 0x234(r6)
/* 80037780 00034360  90 86 02 38 */	stw r4, 0x238(r6)
/* 80037784 00034364  90 86 02 3C */	stw r4, 0x23c(r6)
/* 80037788 00034368  90 86 02 40 */	stw r4, 0x240(r6)
/* 8003778C 0003436C  90 86 02 44 */	stw r4, 0x244(r6)
/* 80037790 00034370  90 86 02 48 */	stw r4, 0x248(r6)
/* 80037794 00034374  90 86 02 4C */	stw r4, 0x24c(r6)
/* 80037798 00034378  90 86 02 50 */	stw r4, 0x250(r6)
/* 8003779C 0003437C  90 86 02 54 */	stw r4, 0x254(r6)
/* 800377A0 00034380  90 86 02 58 */	stw r4, 0x258(r6)
/* 800377A4 00034384  90 86 02 5C */	stw r4, 0x25c(r6)
/* 800377A8 00034388  90 86 02 60 */	stw r4, 0x260(r6)
/* 800377AC 0003438C  90 86 02 64 */	stw r4, 0x264(r6)
/* 800377B0 00034390  90 86 02 68 */	stw r4, 0x268(r6)
/* 800377B4 00034394  90 86 02 6C */	stw r4, 0x26c(r6)
/* 800377B8 00034398  38 C6 00 C0 */	addi r6, r6, 0xc0
/* 800377BC 0003439C  42 00 FF 38 */	bdnz .L_800376F4
/* 800377C0 000343A0  48 00 03 20 */	b .L_80037AE0
.L_800377C4:
/* 800377C4 000343A4  20 05 00 64 */	subfic r0, r5, 0x64
/* 800377C8 000343A8  2C 05 00 64 */	cmpwi r5, 0x64
/* 800377CC 000343AC  7C 09 03 A6 */	mtctr r0
/* 800377D0 000343B0  38 00 00 00 */	li r0, 0
/* 800377D4 000343B4  40 80 00 10 */	bge .L_800377E4
.L_800377D8:
/* 800377D8 000343B8  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 800377DC 000343BC  38 84 00 04 */	addi r4, r4, 4
/* 800377E0 000343C0  42 00 FF F8 */	bdnz .L_800377D8
.L_800377E4:
/* 800377E4 000343C4  38 80 00 00 */	li r4, 0
/* 800377E8 000343C8  90 83 01 AC */	stw r4, 0x1ac(r3)
/* 800377EC 000343CC  38 00 00 02 */	li r0, 2
/* 800377F0 000343D0  7C 09 03 A6 */	mtctr r0
/* 800377F4 000343D4  38 A4 00 00 */	addi r5, r4, 0
/* 800377F8 000343D8  90 83 03 40 */	stw r4, 0x340(r3)
/* 800377FC 000343DC  7C 66 1B 78 */	mr r6, r3
/* 80037800 000343E0  90 83 03 44 */	stw r4, 0x344(r3)
/* 80037804 000343E4  90 83 03 48 */	stw r4, 0x348(r3)
/* 80037808 000343E8  90 83 03 4C */	stw r4, 0x34c(r3)
/* 8003780C 000343EC  90 83 03 50 */	stw r4, 0x350(r3)
/* 80037810 000343F0  90 83 03 54 */	stw r4, 0x354(r3)
.L_80037814:
/* 80037814 000343F4  90 86 03 5C */	stw r4, 0x35c(r6)
/* 80037818 000343F8  38 A5 00 30 */	addi r5, r5, 0x30
/* 8003781C 000343FC  90 86 03 60 */	stw r4, 0x360(r6)
/* 80037820 00034400  90 86 03 64 */	stw r4, 0x364(r6)
/* 80037824 00034404  90 86 03 68 */	stw r4, 0x368(r6)
/* 80037828 00034408  90 86 03 6C */	stw r4, 0x36c(r6)
/* 8003782C 0003440C  90 86 03 70 */	stw r4, 0x370(r6)
/* 80037830 00034410  90 86 03 74 */	stw r4, 0x374(r6)
/* 80037834 00034414  90 86 03 78 */	stw r4, 0x378(r6)
/* 80037838 00034418  90 86 03 7C */	stw r4, 0x37c(r6)
/* 8003783C 0003441C  90 86 03 80 */	stw r4, 0x380(r6)
/* 80037840 00034420  90 86 03 84 */	stw r4, 0x384(r6)
/* 80037844 00034424  90 86 03 88 */	stw r4, 0x388(r6)
/* 80037848 00034428  90 86 03 8C */	stw r4, 0x38c(r6)
/* 8003784C 0003442C  90 86 03 90 */	stw r4, 0x390(r6)
/* 80037850 00034430  90 86 03 94 */	stw r4, 0x394(r6)
/* 80037854 00034434  90 86 03 98 */	stw r4, 0x398(r6)
/* 80037858 00034438  90 86 03 9C */	stw r4, 0x39c(r6)
/* 8003785C 0003443C  90 86 03 A0 */	stw r4, 0x3a0(r6)
/* 80037860 00034440  90 86 03 A4 */	stw r4, 0x3a4(r6)
/* 80037864 00034444  90 86 03 A8 */	stw r4, 0x3a8(r6)
/* 80037868 00034448  90 86 03 AC */	stw r4, 0x3ac(r6)
/* 8003786C 0003444C  90 86 03 B0 */	stw r4, 0x3b0(r6)
/* 80037870 00034450  90 86 03 B4 */	stw r4, 0x3b4(r6)
/* 80037874 00034454  90 86 03 B8 */	stw r4, 0x3b8(r6)
/* 80037878 00034458  90 86 03 BC */	stw r4, 0x3bc(r6)
/* 8003787C 0003445C  90 86 03 C0 */	stw r4, 0x3c0(r6)
/* 80037880 00034460  90 86 03 C4 */	stw r4, 0x3c4(r6)
/* 80037884 00034464  90 86 03 C8 */	stw r4, 0x3c8(r6)
/* 80037888 00034468  90 86 03 CC */	stw r4, 0x3cc(r6)
/* 8003788C 0003446C  90 86 03 D0 */	stw r4, 0x3d0(r6)
/* 80037890 00034470  90 86 03 D4 */	stw r4, 0x3d4(r6)
/* 80037894 00034474  90 86 03 D8 */	stw r4, 0x3d8(r6)
/* 80037898 00034478  90 86 03 DC */	stw r4, 0x3dc(r6)
/* 8003789C 0003447C  90 86 03 E0 */	stw r4, 0x3e0(r6)
/* 800378A0 00034480  90 86 03 E4 */	stw r4, 0x3e4(r6)
/* 800378A4 00034484  90 86 03 E8 */	stw r4, 0x3e8(r6)
/* 800378A8 00034488  90 86 03 EC */	stw r4, 0x3ec(r6)
/* 800378AC 0003448C  90 86 03 F0 */	stw r4, 0x3f0(r6)
/* 800378B0 00034490  90 86 03 F4 */	stw r4, 0x3f4(r6)
/* 800378B4 00034494  90 86 03 F8 */	stw r4, 0x3f8(r6)
/* 800378B8 00034498  90 86 03 FC */	stw r4, 0x3fc(r6)
/* 800378BC 0003449C  90 86 04 00 */	stw r4, 0x400(r6)
/* 800378C0 000344A0  90 86 04 04 */	stw r4, 0x404(r6)
/* 800378C4 000344A4  90 86 04 08 */	stw r4, 0x408(r6)
/* 800378C8 000344A8  90 86 04 0C */	stw r4, 0x40c(r6)
/* 800378CC 000344AC  90 86 04 10 */	stw r4, 0x410(r6)
/* 800378D0 000344B0  90 86 04 14 */	stw r4, 0x414(r6)
/* 800378D4 000344B4  90 86 04 18 */	stw r4, 0x418(r6)
/* 800378D8 000344B8  38 C6 00 C0 */	addi r6, r6, 0xc0
/* 800378DC 000344BC  42 00 FF 38 */	bdnz .L_80037814
/* 800378E0 000344C0  48 00 02 0C */	b .L_80037AEC
.L_800378E4:
/* 800378E4 000344C4  20 05 00 64 */	subfic r0, r5, 0x64
/* 800378E8 000344C8  2C 05 00 64 */	cmpwi r5, 0x64
/* 800378EC 000344CC  7C 09 03 A6 */	mtctr r0
/* 800378F0 000344D0  38 00 00 00 */	li r0, 0
/* 800378F4 000344D4  40 80 00 10 */	bge .L_80037904
.L_800378F8:
/* 800378F8 000344D8  90 04 03 5C */	stw r0, 0x35c(r4)
/* 800378FC 000344DC  38 84 00 04 */	addi r4, r4, 4
/* 80037900 000344E0  42 00 FF F8 */	bdnz .L_800378F8
.L_80037904:
/* 80037904 000344E4  38 80 00 00 */	li r4, 0
/* 80037908 000344E8  90 83 03 58 */	stw r4, 0x358(r3)
/* 8003790C 000344EC  38 00 00 02 */	li r0, 2
/* 80037910 000344F0  7C 09 03 A6 */	mtctr r0
/* 80037914 000344F4  38 C0 00 00 */	li r6, 0
/* 80037918 000344F8  90 83 04 EC */	stw r4, 0x4ec(r3)
/* 8003791C 000344FC  90 83 04 F0 */	stw r4, 0x4f0(r3)
/* 80037920 00034500  90 83 04 F4 */	stw r4, 0x4f4(r3)
/* 80037924 00034504  90 83 04 F8 */	stw r4, 0x4f8(r3)
/* 80037928 00034508  90 83 04 FC */	stw r4, 0x4fc(r3)
/* 8003792C 0003450C  90 83 05 00 */	stw r4, 0x500(r3)
.L_80037930:
/* 80037930 00034510  38 A6 05 04 */	addi r5, r6, 0x504
/* 80037934 00034514  7C A3 2A 14 */	add r5, r3, r5
/* 80037938 00034518  98 85 00 00 */	stb r4, 0(r5)
/* 8003793C 0003451C  98 85 00 01 */	stb r4, 1(r5)
/* 80037940 00034520  98 85 00 02 */	stb r4, 2(r5)
/* 80037944 00034524  98 85 00 03 */	stb r4, 3(r5)
/* 80037948 00034528  98 85 00 04 */	stb r4, 4(r5)
/* 8003794C 0003452C  98 85 00 05 */	stb r4, 5(r5)
/* 80037950 00034530  98 85 00 06 */	stb r4, 6(r5)
/* 80037954 00034534  98 85 00 07 */	stb r4, 7(r5)
/* 80037958 00034538  38 A6 05 0C */	addi r5, r6, 0x50c
/* 8003795C 0003453C  7C A3 2A 14 */	add r5, r3, r5
/* 80037960 00034540  98 85 00 00 */	stb r4, 0(r5)
/* 80037964 00034544  98 85 00 01 */	stb r4, 1(r5)
/* 80037968 00034548  98 85 00 02 */	stb r4, 2(r5)
/* 8003796C 0003454C  98 85 00 03 */	stb r4, 3(r5)
/* 80037970 00034550  98 85 00 04 */	stb r4, 4(r5)
/* 80037974 00034554  98 85 00 05 */	stb r4, 5(r5)
/* 80037978 00034558  98 85 00 06 */	stb r4, 6(r5)
/* 8003797C 0003455C  98 85 00 07 */	stb r4, 7(r5)
/* 80037980 00034560  38 A6 05 14 */	addi r5, r6, 0x514
/* 80037984 00034564  7C A3 2A 14 */	add r5, r3, r5
/* 80037988 00034568  98 85 00 00 */	stb r4, 0(r5)
/* 8003798C 0003456C  98 85 00 01 */	stb r4, 1(r5)
/* 80037990 00034570  98 85 00 02 */	stb r4, 2(r5)
/* 80037994 00034574  98 85 00 03 */	stb r4, 3(r5)
/* 80037998 00034578  98 85 00 04 */	stb r4, 4(r5)
/* 8003799C 0003457C  98 85 00 05 */	stb r4, 5(r5)
/* 800379A0 00034580  98 85 00 06 */	stb r4, 6(r5)
/* 800379A4 00034584  98 85 00 07 */	stb r4, 7(r5)
/* 800379A8 00034588  38 A6 05 1C */	addi r5, r6, 0x51c
/* 800379AC 0003458C  7C A3 2A 14 */	add r5, r3, r5
/* 800379B0 00034590  98 85 00 00 */	stb r4, 0(r5)
/* 800379B4 00034594  98 85 00 01 */	stb r4, 1(r5)
/* 800379B8 00034598  98 85 00 02 */	stb r4, 2(r5)
/* 800379BC 0003459C  98 85 00 03 */	stb r4, 3(r5)
/* 800379C0 000345A0  98 85 00 04 */	stb r4, 4(r5)
/* 800379C4 000345A4  98 85 00 05 */	stb r4, 5(r5)
/* 800379C8 000345A8  98 85 00 06 */	stb r4, 6(r5)
/* 800379CC 000345AC  98 85 00 07 */	stb r4, 7(r5)
/* 800379D0 000345B0  38 A6 05 24 */	addi r5, r6, 0x524
/* 800379D4 000345B4  7C A3 2A 14 */	add r5, r3, r5
/* 800379D8 000345B8  98 85 00 00 */	stb r4, 0(r5)
/* 800379DC 000345BC  98 85 00 01 */	stb r4, 1(r5)
/* 800379E0 000345C0  98 85 00 02 */	stb r4, 2(r5)
/* 800379E4 000345C4  98 85 00 03 */	stb r4, 3(r5)
/* 800379E8 000345C8  98 85 00 04 */	stb r4, 4(r5)
/* 800379EC 000345CC  98 85 00 05 */	stb r4, 5(r5)
/* 800379F0 000345D0  98 85 00 06 */	stb r4, 6(r5)
/* 800379F4 000345D4  98 85 00 07 */	stb r4, 7(r5)
/* 800379F8 000345D8  38 A6 05 2C */	addi r5, r6, 0x52c
/* 800379FC 000345DC  7C A3 2A 14 */	add r5, r3, r5
/* 80037A00 000345E0  98 85 00 00 */	stb r4, 0(r5)
/* 80037A04 000345E4  38 C6 00 30 */	addi r6, r6, 0x30
/* 80037A08 000345E8  98 85 00 01 */	stb r4, 1(r5)
/* 80037A0C 000345EC  98 85 00 02 */	stb r4, 2(r5)
/* 80037A10 000345F0  98 85 00 03 */	stb r4, 3(r5)
/* 80037A14 000345F4  98 85 00 04 */	stb r4, 4(r5)
/* 80037A18 000345F8  98 85 00 05 */	stb r4, 5(r5)
/* 80037A1C 000345FC  98 85 00 06 */	stb r4, 6(r5)
/* 80037A20 00034600  98 85 00 07 */	stb r4, 7(r5)
/* 80037A24 00034604  42 00 FF 0C */	bdnz .L_80037930
/* 80037A28 00034608  20 06 00 64 */	subfic r0, r6, 0x64
/* 80037A2C 0003460C  2C 06 00 64 */	cmpwi r6, 0x64
/* 80037A30 00034610  7C 09 03 A6 */	mtctr r0
/* 80037A34 00034614  38 80 00 00 */	li r4, 0
/* 80037A38 00034618  40 80 00 14 */	bge .L_80037A4C
.L_80037A3C:
/* 80037A3C 0003461C  38 06 05 04 */	addi r0, r6, 0x504
/* 80037A40 00034620  7C 83 01 AE */	stbx r4, r3, r0
/* 80037A44 00034624  38 C6 00 01 */	addi r6, r6, 1
/* 80037A48 00034628  42 00 FF F4 */	bdnz .L_80037A3C
.L_80037A4C:
/* 80037A4C 0003462C  38 80 00 00 */	li r4, 0
/* 80037A50 00034630  90 83 05 68 */	stw r4, 0x568(r3)
/* 80037A54 00034634  90 83 05 70 */	stw r4, 0x570(r3)
/* 80037A58 00034638  90 83 05 6C */	stw r4, 0x56c(r3)
/* 80037A5C 0003463C  90 83 05 74 */	stw r4, 0x574(r3)
/* 80037A60 00034640  90 83 05 78 */	stw r4, 0x578(r3)
/* 80037A64 00034644  90 83 05 7C */	stw r4, 0x57c(r3)
/* 80037A68 00034648  90 83 05 80 */	stw r4, 0x580(r3)
/* 80037A6C 0003464C  90 83 05 84 */	stw r4, 0x584(r3)
/* 80037A70 00034650  90 83 05 88 */	stw r4, 0x588(r3)
/* 80037A74 00034654  90 83 05 8C */	stw r4, 0x58c(r3)
/* 80037A78 00034658  90 83 05 90 */	stw r4, 0x590(r3)
/* 80037A7C 0003465C  90 83 05 94 */	stw r4, 0x594(r3)
/* 80037A80 00034660  90 83 05 98 */	stw r4, 0x598(r3)
/* 80037A84 00034664  90 83 05 9C */	stw r4, 0x59c(r3)
/* 80037A88 00034668  90 83 05 A0 */	stw r4, 0x5a0(r3)
/* 80037A8C 0003466C  90 83 05 A4 */	stw r4, 0x5a4(r3)
/* 80037A90 00034670  90 83 05 A8 */	stw r4, 0x5a8(r3)
/* 80037A94 00034674  90 83 05 AC */	stw r4, 0x5ac(r3)
/* 80037A98 00034678  90 83 05 B0 */	stw r4, 0x5b0(r3)
/* 80037A9C 0003467C  90 83 05 B4 */	stw r4, 0x5b4(r3)
/* 80037AA0 00034680  88 03 05 BC */	lbz r0, 0x5bc(r3)
/* 80037AA4 00034684  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 80037AA8 00034688  98 03 05 BC */	stb r0, 0x5bc(r3)
/* 80037AAC 0003468C  88 03 05 BC */	lbz r0, 0x5bc(r3)
/* 80037AB0 00034690  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 80037AB4 00034694  98 03 05 BC */	stb r0, 0x5bc(r3)
/* 80037AB8 00034698  88 03 05 BC */	lbz r0, 0x5bc(r3)
/* 80037ABC 0003469C  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 80037AC0 000346A0  98 03 05 BC */	stb r0, 0x5bc(r3)
/* 80037AC4 000346A4  88 03 05 BC */	lbz r0, 0x5bc(r3)
/* 80037AC8 000346A8  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80037ACC 000346AC  98 03 05 BC */	stb r0, 0x5bc(r3)
/* 80037AD0 000346B0  48 00 00 28 */	b .L_80037AF8
.L_80037AD4:
/* 80037AD4 000346B4  55 60 10 3A */	slwi r0, r11, 2
/* 80037AD8 000346B8  7C 83 02 14 */	add r4, r3, r0
/* 80037ADC 000346BC  4B FF FB CC */	b .L_800376A8
.L_80037AE0:
/* 80037AE0 000346C0  54 A0 10 3A */	slwi r0, r5, 2
/* 80037AE4 000346C4  7C 83 02 14 */	add r4, r3, r0
/* 80037AE8 000346C8  4B FF FC DC */	b .L_800377C4
.L_80037AEC:
/* 80037AEC 000346CC  54 A0 10 3A */	slwi r0, r5, 2
/* 80037AF0 000346D0  7C 83 02 14 */	add r4, r3, r0
/* 80037AF4 000346D4  4B FF FD F0 */	b .L_800378E4
.L_80037AF8:
/* 80037AF8 000346D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80037AFC 000346DC  38 21 00 08 */	addi r1, r1, 8
/* 80037B00 000346E0  7C 08 03 A6 */	mtlr r0
/* 80037B04 000346E4  4E 80 00 20 */	blr

.global plAttack_80037B08
plAttack_80037B08:
/* 80037B08 000346E8  A0 6D AD E0 */	lhz r3, .L_804D6480@sda21(r13)
/* 80037B0C 000346EC  38 03 00 01 */	addi r0, r3, 1
/* 80037B10 000346F0  B0 0D AD E0 */	sth r0, .L_804D6480@sda21(r13)
/* 80037B14 000346F4  A0 0D AD E0 */	lhz r0, .L_804D6480@sda21(r13)
/* 80037B18 000346F8  28 00 00 00 */	cmplwi r0, 0
/* 80037B1C 000346FC  4C 82 00 20 */	bnelr
/* 80037B20 00034700  38 00 00 01 */	li r0, 1
/* 80037B24 00034704  B0 0D AD E0 */	sth r0, .L_804D6480@sda21(r13)
/* 80037B28 00034708  4E 80 00 20 */	blr

.section .sbss
    .balign 8
.L_804D6480:
    .skip 0x2