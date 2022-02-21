.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global MatToQuat
MatToQuat:
/* 8037E708 0037B2E8  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8037E70C 0037B2EC  3C A0 80 3C */	lis r5, lbl_803B95E8@ha
/* 8037E710 0037B2F0  38 C5 95 E8 */	addi r6, r5, lbl_803B95E8@l
/* 8037E714 0037B2F4  80 A6 00 00 */	lwz r5, 0(r6)
/* 8037E718 0037B2F8  80 06 00 04 */	lwz r0, 4(r6)
/* 8037E71C 0037B2FC  C0 02 ED 40 */	lfs f0, lbl_804DE720@sda21(r2)
/* 8037E720 0037B300  90 A1 00 30 */	stw r5, 0x30(r1)
/* 8037E724 0037B304  90 01 00 34 */	stw r0, 0x34(r1)
/* 8037E728 0037B308  80 06 00 08 */	lwz r0, 8(r6)
/* 8037E72C 0037B30C  90 01 00 38 */	stw r0, 0x38(r1)
/* 8037E730 0037B310  C0 43 00 00 */	lfs f2, 0(r3)
/* 8037E734 0037B314  C0 23 00 10 */	lfs f1, 0x10(r3)
/* 8037E738 0037B318  C0 63 00 20 */	lfs f3, 0x20(r3)
/* 8037E73C 0037B31C  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8037E740 0037B320  EC 21 00 72 */	fmuls f1, f1, f1
/* 8037E744 0037B324  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8037E748 0037B328  EC 22 08 2A */	fadds f1, f2, f1
/* 8037E74C 0037B32C  EC 83 08 2A */	fadds f4, f3, f1
/* 8037E750 0037B330  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8037E754 0037B334  40 81 00 50 */	ble lbl_8037E7A4
/* 8037E758 0037B338  FC 20 20 34 */	frsqrte f1, f4
/* 8037E75C 0037B33C  C8 62 ED 48 */	lfd f3, lbl_804DE728@sda21(r2)
/* 8037E760 0037B340  C8 42 ED 50 */	lfd f2, lbl_804DE730@sda21(r2)
/* 8037E764 0037B344  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E768 0037B348  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E76C 0037B34C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E770 0037B350  FC 21 00 32 */	fmul f1, f1, f0
/* 8037E774 0037B354  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E778 0037B358  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E77C 0037B35C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E780 0037B360  FC 21 00 32 */	fmul f1, f1, f0
/* 8037E784 0037B364  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E788 0037B368  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E78C 0037B36C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E790 0037B370  FC 01 00 32 */	fmul f0, f1, f0
/* 8037E794 0037B374  FC 04 00 32 */	fmul f0, f4, f0
/* 8037E798 0037B378  FC 00 00 18 */	frsp f0, f0
/* 8037E79C 0037B37C  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8037E7A0 0037B380  C0 81 00 20 */	lfs f4, 0x20(r1)
lbl_8037E7A4:
/* 8037E7A4 0037B384  D0 81 00 24 */	stfs f4, 0x24(r1)
/* 8037E7A8 0037B388  C0 02 ED 40 */	lfs f0, lbl_804DE720@sda21(r2)
/* 8037E7AC 0037B38C  C0 43 00 04 */	lfs f2, 4(r3)
/* 8037E7B0 0037B390  C0 23 00 14 */	lfs f1, 0x14(r3)
/* 8037E7B4 0037B394  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8037E7B8 0037B398  C0 63 00 24 */	lfs f3, 0x24(r3)
/* 8037E7BC 0037B39C  EC 21 00 72 */	fmuls f1, f1, f1
/* 8037E7C0 0037B3A0  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8037E7C4 0037B3A4  EC 22 08 2A */	fadds f1, f2, f1
/* 8037E7C8 0037B3A8  EC 83 08 2A */	fadds f4, f3, f1
/* 8037E7CC 0037B3AC  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8037E7D0 0037B3B0  40 81 00 50 */	ble lbl_8037E820
/* 8037E7D4 0037B3B4  FC 20 20 34 */	frsqrte f1, f4
/* 8037E7D8 0037B3B8  C8 62 ED 48 */	lfd f3, lbl_804DE728@sda21(r2)
/* 8037E7DC 0037B3BC  C8 42 ED 50 */	lfd f2, lbl_804DE730@sda21(r2)
/* 8037E7E0 0037B3C0  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E7E4 0037B3C4  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E7E8 0037B3C8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E7EC 0037B3CC  FC 21 00 32 */	fmul f1, f1, f0
/* 8037E7F0 0037B3D0  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E7F4 0037B3D4  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E7F8 0037B3D8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E7FC 0037B3DC  FC 21 00 32 */	fmul f1, f1, f0
/* 8037E800 0037B3E0  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E804 0037B3E4  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E808 0037B3E8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E80C 0037B3EC  FC 01 00 32 */	fmul f0, f1, f0
/* 8037E810 0037B3F0  FC 04 00 32 */	fmul f0, f4, f0
/* 8037E814 0037B3F4  FC 00 00 18 */	frsp f0, f0
/* 8037E818 0037B3F8  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8037E81C 0037B3FC  C0 81 00 1C */	lfs f4, 0x1c(r1)
lbl_8037E820:
/* 8037E820 0037B400  D0 81 00 28 */	stfs f4, 0x28(r1)
/* 8037E824 0037B404  C0 23 00 08 */	lfs f1, 8(r3)
/* 8037E828 0037B408  C0 03 00 18 */	lfs f0, 0x18(r3)
/* 8037E82C 0037B40C  EC 41 00 72 */	fmuls f2, f1, f1
/* 8037E830 0037B410  C0 63 00 28 */	lfs f3, 0x28(r3)
/* 8037E834 0037B414  EC 20 00 32 */	fmuls f1, f0, f0
/* 8037E838 0037B418  C0 02 ED 40 */	lfs f0, lbl_804DE720@sda21(r2)
/* 8037E83C 0037B41C  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8037E840 0037B420  EC 22 08 2A */	fadds f1, f2, f1
/* 8037E844 0037B424  EC 83 08 2A */	fadds f4, f3, f1
/* 8037E848 0037B428  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8037E84C 0037B42C  40 81 00 50 */	ble lbl_8037E89C
/* 8037E850 0037B430  FC 20 20 34 */	frsqrte f1, f4
/* 8037E854 0037B434  C8 62 ED 48 */	lfd f3, lbl_804DE728@sda21(r2)
/* 8037E858 0037B438  C8 42 ED 50 */	lfd f2, lbl_804DE730@sda21(r2)
/* 8037E85C 0037B43C  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E860 0037B440  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E864 0037B444  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E868 0037B448  FC 21 00 32 */	fmul f1, f1, f0
/* 8037E86C 0037B44C  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E870 0037B450  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E874 0037B454  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E878 0037B458  FC 21 00 32 */	fmul f1, f1, f0
/* 8037E87C 0037B45C  FC 01 00 72 */	fmul f0, f1, f1
/* 8037E880 0037B460  FC 23 00 72 */	fmul f1, f3, f1
/* 8037E884 0037B464  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037E888 0037B468  FC 01 00 32 */	fmul f0, f1, f0
/* 8037E88C 0037B46C  FC 04 00 32 */	fmul f0, f4, f0
/* 8037E890 0037B470  FC 00 00 18 */	frsp f0, f0
/* 8037E894 0037B474  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8037E898 0037B478  C0 81 00 18 */	lfs f4, 0x18(r1)
lbl_8037E89C:
/* 8037E89C 0037B47C  D0 81 00 2C */	stfs f4, 0x2c(r1)
/* 8037E8A0 0037B480  C0 63 00 00 */	lfs f3, 0(r3)
/* 8037E8A4 0037B484  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 8037E8A8 0037B488  C0 43 00 14 */	lfs f2, 0x14(r3)
/* 8037E8AC 0037B48C  EC A3 00 24 */	fdivs f5, f3, f0
/* 8037E8B0 0037B490  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 8037E8B4 0037B494  C0 83 00 28 */	lfs f4, 0x28(r3)
/* 8037E8B8 0037B498  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 8037E8BC 0037B49C  C0 62 ED 40 */	lfs f3, lbl_804DE720@sda21(r2)
/* 8037E8C0 0037B4A0  EC C2 08 24 */	fdivs f6, f2, f1
/* 8037E8C4 0037B4A4  EC E4 00 24 */	fdivs f7, f4, f0
/* 8037E8C8 0037B4A8  EC 45 30 2A */	fadds f2, f5, f6
/* 8037E8CC 0037B4AC  EC 87 10 2A */	fadds f4, f7, f2
/* 8037E8D0 0037B4B0  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 8037E8D4 0037B4B4  40 81 00 D0 */	ble lbl_8037E9A4
/* 8037E8D8 0037B4B8  C0 42 ED 58 */	lfs f2, lbl_804DE738@sda21(r2)
/* 8037E8DC 0037B4BC  EC C2 20 2A */	fadds f6, f2, f4
/* 8037E8E0 0037B4C0  FC 06 18 40 */	fcmpo cr0, f6, f3
/* 8037E8E4 0037B4C4  40 81 00 50 */	ble lbl_8037E934
/* 8037E8E8 0037B4C8  FC 60 30 34 */	frsqrte f3, f6
/* 8037E8EC 0037B4CC  C8 A2 ED 48 */	lfd f5, lbl_804DE728@sda21(r2)
/* 8037E8F0 0037B4D0  C8 82 ED 50 */	lfd f4, lbl_804DE730@sda21(r2)
/* 8037E8F4 0037B4D4  FC 43 00 F2 */	fmul f2, f3, f3
/* 8037E8F8 0037B4D8  FC 65 00 F2 */	fmul f3, f5, f3
/* 8037E8FC 0037B4DC  FC 46 20 BC */	fnmsub f2, f6, f2, f4
/* 8037E900 0037B4E0  FC 63 00 B2 */	fmul f3, f3, f2
/* 8037E904 0037B4E4  FC 43 00 F2 */	fmul f2, f3, f3
/* 8037E908 0037B4E8  FC 65 00 F2 */	fmul f3, f5, f3
/* 8037E90C 0037B4EC  FC 46 20 BC */	fnmsub f2, f6, f2, f4
/* 8037E910 0037B4F0  FC 63 00 B2 */	fmul f3, f3, f2
/* 8037E914 0037B4F4  FC 43 00 F2 */	fmul f2, f3, f3
/* 8037E918 0037B4F8  FC 65 00 F2 */	fmul f3, f5, f3
/* 8037E91C 0037B4FC  FC 46 20 BC */	fnmsub f2, f6, f2, f4
/* 8037E920 0037B500  FC 43 00 B2 */	fmul f2, f3, f2
/* 8037E924 0037B504  FC 46 00 B2 */	fmul f2, f6, f2
/* 8037E928 0037B508  FC 40 10 18 */	frsp f2, f2
/* 8037E92C 0037B50C  D0 41 00 14 */	stfs f2, 0x14(r1)
/* 8037E930 0037B510  C0 C1 00 14 */	lfs f6, 0x14(r1)
lbl_8037E934:
/* 8037E934 0037B514  C0 62 ED 5C */	lfs f3, lbl_804DE73C@sda21(r2)
/* 8037E938 0037B518  EC 43 01 B2 */	fmuls f2, f3, f6
/* 8037E93C 0037B51C  EC A3 30 24 */	fdivs f5, f3, f6
/* 8037E940 0037B520  D0 44 00 0C */	stfs f2, 0xc(r4)
/* 8037E944 0037B524  C0 63 00 24 */	lfs f3, 0x24(r3)
/* 8037E948 0037B528  C0 43 00 18 */	lfs f2, 0x18(r3)
/* 8037E94C 0037B52C  EC 63 08 24 */	fdivs f3, f3, f1
/* 8037E950 0037B530  EC 42 00 24 */	fdivs f2, f2, f0
/* 8037E954 0037B534  EC 43 10 28 */	fsubs f2, f3, f2
/* 8037E958 0037B538  EC 45 00 B2 */	fmuls f2, f5, f2
/* 8037E95C 0037B53C  D0 44 00 00 */	stfs f2, 0(r4)
/* 8037E960 0037B540  C0 83 00 08 */	lfs f4, 8(r3)
/* 8037E964 0037B544  C0 63 00 20 */	lfs f3, 0x20(r3)
/* 8037E968 0037B548  C0 41 00 24 */	lfs f2, 0x24(r1)
/* 8037E96C 0037B54C  EC 84 00 24 */	fdivs f4, f4, f0
/* 8037E970 0037B550  EC 03 10 24 */	fdivs f0, f3, f2
/* 8037E974 0037B554  EC 04 00 28 */	fsubs f0, f4, f0
/* 8037E978 0037B558  EC 05 00 32 */	fmuls f0, f5, f0
/* 8037E97C 0037B55C  D0 04 00 04 */	stfs f0, 4(r4)
/* 8037E980 0037B560  C0 03 00 04 */	lfs f0, 4(r3)
/* 8037E984 0037B564  C0 63 00 10 */	lfs f3, 0x10(r3)
/* 8037E988 0037B568  C0 41 00 24 */	lfs f2, 0x24(r1)
/* 8037E98C 0037B56C  EC 00 08 24 */	fdivs f0, f0, f1
/* 8037E990 0037B570  EC 23 10 24 */	fdivs f1, f3, f2
/* 8037E994 0037B574  EC 01 00 28 */	fsubs f0, f1, f0
/* 8037E998 0037B578  EC 05 00 32 */	fmuls f0, f5, f0
/* 8037E99C 0037B57C  D0 04 00 08 */	stfs f0, 8(r4)
/* 8037E9A0 0037B580  48 00 01 7C */	b lbl_8037EB1C
lbl_8037E9A4:
/* 8037E9A4 0037B584  FC 06 28 40 */	fcmpo cr0, f6, f5
/* 8037E9A8 0037B588  38 E0 00 00 */	li r7, 0
/* 8037E9AC 0037B58C  40 81 00 08 */	ble lbl_8037E9B4
/* 8037E9B0 0037B590  38 E0 00 01 */	li r7, 1
lbl_8037E9B4:
/* 8037E9B4 0037B594  54 E6 10 3A */	slwi r6, r7, 2
/* 8037E9B8 0037B598  54 E0 20 36 */	slwi r0, r7, 4
/* 8037E9BC 0037B59C  7C 00 32 14 */	add r0, r0, r6
/* 8037E9C0 0037B5A0  38 A1 00 24 */	addi r5, r1, 0x24
/* 8037E9C4 0037B5A4  7C 23 04 2E */	lfsx f1, r3, r0
/* 8037E9C8 0037B5A8  7C 05 34 2E */	lfsx f0, r5, r6
/* 8037E9CC 0037B5AC  EC 01 00 24 */	fdivs f0, f1, f0
/* 8037E9D0 0037B5B0  FC 07 00 40 */	fcmpo cr0, f7, f0
/* 8037E9D4 0037B5B4  40 81 00 08 */	ble lbl_8037E9DC
/* 8037E9D8 0037B5B8  38 E0 00 02 */	li r7, 2
lbl_8037E9DC:
/* 8037E9DC 0037B5BC  54 E8 10 3A */	slwi r8, r7, 2
/* 8037E9E0 0037B5C0  C0 E2 ED 58 */	lfs f7, lbl_804DE738@sda21(r2)
/* 8037E9E4 0037B5C4  38 C1 00 30 */	addi r6, r1, 0x30
/* 8037E9E8 0037B5C8  C0 62 ED 40 */	lfs f3, lbl_804DE720@sda21(r2)
/* 8037E9EC 0037B5CC  54 E0 20 36 */	slwi r0, r7, 4
/* 8037E9F0 0037B5D0  7D 26 40 2E */	lwzx r9, r6, r8
/* 8037E9F4 0037B5D4  7D 63 02 14 */	add r11, r3, r0
/* 8037E9F8 0037B5D8  55 27 10 3A */	slwi r7, r9, 2
/* 8037E9FC 0037B5DC  7C 0B 44 2E */	lfsx f0, r11, r8
/* 8037EA00 0037B5E0  38 A1 00 24 */	addi r5, r1, 0x24
/* 8037EA04 0037B5E4  7C C6 38 2E */	lwzx r6, r6, r7
/* 8037EA08 0037B5E8  55 20 20 36 */	slwi r0, r9, 4
/* 8037EA0C 0037B5EC  7C 45 44 2E */	lfsx f2, r5, r8
/* 8037EA10 0037B5F0  7D 23 02 14 */	add r9, r3, r0
/* 8037EA14 0037B5F4  7C 25 3C 2E */	lfsx f1, r5, r7
/* 8037EA18 0037B5F8  54 C0 20 36 */	slwi r0, r6, 4
/* 8037EA1C 0037B5FC  7C A9 3C 2E */	lfsx f5, r9, r7
/* 8037EA20 0037B600  54 C6 10 3A */	slwi r6, r6, 2
/* 8037EA24 0037B604  EC C0 10 24 */	fdivs f6, f0, f2
/* 8037EA28 0037B608  7D 43 02 14 */	add r10, r3, r0
/* 8037EA2C 0037B60C  7C 05 34 2E */	lfsx f0, r5, r6
/* 8037EA30 0037B610  7C 8A 34 2E */	lfsx f4, r10, r6
/* 8037EA34 0037B614  EC A5 08 24 */	fdivs f5, f5, f1
/* 8037EA38 0037B618  EC 84 00 24 */	fdivs f4, f4, f0
/* 8037EA3C 0037B61C  EC A6 28 28 */	fsubs f5, f6, f5
/* 8037EA40 0037B620  EC 85 20 28 */	fsubs f4, f5, f4
/* 8037EA44 0037B624  EC E7 20 2A */	fadds f7, f7, f4
/* 8037EA48 0037B628  FC 07 18 40 */	fcmpo cr0, f7, f3
/* 8037EA4C 0037B62C  40 81 00 50 */	ble lbl_8037EA9C
/* 8037EA50 0037B630  FC 80 38 34 */	frsqrte f4, f7
/* 8037EA54 0037B634  C8 C2 ED 48 */	lfd f6, lbl_804DE728@sda21(r2)
/* 8037EA58 0037B638  C8 A2 ED 50 */	lfd f5, lbl_804DE730@sda21(r2)
/* 8037EA5C 0037B63C  FC 64 01 32 */	fmul f3, f4, f4
/* 8037EA60 0037B640  FC 86 01 32 */	fmul f4, f6, f4
/* 8037EA64 0037B644  FC 67 28 FC */	fnmsub f3, f7, f3, f5
/* 8037EA68 0037B648  FC 84 00 F2 */	fmul f4, f4, f3
/* 8037EA6C 0037B64C  FC 64 01 32 */	fmul f3, f4, f4
/* 8037EA70 0037B650  FC 86 01 32 */	fmul f4, f6, f4
/* 8037EA74 0037B654  FC 67 28 FC */	fnmsub f3, f7, f3, f5
/* 8037EA78 0037B658  FC 84 00 F2 */	fmul f4, f4, f3
/* 8037EA7C 0037B65C  FC 64 01 32 */	fmul f3, f4, f4
/* 8037EA80 0037B660  FC 86 01 32 */	fmul f4, f6, f4
/* 8037EA84 0037B664  FC 67 28 FC */	fnmsub f3, f7, f3, f5
/* 8037EA88 0037B668  FC 64 00 F2 */	fmul f3, f4, f3
/* 8037EA8C 0037B66C  FC 67 00 F2 */	fmul f3, f7, f3
/* 8037EA90 0037B670  FC 60 18 18 */	frsp f3, f3
/* 8037EA94 0037B674  D0 61 00 10 */	stfs f3, 0x10(r1)
/* 8037EA98 0037B678  C0 E1 00 10 */	lfs f7, 0x10(r1)
lbl_8037EA9C:
/* 8037EA9C 0037B67C  C0 82 ED 5C */	lfs f4, lbl_804DE73C@sda21(r2)
/* 8037EAA0 0037B680  38 61 00 3C */	addi r3, r1, 0x3c
/* 8037EAA4 0037B684  EC 64 01 F2 */	fmuls f3, f4, f7
/* 8037EAA8 0037B688  EC A4 38 24 */	fdivs f5, f4, f7
/* 8037EAAC 0037B68C  7C 63 45 2E */	stfsx f3, r3, r8
/* 8037EAB0 0037B690  7C 8A 3C 2E */	lfsx f4, r10, r7
/* 8037EAB4 0037B694  7C 69 34 2E */	lfsx f3, r9, r6
/* 8037EAB8 0037B698  EC 84 08 24 */	fdivs f4, f4, f1
/* 8037EABC 0037B69C  EC 63 00 24 */	fdivs f3, f3, f0
/* 8037EAC0 0037B6A0  EC 64 18 28 */	fsubs f3, f4, f3
/* 8037EAC4 0037B6A4  EC 65 00 F2 */	fmuls f3, f5, f3
/* 8037EAC8 0037B6A8  D0 64 00 0C */	stfs f3, 0xc(r4)
/* 8037EACC 0037B6AC  7C 89 44 2E */	lfsx f4, r9, r8
/* 8037EAD0 0037B6B0  7C 6B 3C 2E */	lfsx f3, r11, r7
/* 8037EAD4 0037B6B4  EC 84 10 24 */	fdivs f4, f4, f2
/* 8037EAD8 0037B6B8  EC 23 08 24 */	fdivs f1, f3, f1
/* 8037EADC 0037B6BC  EC 24 08 2A */	fadds f1, f4, f1
/* 8037EAE0 0037B6C0  EC 25 00 72 */	fmuls f1, f5, f1
/* 8037EAE4 0037B6C4  7C 23 3D 2E */	stfsx f1, r3, r7
/* 8037EAE8 0037B6C8  7C 6A 44 2E */	lfsx f3, r10, r8
/* 8037EAEC 0037B6CC  7C 2B 34 2E */	lfsx f1, r11, r6
/* 8037EAF0 0037B6D0  EC 43 10 24 */	fdivs f2, f3, f2
/* 8037EAF4 0037B6D4  EC 01 00 24 */	fdivs f0, f1, f0
/* 8037EAF8 0037B6D8  EC 02 00 2A */	fadds f0, f2, f0
/* 8037EAFC 0037B6DC  EC 05 00 32 */	fmuls f0, f5, f0
/* 8037EB00 0037B6E0  7C 03 35 2E */	stfsx f0, r3, r6
/* 8037EB04 0037B6E4  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 8037EB08 0037B6E8  D0 04 00 00 */	stfs f0, 0(r4)
/* 8037EB0C 0037B6EC  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 8037EB10 0037B6F0  D0 04 00 04 */	stfs f0, 4(r4)
/* 8037EB14 0037B6F4  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 8037EB18 0037B6F8  D0 04 00 08 */	stfs f0, 8(r4)
lbl_8037EB1C:
/* 8037EB1C 0037B6FC  38 60 00 00 */	li r3, 0
/* 8037EB20 0037B700  38 21 00 48 */	addi r1, r1, 0x48
/* 8037EB24 0037B704  4E 80 00 20 */	blr 

.global func_8037EB28
func_8037EB28:
/* 8037EB28 0037B708  7C 08 02 A6 */	mflr r0
/* 8037EB2C 0037B70C  90 01 00 04 */	stw r0, 4(r1)
/* 8037EB30 0037B710  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8037EB34 0037B714  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8037EB38 0037B718  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8037EB3C 0037B71C  7C 9F 23 78 */	mr r31, r4
/* 8037EB40 0037B720  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8037EB44 0037B724  7C 7E 1B 78 */	mr r30, r3
/* 8037EB48 0037B728  C0 43 00 00 */	lfs f2, 0(r3)
/* 8037EB4C 0037B72C  C0 23 00 10 */	lfs f1, 0x10(r3)
/* 8037EB50 0037B730  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8037EB54 0037B734  C0 02 ED 40 */	lfs f0, lbl_804DE720@sda21(r2)
/* 8037EB58 0037B738  EC 21 00 72 */	fmuls f1, f1, f1
/* 8037EB5C 0037B73C  EC 82 08 2A */	fadds f4, f2, f1
/* 8037EB60 0037B740  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8037EB64 0037B744  40 81 00 50 */	ble lbl_8037EBB4
/* 8037EB68 0037B748  FC 20 20 34 */	frsqrte f1, f4
/* 8037EB6C 0037B74C  C8 62 ED 48 */	lfd f3, lbl_804DE728@sda21(r2)
/* 8037EB70 0037B750  C8 42 ED 50 */	lfd f2, lbl_804DE730@sda21(r2)
/* 8037EB74 0037B754  FC 01 00 72 */	fmul f0, f1, f1
/* 8037EB78 0037B758  FC 23 00 72 */	fmul f1, f3, f1
/* 8037EB7C 0037B75C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037EB80 0037B760  FC 21 00 32 */	fmul f1, f1, f0
/* 8037EB84 0037B764  FC 01 00 72 */	fmul f0, f1, f1
/* 8037EB88 0037B768  FC 23 00 72 */	fmul f1, f3, f1
/* 8037EB8C 0037B76C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037EB90 0037B770  FC 21 00 32 */	fmul f1, f1, f0
/* 8037EB94 0037B774  FC 01 00 72 */	fmul f0, f1, f1
/* 8037EB98 0037B778  FC 23 00 72 */	fmul f1, f3, f1
/* 8037EB9C 0037B77C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8037EBA0 0037B780  FC 01 00 32 */	fmul f0, f1, f0
/* 8037EBA4 0037B784  FC 04 00 32 */	fmul f0, f4, f0
/* 8037EBA8 0037B788  FC 00 00 18 */	frsp f0, f0
/* 8037EBAC 0037B78C  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8037EBB0 0037B790  C0 81 00 10 */	lfs f4, 0x10(r1)
lbl_8037EBB4:
/* 8037EBB4 0037B794  C8 02 ED 60 */	lfd f0, lbl_804DE740@sda21(r2)
/* 8037EBB8 0037B798  FF E0 20 90 */	fmr f31, f4
/* 8037EBBC 0037B79C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8037EBC0 0037B7A0  40 81 00 3C */	ble lbl_8037EBFC
/* 8037EBC4 0037B7A4  C0 3E 00 24 */	lfs f1, 0x24(r30)
/* 8037EBC8 0037B7A8  C0 5E 00 28 */	lfs f2, 0x28(r30)
/* 8037EBCC 0037B7AC  4B CA 40 65 */	bl func_80022C30
/* 8037EBD0 0037B7B0  D0 3F 00 00 */	stfs f1, 0(r31)
/* 8037EBD4 0037B7B4  FC 40 F8 90 */	fmr f2, f31
/* 8037EBD8 0037B7B8  C0 1E 00 20 */	lfs f0, 0x20(r30)
/* 8037EBDC 0037B7BC  FC 20 00 50 */	fneg f1, f0
/* 8037EBE0 0037B7C0  4B CA 40 51 */	bl func_80022C30
/* 8037EBE4 0037B7C4  D0 3F 00 04 */	stfs f1, 4(r31)
/* 8037EBE8 0037B7C8  C0 3E 00 10 */	lfs f1, 0x10(r30)
/* 8037EBEC 0037B7CC  C0 5E 00 00 */	lfs f2, 0(r30)
/* 8037EBF0 0037B7D0  4B CA 40 41 */	bl func_80022C30
/* 8037EBF4 0037B7D4  D0 3F 00 08 */	stfs f1, 8(r31)
/* 8037EBF8 0037B7D8  48 00 00 34 */	b lbl_8037EC2C
lbl_8037EBFC:
/* 8037EBFC 0037B7DC  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 8037EC00 0037B7E0  C0 5E 00 14 */	lfs f2, 0x14(r30)
/* 8037EC04 0037B7E4  FC 20 00 50 */	fneg f1, f0
/* 8037EC08 0037B7E8  4B CA 40 29 */	bl func_80022C30
/* 8037EC0C 0037B7EC  D0 3F 00 00 */	stfs f1, 0(r31)
/* 8037EC10 0037B7F0  FC 40 F8 90 */	fmr f2, f31
/* 8037EC14 0037B7F4  C0 1E 00 20 */	lfs f0, 0x20(r30)
/* 8037EC18 0037B7F8  FC 20 00 50 */	fneg f1, f0
/* 8037EC1C 0037B7FC  4B CA 40 15 */	bl func_80022C30
/* 8037EC20 0037B800  D0 3F 00 04 */	stfs f1, 4(r31)
/* 8037EC24 0037B804  C0 02 ED 40 */	lfs f0, lbl_804DE720@sda21(r2)
/* 8037EC28 0037B808  D0 1F 00 08 */	stfs f0, 8(r31)
lbl_8037EC2C:
/* 8037EC2C 0037B80C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8037EC30 0037B810  38 60 00 00 */	li r3, 0
/* 8037EC34 0037B814  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8037EC38 0037B818  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8037EC3C 0037B81C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8037EC40 0037B820  38 21 00 28 */	addi r1, r1, 0x28
/* 8037EC44 0037B824  7C 08 03 A6 */	mtlr r0
/* 8037EC48 0037B828  4E 80 00 20 */	blr 

.global func_8037EC4C
func_8037EC4C:
/* 8037EC4C 0037B82C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8037EC50 0037B830  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8037EC54 0037B834  C1 83 00 0C */	lfs f12, 0xc(r3)
/* 8037EC58 0037B838  C1 24 00 04 */	lfs f9, 4(r4)
/* 8037EC5C 0037B83C  C1 04 00 00 */	lfs f8, 0(r4)
/* 8037EC60 0037B840  C0 E3 00 04 */	lfs f7, 4(r3)
/* 8037EC64 0037B844  EC CC 02 72 */	fmuls f6, f12, f9
/* 8037EC68 0037B848  C1 A3 00 08 */	lfs f13, 8(r3)
/* 8037EC6C 0037B84C  EC 8C 02 32 */	fmuls f4, f12, f8
/* 8037EC70 0037B850  C1 43 00 00 */	lfs f10, 0(r3)
/* 8037EC74 0037B854  C1 64 00 08 */	lfs f11, 8(r4)
/* 8037EC78 0037B858  C3 E4 00 0C */	lfs f31, 0xc(r4)
/* 8037EC7C 0037B85C  EC 69 03 72 */	fmuls f3, f9, f13
/* 8037EC80 0037B860  EC AA 02 F2 */	fmuls f5, f10, f11
/* 8037EC84 0037B864  38 60 00 00 */	li r3, 0
/* 8037EC88 0037B868  EC 07 02 72 */	fmuls f0, f7, f9
/* 8037EC8C 0037B86C  EC 4C 02 F2 */	fmuls f2, f12, f11
/* 8037EC90 0037B870  EC 28 01 F2 */	fmuls f1, f8, f7
/* 8037EC94 0037B874  EC 0A 02 3A */	fmadds f0, f10, f8, f0
/* 8037EC98 0037B878  EC 9F 22 BA */	fmadds f4, f31, f10, f4
/* 8037EC9C 0037B87C  EC 67 1A F8 */	fmsubs f3, f7, f11, f3
/* 8037ECA0 0037B880  EC 0D 02 FA */	fmadds f0, f13, f11, f0
/* 8037ECA4 0037B884  EC DF 31 FA */	fmadds f6, f31, f7, f6
/* 8037ECA8 0037B888  EC 64 18 2A */	fadds f3, f4, f3
/* 8037ECAC 0037B88C  EC A8 2B 78 */	fmsubs f5, f8, f13, f5
/* 8037ECB0 0037B890  EC 5F 13 7A */	fmadds f2, f31, f13, f2
/* 8037ECB4 0037B894  EC 2A 0A 78 */	fmsubs f1, f10, f9, f1
/* 8037ECB8 0037B898  D0 65 00 00 */	stfs f3, 0(r5)
/* 8037ECBC 0037B89C  EC 86 28 2A */	fadds f4, f6, f5
/* 8037ECC0 0037B8A0  EC 0C 07 F8 */	fmsubs f0, f12, f31, f0
/* 8037ECC4 0037B8A4  EC 22 08 2A */	fadds f1, f2, f1
/* 8037ECC8 0037B8A8  D0 85 00 04 */	stfs f4, 4(r5)
/* 8037ECCC 0037B8AC  D0 25 00 08 */	stfs f1, 8(r5)
/* 8037ECD0 0037B8B0  D0 05 00 0C */	stfs f0, 0xc(r5)
/* 8037ECD4 0037B8B4  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8037ECD8 0037B8B8  38 21 00 38 */	addi r1, r1, 0x38
/* 8037ECDC 0037B8BC  4E 80 00 20 */	blr 

.global func_8037ECE0
func_8037ECE0:
/* 8037ECE0 0037B8C0  7C 08 02 A6 */	mflr r0
/* 8037ECE4 0037B8C4  90 01 00 04 */	stw r0, 4(r1)
/* 8037ECE8 0037B8C8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8037ECEC 0037B8CC  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8037ECF0 0037B8D0  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 8037ECF4 0037B8D4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8037ECF8 0037B8D8  7C 9F 23 78 */	mr r31, r4
/* 8037ECFC 0037B8DC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8037ED00 0037B8E0  7C 7E 1B 78 */	mr r30, r3
/* 8037ED04 0037B8E4  C0 63 00 00 */	lfs f3, 0(r3)
/* 8037ED08 0037B8E8  C0 43 00 04 */	lfs f2, 4(r3)
/* 8037ED0C 0037B8EC  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8037ED10 0037B8F0  C0 83 00 08 */	lfs f4, 8(r3)
/* 8037ED14 0037B8F4  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8037ED18 0037B8F8  C0 02 ED 40 */	lfs f0, lbl_804DE720@sda21(r2)
/* 8037ED1C 0037B8FC  EC 84 01 32 */	fmuls f4, f4, f4
/* 8037ED20 0037B900  EC 43 10 2A */	fadds f2, f3, f2
/* 8037ED24 0037B904  EC A4 10 2A */	fadds f5, f4, f2
/* 8037ED28 0037B908  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 8037ED2C 0037B90C  40 81 00 50 */	ble lbl_8037ED7C
/* 8037ED30 0037B910  FC 40 28 34 */	frsqrte f2, f5
/* 8037ED34 0037B914  C8 82 ED 48 */	lfd f4, lbl_804DE728@sda21(r2)
/* 8037ED38 0037B918  C8 62 ED 50 */	lfd f3, lbl_804DE730@sda21(r2)
/* 8037ED3C 0037B91C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037ED40 0037B920  FC 44 00 B2 */	fmul f2, f4, f2
/* 8037ED44 0037B924  FC 05 18 3C */	fnmsub f0, f5, f0, f3
/* 8037ED48 0037B928  FC 42 00 32 */	fmul f2, f2, f0
/* 8037ED4C 0037B92C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037ED50 0037B930  FC 44 00 B2 */	fmul f2, f4, f2
/* 8037ED54 0037B934  FC 05 18 3C */	fnmsub f0, f5, f0, f3
/* 8037ED58 0037B938  FC 42 00 32 */	fmul f2, f2, f0
/* 8037ED5C 0037B93C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037ED60 0037B940  FC 44 00 B2 */	fmul f2, f4, f2
/* 8037ED64 0037B944  FC 05 18 3C */	fnmsub f0, f5, f0, f3
/* 8037ED68 0037B948  FC 02 00 32 */	fmul f0, f2, f0
/* 8037ED6C 0037B94C  FC 05 00 32 */	fmul f0, f5, f0
/* 8037ED70 0037B950  FC 00 00 18 */	frsp f0, f0
/* 8037ED74 0037B954  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 8037ED78 0037B958  C0 A1 00 14 */	lfs f5, 0x14(r1)
lbl_8037ED7C:
/* 8037ED7C 0037B95C  FC 40 2A 10 */	fabs f2, f5
/* 8037ED80 0037B960  C0 02 ED 68 */	lfs f0, lbl_804DE748@sda21(r2)
/* 8037ED84 0037B964  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8037ED88 0037B968  40 80 00 0C */	bge lbl_8037ED94
/* 8037ED8C 0037B96C  38 60 FF FF */	li r3, -1
/* 8037ED90 0037B970  48 00 00 5C */	b lbl_8037EDEC
lbl_8037ED94:
/* 8037ED94 0037B974  C0 42 ED 58 */	lfs f2, lbl_804DE738@sda21(r2)
/* 8037ED98 0037B978  C0 02 ED 5C */	lfs f0, lbl_804DE73C@sda21(r2)
/* 8037ED9C 0037B97C  EF C2 28 24 */	fdivs f30, f2, f5
/* 8037EDA0 0037B980  EF E0 00 72 */	fmuls f31, f0, f1
/* 8037EDA4 0037B984  FC 20 F8 90 */	fmr f1, f31
/* 8037EDA8 0037B988  4B FA 74 99 */	bl cosf
/* 8037EDAC 0037B98C  D0 3F 00 0C */	stfs f1, 0xc(r31)
/* 8037EDB0 0037B990  FC 20 F8 90 */	fmr f1, f31
/* 8037EDB4 0037B994  4B FA 76 21 */	bl sinf
/* 8037EDB8 0037B998  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8037EDBC 0037B99C  38 60 00 00 */	li r3, 0
/* 8037EDC0 0037B9A0  EC 1E 00 32 */	fmuls f0, f30, f0
/* 8037EDC4 0037B9A4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037EDC8 0037B9A8  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8037EDCC 0037B9AC  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8037EDD0 0037B9B0  EC 1E 00 32 */	fmuls f0, f30, f0
/* 8037EDD4 0037B9B4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037EDD8 0037B9B8  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8037EDDC 0037B9BC  C0 1E 00 08 */	lfs f0, 8(r30)
/* 8037EDE0 0037B9C0  EC 1E 00 32 */	fmuls f0, f30, f0
/* 8037EDE4 0037B9C4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037EDE8 0037B9C8  D0 1F 00 08 */	stfs f0, 8(r31)
lbl_8037EDEC:
/* 8037EDEC 0037B9CC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8037EDF0 0037B9D0  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8037EDF4 0037B9D4  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 8037EDF8 0037B9D8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8037EDFC 0037B9DC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8037EE00 0037B9E0  38 21 00 30 */	addi r1, r1, 0x30
/* 8037EE04 0037B9E4  7C 08 03 A6 */	mtlr r0
/* 8037EE08 0037B9E8  4E 80 00 20 */	blr 

.global func_8037EE0C
func_8037EE0C:
/* 8037EE0C 0037B9EC  7C 08 02 A6 */	mflr r0
/* 8037EE10 0037B9F0  90 01 00 04 */	stw r0, 4(r1)
/* 8037EE14 0037B9F4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8037EE18 0037B9F8  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 8037EE1C 0037B9FC  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 8037EE20 0037BA00  DB A1 00 28 */	stfd f29, 0x28(r1)
/* 8037EE24 0037BA04  DB 81 00 20 */	stfd f28, 0x20(r1)
/* 8037EE28 0037BA08  DB 61 00 18 */	stfd f27, 0x18(r1)
/* 8037EE2C 0037BA0C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8037EE30 0037BA10  7C 9F 23 78 */	mr r31, r4
/* 8037EE34 0037BA14  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8037EE38 0037BA18  7C 7E 1B 78 */	mr r30, r3
/* 8037EE3C 0037BA1C  C0 22 ED 5C */	lfs f1, lbl_804DE73C@sda21(r2)
/* 8037EE40 0037BA20  C0 03 00 00 */	lfs f0, 0(r3)
/* 8037EE44 0037BA24  EC 21 00 32 */	fmuls f1, f1, f0
/* 8037EE48 0037BA28  4B FA 73 F9 */	bl cosf
/* 8037EE4C 0037BA2C  C0 42 ED 5C */	lfs f2, lbl_804DE73C@sda21(r2)
/* 8037EE50 0037BA30  FF A0 08 90 */	fmr f29, f1
/* 8037EE54 0037BA34  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8037EE58 0037BA38  EC 22 00 32 */	fmuls f1, f2, f0
/* 8037EE5C 0037BA3C  4B FA 73 E5 */	bl cosf
/* 8037EE60 0037BA40  C0 42 ED 5C */	lfs f2, lbl_804DE73C@sda21(r2)
/* 8037EE64 0037BA44  FF C0 08 90 */	fmr f30, f1
/* 8037EE68 0037BA48  C0 1E 00 08 */	lfs f0, 8(r30)
/* 8037EE6C 0037BA4C  EC 22 00 32 */	fmuls f1, f2, f0
/* 8037EE70 0037BA50  4B FA 73 D1 */	bl cosf
/* 8037EE74 0037BA54  C0 42 ED 5C */	lfs f2, lbl_804DE73C@sda21(r2)
/* 8037EE78 0037BA58  FF E0 08 90 */	fmr f31, f1
/* 8037EE7C 0037BA5C  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8037EE80 0037BA60  EC 22 00 32 */	fmuls f1, f2, f0
/* 8037EE84 0037BA64  4B FA 75 51 */	bl sinf
/* 8037EE88 0037BA68  C0 42 ED 5C */	lfs f2, lbl_804DE73C@sda21(r2)
/* 8037EE8C 0037BA6C  FF 60 08 90 */	fmr f27, f1
/* 8037EE90 0037BA70  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8037EE94 0037BA74  EC 22 00 32 */	fmuls f1, f2, f0
/* 8037EE98 0037BA78  4B FA 75 3D */	bl sinf
/* 8037EE9C 0037BA7C  C0 42 ED 5C */	lfs f2, lbl_804DE73C@sda21(r2)
/* 8037EEA0 0037BA80  FF 80 08 90 */	fmr f28, f1
/* 8037EEA4 0037BA84  C0 1E 00 08 */	lfs f0, 8(r30)
/* 8037EEA8 0037BA88  EC 22 00 32 */	fmuls f1, f2, f0
/* 8037EEAC 0037BA8C  4B FA 75 29 */	bl sinf
/* 8037EEB0 0037BA90  EC 9C 00 72 */	fmuls f4, f28, f1
/* 8037EEB4 0037BA94  38 60 00 00 */	li r3, 0
/* 8037EEB8 0037BA98  EC 5B 07 B2 */	fmuls f2, f27, f30
/* 8037EEBC 0037BA9C  EC 1B 07 32 */	fmuls f0, f27, f28
/* 8037EEC0 0037BAA0  EC FE 07 F2 */	fmuls f7, f30, f31
/* 8037EEC4 0037BAA4  EC 7B 01 32 */	fmuls f3, f27, f4
/* 8037EEC8 0037BAA8  EC BD 01 32 */	fmuls f5, f29, f4
/* 8037EECC 0037BAAC  EC 9D 07 32 */	fmuls f4, f29, f28
/* 8037EED0 0037BAB0  EC DD 19 FA */	fmadds f6, f29, f7, f3
/* 8037EED4 0037BAB4  EC 61 00 B2 */	fmuls f3, f1, f2
/* 8037EED8 0037BAB8  EC BB 29 F8 */	fmsubs f5, f27, f7, f5
/* 8037EEDC 0037BABC  D0 DF 00 0C */	stfs f6, 0xc(r31)
/* 8037EEE0 0037BAC0  EC 5D 07 B2 */	fmuls f2, f29, f30
/* 8037EEE4 0037BAC4  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037EEE8 0037BAC8  EC 7F 19 3A */	fmadds f3, f31, f4, f3
/* 8037EEEC 0037BACC  D0 BF 00 00 */	stfs f5, 0(r31)
/* 8037EEF0 0037BAD0  EC 01 00 B8 */	fmsubs f0, f1, f2, f0
/* 8037EEF4 0037BAD4  D0 7F 00 04 */	stfs f3, 4(r31)
/* 8037EEF8 0037BAD8  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8037EEFC 0037BADC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8037EF00 0037BAE0  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 8037EF04 0037BAE4  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 8037EF08 0037BAE8  CB A1 00 28 */	lfd f29, 0x28(r1)
/* 8037EF0C 0037BAEC  CB 81 00 20 */	lfd f28, 0x20(r1)
/* 8037EF10 0037BAF0  CB 61 00 18 */	lfd f27, 0x18(r1)
/* 8037EF14 0037BAF4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8037EF18 0037BAF8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8037EF1C 0037BAFC  38 21 00 40 */	addi r1, r1, 0x40
/* 8037EF20 0037BB00  7C 08 03 A6 */	mtlr r0
/* 8037EF24 0037BB04  4E 80 00 20 */	blr 

.global func_8037EF28
func_8037EF28:
/* 8037EF28 0037BB08  7C 08 02 A6 */	mflr r0
/* 8037EF2C 0037BB0C  90 01 00 04 */	stw r0, 4(r1)
/* 8037EF30 0037BB10  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8037EF34 0037BB14  DB E1 00 40 */	stfd f31, 0x40(r1)
/* 8037EF38 0037BB18  DB C1 00 38 */	stfd f30, 0x38(r1)
/* 8037EF3C 0037BB1C  FF C0 08 90 */	fmr f30, f1
/* 8037EF40 0037BB20  DB A1 00 30 */	stfd f29, 0x30(r1)
/* 8037EF44 0037BB24  DB 81 00 28 */	stfd f28, 0x28(r1)
/* 8037EF48 0037BB28  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8037EF4C 0037BB2C  7C BF 2B 78 */	mr r31, r5
/* 8037EF50 0037BB30  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8037EF54 0037BB34  7C 9E 23 78 */	mr r30, r4
/* 8037EF58 0037BB38  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8037EF5C 0037BB3C  7C 7D 1B 78 */	mr r29, r3
/* 8037EF60 0037BB40  C0 E3 00 04 */	lfs f7, 4(r3)
/* 8037EF64 0037BB44  C0 04 00 04 */	lfs f0, 4(r4)
/* 8037EF68 0037BB48  C0 43 00 00 */	lfs f2, 0(r3)
/* 8037EF6C 0037BB4C  EC 07 00 32 */	fmuls f0, f7, f0
/* 8037EF70 0037BB50  C0 24 00 00 */	lfs f1, 0(r4)
/* 8037EF74 0037BB54  C0 83 00 08 */	lfs f4, 8(r3)
/* 8037EF78 0037BB58  C0 C3 00 0C */	lfs f6, 0xc(r3)
/* 8037EF7C 0037BB5C  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8037EF80 0037BB60  C0 24 00 08 */	lfs f1, 8(r4)
/* 8037EF84 0037BB64  C0 A4 00 0C */	lfs f5, 0xc(r4)
/* 8037EF88 0037BB68  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8037EF8C 0037BB6C  C0 62 ED 58 */	lfs f3, lbl_804DE738@sda21(r2)
/* 8037EF90 0037BB70  C0 42 ED 6C */	lfs f2, lbl_804DE74C@sda21(r2)
/* 8037EF94 0037BB74  EC 26 01 7A */	fmadds f1, f6, f5, f0
/* 8037EF98 0037BB78  EC 03 08 2A */	fadds f0, f3, f1
/* 8037EF9C 0037BB7C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8037EFA0 0037BB80  40 81 00 A8 */	ble lbl_8037F048
/* 8037EFA4 0037BB84  EC 03 08 28 */	fsubs f0, f3, f1
/* 8037EFA8 0037BB88  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8037EFAC 0037BB8C  40 81 00 38 */	ble lbl_8037EFE4
/* 8037EFB0 0037BB90  4B CA 3D 6D */	bl func_80022D1C
/* 8037EFB4 0037BB94  FF 80 08 90 */	fmr f28, f1
/* 8037EFB8 0037BB98  4B FA 74 1D */	bl sinf
/* 8037EFBC 0037BB9C  C0 02 ED 58 */	lfs f0, lbl_804DE738@sda21(r2)
/* 8037EFC0 0037BBA0  FF A0 08 90 */	fmr f29, f1
/* 8037EFC4 0037BBA4  EC 00 F0 28 */	fsubs f0, f0, f30
/* 8037EFC8 0037BBA8  EC 20 07 32 */	fmuls f1, f0, f28
/* 8037EFCC 0037BBAC  4B FA 74 09 */	bl sinf
/* 8037EFD0 0037BBB0  EF E1 E8 24 */	fdivs f31, f1, f29
/* 8037EFD4 0037BBB4  EC 3E 07 32 */	fmuls f1, f30, f28
/* 8037EFD8 0037BBB8  4B FA 73 FD */	bl sinf
/* 8037EFDC 0037BBBC  EC 41 E8 24 */	fdivs f2, f1, f29
/* 8037EFE0 0037BBC0  48 00 00 14 */	b lbl_8037EFF4
lbl_8037EFE4:
/* 8037EFE4 0037BBC4  C8 02 ED 70 */	lfd f0, lbl_804DE750@sda21(r2)
/* 8037EFE8 0037BBC8  FC 40 F0 90 */	fmr f2, f30
/* 8037EFEC 0037BBCC  FF E0 F0 28 */	fsub f31, f0, f30
/* 8037EFF0 0037BBD0  FF E0 F8 18 */	frsp f31, f31
lbl_8037EFF4:
/* 8037EFF4 0037BBD4  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8037EFF8 0037BBD8  C0 3D 00 00 */	lfs f1, 0(r29)
/* 8037EFFC 0037BBDC  EC 02 00 32 */	fmuls f0, f2, f0
/* 8037F000 0037BBE0  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 8037F004 0037BBE4  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8037F008 0037BBE8  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8037F00C 0037BBEC  C0 3D 00 04 */	lfs f1, 4(r29)
/* 8037F010 0037BBF0  EC 02 00 32 */	fmuls f0, f2, f0
/* 8037F014 0037BBF4  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 8037F018 0037BBF8  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8037F01C 0037BBFC  C0 1E 00 08 */	lfs f0, 8(r30)
/* 8037F020 0037BC00  C0 3D 00 08 */	lfs f1, 8(r29)
/* 8037F024 0037BC04  EC 02 00 32 */	fmuls f0, f2, f0
/* 8037F028 0037BC08  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 8037F02C 0037BC0C  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8037F030 0037BC10  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 8037F034 0037BC14  C0 3D 00 0C */	lfs f1, 0xc(r29)
/* 8037F038 0037BC18  EC 02 00 32 */	fmuls f0, f2, f0
/* 8037F03C 0037BC1C  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 8037F040 0037BC20  D0 1F 00 0C */	stfs f0, 0xc(r31)
/* 8037F044 0037BC24  48 00 01 3C */	b lbl_8037F180
lbl_8037F048:
/* 8037F048 0037BC28  FC 00 38 50 */	fneg f0, f7
/* 8037F04C 0037BC2C  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8037F050 0037BC30  C0 1D 00 00 */	lfs f0, 0(r29)
/* 8037F054 0037BC34  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8037F058 0037BC38  C0 1D 00 0C */	lfs f0, 0xc(r29)
/* 8037F05C 0037BC3C  FC 00 00 50 */	fneg f0, f0
/* 8037F060 0037BC40  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8037F064 0037BC44  C0 1D 00 08 */	lfs f0, 8(r29)
/* 8037F068 0037BC48  D0 1F 00 0C */	stfs f0, 0xc(r31)
/* 8037F06C 0037BC4C  C0 02 ED 5C */	lfs f0, lbl_804DE73C@sda21(r2)
/* 8037F070 0037BC50  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8037F074 0037BC54  40 80 00 88 */	bge lbl_8037F0FC
/* 8037F078 0037BC58  C0 02 ED 80 */	lfs f0, lbl_804DE760@sda21(r2)
/* 8037F07C 0037BC5C  C8 22 ED 78 */	lfd f1, lbl_804DE758@sda21(r2)
/* 8037F080 0037BC60  EF A0 07 B2 */	fmuls f29, f0, f30
/* 8037F084 0037BC64  EC 03 E8 28 */	fsubs f0, f3, f29
/* 8037F088 0037BC68  FC 21 00 32 */	fmul f1, f1, f0
/* 8037F08C 0037BC6C  FC 20 08 18 */	frsp f1, f1
/* 8037F090 0037BC70  4B FA 73 45 */	bl sinf
/* 8037F094 0037BC74  C8 02 ED 78 */	lfd f0, lbl_804DE758@sda21(r2)
/* 8037F098 0037BC78  FF C0 08 90 */	fmr f30, f1
/* 8037F09C 0037BC7C  FC 20 07 72 */	fmul f1, f0, f29
/* 8037F0A0 0037BC80  FC 20 08 18 */	frsp f1, f1
/* 8037F0A4 0037BC84  4B FA 73 31 */	bl sinf
/* 8037F0A8 0037BC88  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8037F0AC 0037BC8C  C0 5D 00 00 */	lfs f2, 0(r29)
/* 8037F0B0 0037BC90  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F0B4 0037BC94  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F0B8 0037BC98  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8037F0BC 0037BC9C  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8037F0C0 0037BCA0  C0 5D 00 04 */	lfs f2, 4(r29)
/* 8037F0C4 0037BCA4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F0C8 0037BCA8  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F0CC 0037BCAC  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8037F0D0 0037BCB0  C0 1E 00 08 */	lfs f0, 8(r30)
/* 8037F0D4 0037BCB4  C0 5D 00 08 */	lfs f2, 8(r29)
/* 8037F0D8 0037BCB8  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F0DC 0037BCBC  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F0E0 0037BCC0  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8037F0E4 0037BCC4  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 8037F0E8 0037BCC8  C0 5D 00 0C */	lfs f2, 0xc(r29)
/* 8037F0EC 0037BCCC  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F0F0 0037BCD0  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F0F4 0037BCD4  D0 1F 00 0C */	stfs f0, 0xc(r31)
/* 8037F0F8 0037BCD8  48 00 00 88 */	b lbl_8037F180
lbl_8037F0FC:
/* 8037F0FC 0037BCDC  EF DE 00 28 */	fsubs f30, f30, f0
/* 8037F100 0037BCE0  C0 02 ED 80 */	lfs f0, lbl_804DE760@sda21(r2)
/* 8037F104 0037BCE4  C8 22 ED 78 */	lfd f1, lbl_804DE758@sda21(r2)
/* 8037F108 0037BCE8  EF A0 07 B2 */	fmuls f29, f0, f30
/* 8037F10C 0037BCEC  EC 03 E8 28 */	fsubs f0, f3, f29
/* 8037F110 0037BCF0  FC 21 00 32 */	fmul f1, f1, f0
/* 8037F114 0037BCF4  FC 20 08 18 */	frsp f1, f1
/* 8037F118 0037BCF8  4B FA 72 BD */	bl sinf
/* 8037F11C 0037BCFC  C8 02 ED 78 */	lfd f0, lbl_804DE758@sda21(r2)
/* 8037F120 0037BD00  FF C0 08 90 */	fmr f30, f1
/* 8037F124 0037BD04  FC 20 07 72 */	fmul f1, f0, f29
/* 8037F128 0037BD08  FC 20 08 18 */	frsp f1, f1
/* 8037F12C 0037BD0C  4B FA 72 A9 */	bl sinf
/* 8037F130 0037BD10  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8037F134 0037BD14  C0 5D 00 00 */	lfs f2, 0(r29)
/* 8037F138 0037BD18  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F13C 0037BD1C  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F140 0037BD20  D0 1F 00 00 */	stfs f0, 0(r31)
/* 8037F144 0037BD24  C0 1E 00 04 */	lfs f0, 4(r30)
/* 8037F148 0037BD28  C0 5D 00 04 */	lfs f2, 4(r29)
/* 8037F14C 0037BD2C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F150 0037BD30  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F154 0037BD34  D0 1F 00 04 */	stfs f0, 4(r31)
/* 8037F158 0037BD38  C0 1E 00 08 */	lfs f0, 8(r30)
/* 8037F15C 0037BD3C  C0 5D 00 08 */	lfs f2, 8(r29)
/* 8037F160 0037BD40  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F164 0037BD44  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F168 0037BD48  D0 1F 00 08 */	stfs f0, 8(r31)
/* 8037F16C 0037BD4C  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 8037F170 0037BD50  C0 5D 00 0C */	lfs f2, 0xc(r29)
/* 8037F174 0037BD54  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037F178 0037BD58  EC 1E 00 BA */	fmadds f0, f30, f2, f0
/* 8037F17C 0037BD5C  D0 1F 00 0C */	stfs f0, 0xc(r31)
lbl_8037F180:
/* 8037F180 0037BD60  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8037F184 0037BD64  38 60 00 00 */	li r3, 0
/* 8037F188 0037BD68  CB E1 00 40 */	lfd f31, 0x40(r1)
/* 8037F18C 0037BD6C  CB C1 00 38 */	lfd f30, 0x38(r1)
/* 8037F190 0037BD70  CB A1 00 30 */	lfd f29, 0x30(r1)
/* 8037F194 0037BD74  CB 81 00 28 */	lfd f28, 0x28(r1)
/* 8037F198 0037BD78  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8037F19C 0037BD7C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8037F1A0 0037BD80  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8037F1A4 0037BD84  38 21 00 48 */	addi r1, r1, 0x48
/* 8037F1A8 0037BD88  7C 08 03 A6 */	mtlr r0
/* 8037F1AC 0037BD8C  4E 80 00 20 */	blr 


.section .rodata
    .balign 8
.global lbl_803B95E8
lbl_803B95E8:
	.long 1
    .long 2
    .long 0


.section .sdata2
    .balign 8
.global lbl_804DE720
lbl_804DE720:
	.4byte 0x00000000
	.4byte 0x00000000
.global lbl_804DE728
lbl_804DE728:
	.4byte 0x3FE00000
	.4byte 0x00000000
.global lbl_804DE730
lbl_804DE730:
	.4byte 0x40080000
	.4byte 0x00000000
.global lbl_804DE738
lbl_804DE738:
	.4byte 0x3F800000
.global lbl_804DE73C
lbl_804DE73C:
	.4byte 0x3F000000
.global lbl_804DE740
lbl_804DE740:
	.4byte 0x3EE4F8B5
	.4byte 0x88E368F1
.global lbl_804DE748
lbl_804DE748:
	.4byte 0x00800000
.global lbl_804DE74C
lbl_804DE74C:
	.4byte 0x2EDBE6FF
.global lbl_804DE750
lbl_804DE750:
	.4byte 0x3FF00000
	.4byte 0x00000000
.global lbl_804DE758
lbl_804DE758:
	.4byte 0x3FF921FB
	.4byte 0x54442D18
.global lbl_804DE760
lbl_804DE760:
	.4byte 0x40000000
	.4byte 0x00000000
