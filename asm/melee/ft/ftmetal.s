.include "macros.inc"

.section .text

.global ft_800C8170
ft_800C8170:
/* 800C8170 000C4D50  7C 08 02 A6 */	mflr r0
/* 800C8174 000C4D54  3C A0 80 3C */	lis r5, .L_803C6CF8@ha
/* 800C8178 000C4D58  90 01 00 04 */	stw r0, 4(r1)
/* 800C817C 000C4D5C  3C 80 80 3C */	lis r4, .L_803C6D24@ha
/* 800C8180 000C4D60  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800C8184 000C4D64  BE 81 00 18 */	stmw r20, 0x18(r1)
/* 800C8188 000C4D68  3A A3 00 00 */	addi r21, r3, 0
/* 800C818C 000C4D6C  3B E5 6C F8 */	addi r31, r5, .L_803C6CF8@l
/* 800C8190 000C4D70  3A 84 6D 24 */	addi r20, r4, .L_803C6D24@l
/* 800C8194 000C4D74  3B 20 00 00 */	li r25, 0
/* 800C8198 000C4D78  3B 60 00 00 */	li r27, 0
/* 800C819C 000C4D7C  3F C0 60 00 */	lis r30, 0x6000
/* 800C81A0 000C4D80  3F A0 40 00 */	lis r29, 0x4000
/* 800C81A4 000C4D84  3F 80 00 05 */	lis r28, 5
/* 800C81A8 000C4D88  48 00 01 70 */	b .L_800C8318
.L_800C81AC:
/* 800C81AC 000C4D8C  80 15 05 E8 */	lwz r0, 0x5e8(r21)
/* 800C81B0 000C4D90  7F 40 DA 14 */	add r26, r0, r27
/* 800C81B4 000C4D94  88 1A 00 08 */	lbz r0, 8(r26)
/* 800C81B8 000C4D98  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 800C81BC 000C4D9C  41 82 01 54 */	beq .L_800C8310
/* 800C81C0 000C4DA0  83 1A 00 00 */	lwz r24, 0(r26)
/* 800C81C4 000C4DA4  7F 03 C3 78 */	mr r3, r24
/* 800C81C8 000C4DA8  48 2A 9A 25 */	bl HSD_JObjGetDObj
/* 800C81CC 000C4DAC  88 1A 00 08 */	lbz r0, 8(r26)
/* 800C81D0 000C4DB0  3A E3 00 00 */	addi r23, r3, 0
/* 800C81D4 000C4DB4  3A C0 00 00 */	li r22, 0
/* 800C81D8 000C4DB8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800C81DC 000C4DBC  41 82 00 08 */	beq .L_800C81E4
/* 800C81E0 000C4DC0  62 D6 00 80 */	ori r22, r22, 0x80
.L_800C81E4:
/* 800C81E4 000C4DC4  88 1A 00 09 */	lbz r0, 9(r26)
/* 800C81E8 000C4DC8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800C81EC 000C4DCC  41 82 00 08 */	beq .L_800C81F4
/* 800C81F0 000C4DD0  62 D6 01 00 */	ori r22, r22, 0x100
.L_800C81F4:
/* 800C81F4 000C4DD4  88 1A 00 09 */	lbz r0, 9(r26)
/* 800C81F8 000C4DD8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 800C81FC 000C4DDC  41 82 00 08 */	beq .L_800C8204
/* 800C8200 000C4DE0  66 D6 00 01 */	oris r22, r22, 1
.L_800C8204:
/* 800C8204 000C4DE4  88 1A 00 09 */	lbz r0, 9(r26)
/* 800C8208 000C4DE8  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800C820C 000C4DEC  41 82 00 08 */	beq .L_800C8214
/* 800C8210 000C4DF0  66 D6 00 04 */	oris r22, r22, 4
.L_800C8214:
/* 800C8214 000C4DF4  88 1A 00 09 */	lbz r0, 9(r26)
/* 800C8218 000C4DF8  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800C821C 000C4DFC  41 82 00 08 */	beq .L_800C8224
/* 800C8220 000C4E00  66 D6 00 10 */	oris r22, r22, 0x10
.L_800C8224:
/* 800C8224 000C4E04  88 1A 00 09 */	lbz r0, 9(r26)
/* 800C8228 000C4E08  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800C822C 000C4E0C  41 82 00 08 */	beq .L_800C8234
/* 800C8230 000C4E10  66 D6 00 08 */	oris r22, r22, 8
.L_800C8234:
/* 800C8234 000C4E14  38 78 00 00 */	addi r3, r24, 0
/* 800C8238 000C4E18  38 9C 01 80 */	addi r4, r28, 0x180
/* 800C823C 000C4E1C  48 2A 9C C5 */	bl HSD_JObjClearFlags
/* 800C8240 000C4E20  38 78 00 00 */	addi r3, r24, 0
/* 800C8244 000C4E24  38 96 00 00 */	addi r4, r22, 0
/* 800C8248 000C4E28  48 2A 9A B9 */	bl HSD_JObjSetFlags
/* 800C824C 000C4E2C  48 00 00 BC */	b .L_800C8308
.L_800C8250:
/* 800C8250 000C4E30  28 17 00 00 */	cmplwi r23, 0
/* 800C8254 000C4E34  41 82 00 0C */	beq .L_800C8260
/* 800C8258 000C4E38  80 77 00 08 */	lwz r3, 8(r23)
/* 800C825C 000C4E3C  48 00 00 08 */	b .L_800C8264
.L_800C8260:
/* 800C8260 000C4E40  38 60 00 00 */	li r3, 0
.L_800C8264:
/* 800C8264 000C4E44  80 03 00 04 */	lwz r0, 4(r3)
/* 800C8268 000C4E48  54 00 00 44 */	rlwinm r0, r0, 0, 1, 2
/* 800C826C 000C4E4C  7C 00 E8 00 */	cmpw r0, r29
/* 800C8270 000C4E50  41 82 00 34 */	beq .L_800C82A4
/* 800C8274 000C4E54  40 80 00 10 */	bge .L_800C8284
/* 800C8278 000C4E58  2C 00 00 00 */	cmpwi r0, 0
/* 800C827C 000C4E5C  41 82 00 14 */	beq .L_800C8290
/* 800C8280 000C4E60  48 00 00 4C */	b .L_800C82CC
.L_800C8284:
/* 800C8284 000C4E64  7C 00 F0 00 */	cmpw r0, r30
/* 800C8288 000C4E68  41 82 00 30 */	beq .L_800C82B8
/* 800C828C 000C4E6C  48 00 00 40 */	b .L_800C82CC
.L_800C8290:
/* 800C8290 000C4E70  38 77 00 00 */	addi r3, r23, 0
/* 800C8294 000C4E74  38 80 00 02 */	li r4, 2
/* 800C8298 000C4E78  38 A0 00 0E */	li r5, 0xe
/* 800C829C 000C4E7C  48 29 5B 4D */	bl HSD_DObjModifyFlags
/* 800C82A0 000C4E80  48 00 00 50 */	b .L_800C82F0
.L_800C82A4:
/* 800C82A4 000C4E84  38 77 00 00 */	addi r3, r23, 0
/* 800C82A8 000C4E88  38 80 00 08 */	li r4, 8
/* 800C82AC 000C4E8C  38 A0 00 0E */	li r5, 0xe
/* 800C82B0 000C4E90  48 29 5B 39 */	bl HSD_DObjModifyFlags
/* 800C82B4 000C4E94  48 00 00 3C */	b .L_800C82F0
.L_800C82B8:
/* 800C82B8 000C4E98  38 77 00 00 */	addi r3, r23, 0
/* 800C82BC 000C4E9C  38 80 00 04 */	li r4, 4
/* 800C82C0 000C4EA0  38 A0 00 0E */	li r5, 0xe
/* 800C82C4 000C4EA4  48 29 5B 25 */	bl HSD_DObjModifyFlags
/* 800C82C8 000C4EA8  48 00 00 28 */	b .L_800C82F0
.L_800C82CC:
/* 800C82CC 000C4EAC  80 97 00 08 */	lwz r4, 8(r23)
/* 800C82D0 000C4EB0  38 7F 00 00 */	addi r3, r31, 0
/* 800C82D4 000C4EB4  4C C6 31 82 */	crclr 6
/* 800C82D8 000C4EB8  80 84 00 04 */	lwz r4, 4(r4)
/* 800C82DC 000C4EBC  48 27 D3 CD */	bl OSReport
/* 800C82E0 000C4EC0  38 74 00 00 */	addi r3, r20, 0
/* 800C82E4 000C4EC4  38 80 00 73 */	li r4, 0x73
/* 800C82E8 000C4EC8  38 AD 85 F0 */	addi r5, r13, ftCo_804D3C90@sda21
/* 800C82EC 000C4ECC  48 2B FF 8D */	bl HSD_Panic
.L_800C82F0:
/* 800C82F0 000C4ED0  28 17 00 00 */	cmplwi r23, 0
/* 800C82F4 000C4ED4  41 82 00 0C */	beq .L_800C8300
/* 800C82F8 000C4ED8  80 17 00 04 */	lwz r0, 4(r23)
/* 800C82FC 000C4EDC  48 00 00 08 */	b .L_800C8304
.L_800C8300:
/* 800C8300 000C4EE0  38 00 00 00 */	li r0, 0
.L_800C8304:
/* 800C8304 000C4EE4  7C 17 03 78 */	mr r23, r0
.L_800C8308:
/* 800C8308 000C4EE8  28 17 00 00 */	cmplwi r23, 0
/* 800C830C 000C4EEC  40 82 FF 44 */	bne .L_800C8250
.L_800C8310:
/* 800C8310 000C4EF0  3B 7B 00 10 */	addi r27, r27, 0x10
/* 800C8314 000C4EF4  3B 39 00 01 */	addi r25, r25, 1
.L_800C8318:
/* 800C8318 000C4EF8  80 15 00 04 */	lwz r0, 4(r21)
/* 800C831C 000C4EFC  80 6D AE A4 */	lwz r3, ftPartsTable@sda21(r13)
/* 800C8320 000C4F00  54 00 10 3A */	slwi r0, r0, 2
/* 800C8324 000C4F04  7C 63 00 2E */	lwzx r3, r3, r0
/* 800C8328 000C4F08  80 03 00 08 */	lwz r0, 8(r3)
/* 800C832C 000C4F0C  7C 19 00 40 */	cmplw r25, r0
/* 800C8330 000C4F10  41 80 FE 7C */	blt .L_800C81AC
/* 800C8334 000C4F14  BA 81 00 18 */	lmw r20, 0x18(r1)
/* 800C8338 000C4F18  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800C833C 000C4F1C  38 21 00 48 */	addi r1, r1, 0x48
/* 800C8340 000C4F20  7C 08 03 A6 */	mtlr r0
/* 800C8344 000C4F24  4E 80 00 20 */	blr

.global ftCo_800C8348
ftCo_800C8348:
/* 800C8348 000C4F28  7C 08 02 A6 */	mflr r0
/* 800C834C 000C4F2C  90 01 00 04 */	stw r0, 4(r1)
/* 800C8350 000C4F30  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C8354 000C4F34  BF 41 00 28 */	stmw r26, 0x28(r1)
/* 800C8358 000C4F38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C835C 000C4F3C  90 9F 20 28 */	stw r4, 0x2028(r31)
/* 800C8360 000C4F40  90 BF 20 2C */	stw r5, 0x202c(r31)
/* 800C8364 000C4F44  88 7F 22 23 */	lbz r3, 0x2223(r31)
/* 800C8368 000C4F48  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 800C836C 000C4F4C  40 82 00 B8 */	bne .L_800C8424
/* 800C8370 000C4F50  38 00 00 01 */	li r0, 1
/* 800C8374 000C4F54  50 03 07 FE */	rlwimi r3, r0, 0, 0x1f, 0x1f
/* 800C8378 000C4F58  3B 80 00 00 */	li r28, 0
/* 800C837C 000C4F5C  98 7F 22 23 */	stb r3, 0x2223(r31)
/* 800C8380 000C4F60  3B 5C 00 00 */	addi r26, r28, 0
/* 800C8384 000C4F64  3F C0 00 05 */	lis r30, 5
/* 800C8388 000C4F68  48 00 00 78 */	b .L_800C8400
.L_800C838C:
/* 800C838C 000C4F6C  80 1F 05 E8 */	lwz r0, 0x5e8(r31)
/* 800C8390 000C4F70  7C 60 D2 14 */	add r3, r0, r26
/* 800C8394 000C4F74  88 03 00 08 */	lbz r0, 8(r3)
/* 800C8398 000C4F78  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 800C839C 000C4F7C  41 82 00 5C */	beq .L_800C83F8
/* 800C83A0 000C4F80  83 A3 00 00 */	lwz r29, 0(r3)
/* 800C83A4 000C4F84  7F A3 EB 78 */	mr r3, r29
/* 800C83A8 000C4F88  48 2A 98 45 */	bl HSD_JObjGetDObj
/* 800C83AC 000C4F8C  3B 63 00 00 */	addi r27, r3, 0
/* 800C83B0 000C4F90  38 7D 00 00 */	addi r3, r29, 0
/* 800C83B4 000C4F94  38 9E 01 80 */	addi r4, r30, 0x180
/* 800C83B8 000C4F98  48 2A 99 49 */	bl HSD_JObjSetFlags
/* 800C83BC 000C4F9C  38 7D 00 00 */	addi r3, r29, 0
/* 800C83C0 000C4FA0  3C 80 00 18 */	lis r4, 0x18
/* 800C83C4 000C4FA4  48 2A 9B 3D */	bl HSD_JObjClearFlags
/* 800C83C8 000C4FA8  48 00 00 28 */	b .L_800C83F0
.L_800C83CC:
/* 800C83CC 000C4FAC  38 7B 00 00 */	addi r3, r27, 0
/* 800C83D0 000C4FB0  38 80 00 02 */	li r4, 2
/* 800C83D4 000C4FB4  38 A0 00 0E */	li r5, 0xe
/* 800C83D8 000C4FB8  48 29 5A 11 */	bl HSD_DObjModifyFlags
/* 800C83DC 000C4FBC  28 1B 00 00 */	cmplwi r27, 0
/* 800C83E0 000C4FC0  41 82 00 0C */	beq .L_800C83EC
/* 800C83E4 000C4FC4  83 7B 00 04 */	lwz r27, 4(r27)
/* 800C83E8 000C4FC8  48 00 00 08 */	b .L_800C83F0
.L_800C83EC:
/* 800C83EC 000C4FCC  3B 60 00 00 */	li r27, 0
.L_800C83F0:
/* 800C83F0 000C4FD0  28 1B 00 00 */	cmplwi r27, 0
/* 800C83F4 000C4FD4  40 82 FF D8 */	bne .L_800C83CC
.L_800C83F8:
/* 800C83F8 000C4FD8  3B 5A 00 10 */	addi r26, r26, 0x10
/* 800C83FC 000C4FDC  3B 9C 00 01 */	addi r28, r28, 1
.L_800C8400:
/* 800C8400 000C4FE0  80 1F 00 04 */	lwz r0, 4(r31)
/* 800C8404 000C4FE4  80 6D AE A4 */	lwz r3, ftPartsTable@sda21(r13)
/* 800C8408 000C4FE8  54 00 10 3A */	slwi r0, r0, 2
/* 800C840C 000C4FEC  7C 63 00 2E */	lwzx r3, r3, r0
/* 800C8410 000C4FF0  80 03 00 08 */	lwz r0, 8(r3)
/* 800C8414 000C4FF4  7C 1C 00 40 */	cmplw r28, r0
/* 800C8418 000C4FF8  41 80 FF 74 */	blt .L_800C838C
/* 800C841C 000C4FFC  7F E3 FB 78 */	mr r3, r31
/* 800C8420 000C5000  4B FB 80 41 */	bl ftCommon_80080460
.L_800C8424:
/* 800C8424 000C5004  BB 41 00 28 */	lmw r26, 0x28(r1)
/* 800C8428 000C5008  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C842C 000C500C  38 21 00 40 */	addi r1, r1, 0x40
/* 800C8430 000C5010  7C 08 03 A6 */	mtlr r0
/* 800C8434 000C5014  4E 80 00 20 */	blr

.global ftCo_800C8438
ftCo_800C8438:
/* 800C8438 000C5018  7C 08 02 A6 */	mflr r0
/* 800C843C 000C501C  90 01 00 04 */	stw r0, 4(r1)
/* 800C8440 000C5020  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C8444 000C5024  BF 21 00 24 */	stmw r25, 0x24(r1)
/* 800C8448 000C5028  7C 7D 1B 78 */	mr r29, r3
/* 800C844C 000C502C  3B E0 00 00 */	li r31, 0
/* 800C8450 000C5030  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800C8454 000C5034  88 7E 22 23 */	lbz r3, 0x2223(r30)
/* 800C8458 000C5038  50 63 FF FE */	rlwimi r3, r3, 0x1f, 0x1f, 0x1f
/* 800C845C 000C503C  98 7E 22 23 */	stb r3, 0x2223(r30)
/* 800C8460 000C5040  93 FE 20 28 */	stw r31, 0x2028(r30)
/* 800C8464 000C5044  93 FE 20 2C */	stw r31, 0x202c(r30)
/* 800C8468 000C5048  88 1E 22 23 */	lbz r0, 0x2223(r30)
/* 800C846C 000C504C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800C8470 000C5050  41 82 00 BC */	beq .L_800C852C
/* 800C8474 000C5054  3B 3F 00 00 */	addi r25, r31, 0
/* 800C8478 000C5058  3F 80 00 05 */	lis r28, 5
/* 800C847C 000C505C  48 00 00 78 */	b .L_800C84F4
.L_800C8480:
/* 800C8480 000C5060  80 1E 05 E8 */	lwz r0, 0x5e8(r30)
/* 800C8484 000C5064  7C 60 CA 14 */	add r3, r0, r25
/* 800C8488 000C5068  88 03 00 08 */	lbz r0, 8(r3)
/* 800C848C 000C506C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 800C8490 000C5070  41 82 00 5C */	beq .L_800C84EC
/* 800C8494 000C5074  83 63 00 00 */	lwz r27, 0(r3)
/* 800C8498 000C5078  7F 63 DB 78 */	mr r3, r27
/* 800C849C 000C507C  48 2A 97 51 */	bl HSD_JObjGetDObj
/* 800C84A0 000C5080  3B 43 00 00 */	addi r26, r3, 0
/* 800C84A4 000C5084  38 7B 00 00 */	addi r3, r27, 0
/* 800C84A8 000C5088  38 9C 01 80 */	addi r4, r28, 0x180
/* 800C84AC 000C508C  48 2A 98 55 */	bl HSD_JObjSetFlags
/* 800C84B0 000C5090  38 7B 00 00 */	addi r3, r27, 0
/* 800C84B4 000C5094  3C 80 00 18 */	lis r4, 0x18
/* 800C84B8 000C5098  48 2A 9A 49 */	bl HSD_JObjClearFlags
/* 800C84BC 000C509C  48 00 00 28 */	b .L_800C84E4
.L_800C84C0:
/* 800C84C0 000C50A0  38 7A 00 00 */	addi r3, r26, 0
/* 800C84C4 000C50A4  38 80 00 02 */	li r4, 2
/* 800C84C8 000C50A8  38 A0 00 0E */	li r5, 0xe
/* 800C84CC 000C50AC  48 29 59 1D */	bl HSD_DObjModifyFlags
/* 800C84D0 000C50B0  28 1A 00 00 */	cmplwi r26, 0
/* 800C84D4 000C50B4  41 82 00 0C */	beq .L_800C84E0
/* 800C84D8 000C50B8  83 5A 00 04 */	lwz r26, 4(r26)
/* 800C84DC 000C50BC  48 00 00 08 */	b .L_800C84E4
.L_800C84E0:
/* 800C84E0 000C50C0  3B 40 00 00 */	li r26, 0
.L_800C84E4:
/* 800C84E4 000C50C4  28 1A 00 00 */	cmplwi r26, 0
/* 800C84E8 000C50C8  40 82 FF D8 */	bne .L_800C84C0
.L_800C84EC:
/* 800C84EC 000C50CC  3B 39 00 10 */	addi r25, r25, 0x10
/* 800C84F0 000C50D0  3B FF 00 01 */	addi r31, r31, 1
.L_800C84F4:
/* 800C84F4 000C50D4  80 1E 00 04 */	lwz r0, 4(r30)
/* 800C84F8 000C50D8  80 6D AE A4 */	lwz r3, ftPartsTable@sda21(r13)
/* 800C84FC 000C50DC  54 00 10 3A */	slwi r0, r0, 2
/* 800C8500 000C50E0  7C 63 00 2E */	lwzx r3, r3, r0
/* 800C8504 000C50E4  80 03 00 08 */	lwz r0, 8(r3)
/* 800C8508 000C50E8  7C 1F 00 40 */	cmplw r31, r0
/* 800C850C 000C50EC  41 80 FF 74 */	blt .L_800C8480
/* 800C8510 000C50F0  7F C3 F3 78 */	mr r3, r30
/* 800C8514 000C50F4  4B FB 7F 4D */	bl ftCommon_80080460
/* 800C8518 000C50F8  7F A3 EB 78 */	mr r3, r29
/* 800C851C 000C50FC  48 00 8B 41 */	bl ftCo_800D105C
/* 800C8520 000C5100  7F A3 EB 78 */	mr r3, r29
/* 800C8524 000C5104  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 800C8528 000C5108  4B FB 97 61 */	bl ft_80081C88
.L_800C852C:
/* 800C852C 000C510C  BB 21 00 24 */	lmw r25, 0x24(r1)
/* 800C8530 000C5110  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C8534 000C5114  38 21 00 40 */	addi r1, r1, 0x40
/* 800C8538 000C5118  7C 08 03 A6 */	mtlr r0
/* 800C853C 000C511C  4E 80 00 20 */	blr

.global ftCo_800C8540
ftCo_800C8540:
/* 800C8540 000C5120  7C 08 02 A6 */	mflr r0
/* 800C8544 000C5124  38 80 00 00 */	li r4, 0
/* 800C8548 000C5128  90 01 00 04 */	stw r0, 4(r1)
/* 800C854C 000C512C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C8550 000C5130  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C8554 000C5134  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800C8558 000C5138  7C 7E 1B 78 */	mr r30, r3
/* 800C855C 000C513C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C8560 000C5140  90 9F 20 28 */	stw r4, 0x2028(r31)
/* 800C8564 000C5144  90 9F 20 2C */	stw r4, 0x202c(r31)
/* 800C8568 000C5148  88 7F 22 23 */	lbz r3, 0x2223(r31)
/* 800C856C 000C514C  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 800C8570 000C5150  40 82 00 30 */	bne .L_800C85A0
/* 800C8574 000C5154  50 83 07 FE */	rlwimi r3, r4, 0, 0x1f, 0x1f
/* 800C8578 000C5158  98 7F 22 23 */	stb r3, 0x2223(r31)
/* 800C857C 000C515C  7F C3 F3 78 */	mr r3, r30
/* 800C8580 000C5160  48 00 8A DD */	bl ftCo_800D105C
/* 800C8584 000C5164  7F C3 F3 78 */	mr r3, r30
/* 800C8588 000C5168  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800C858C 000C516C  4B FB 96 FD */	bl ft_80081C88
/* 800C8590 000C5170  7F E3 FB 78 */	mr r3, r31
/* 800C8594 000C5174  4B FF FB DD */	bl ft_800C8170
/* 800C8598 000C5178  7F E3 FB 78 */	mr r3, r31
/* 800C859C 000C517C  4B FB 7E D9 */	bl ftCommon_80080474
.L_800C85A0:
/* 800C85A0 000C5180  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C85A4 000C5184  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C85A8 000C5188  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800C85AC 000C518C  38 21 00 18 */	addi r1, r1, 0x18
/* 800C85B0 000C5190  7C 08 03 A6 */	mtlr r0
/* 800C85B4 000C5194  4E 80 00 20 */	blr

.global ft_800C85B8
ft_800C85B8:
/* 800C85B8 000C5198  7C 08 02 A6 */	mflr r0
/* 800C85BC 000C519C  3C 80 80 3C */	lis r4, .L_803C6CF8@ha
/* 800C85C0 000C51A0  90 01 00 04 */	stw r0, 4(r1)
/* 800C85C4 000C51A4  38 00 00 00 */	li r0, 0
/* 800C85C8 000C51A8  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800C85CC 000C51AC  BE A1 00 2C */	stmw r21, 0x2c(r1)
/* 800C85D0 000C51B0  3B 00 00 00 */	li r24, 0
/* 800C85D4 000C51B4  3B C4 6C F8 */	addi r30, r4, .L_803C6CF8@l
/* 800C85D8 000C51B8  57 16 20 36 */	slwi r22, r24, 4
/* 800C85DC 000C51BC  3B 40 00 00 */	li r26, 0
/* 800C85E0 000C51C0  83 83 00 2C */	lwz r28, 0x2c(r3)
/* 800C85E4 000C51C4  80 7C 01 0C */	lwz r3, 0x10c(r28)
/* 800C85E8 000C51C8  82 E3 00 5C */	lwz r23, 0x5c(r3)
/* 800C85EC 000C51CC  92 E1 00 20 */	stw r23, 0x20(r1)
/* 800C85F0 000C51D0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800C85F4 000C51D4  48 00 00 4C */	b .L_800C8640
.L_800C85F8:
/* 800C85F8 000C51D8  80 7C 00 04 */	lwz r3, 4(r28)
/* 800C85FC 000C51DC  7F 04 C3 78 */	mr r4, r24
/* 800C8600 000C51E0  4B FA CA 6D */	bl ftParts_8007506C
/* 800C8604 000C51E4  28 03 00 00 */	cmplwi r3, 0
/* 800C8608 000C51E8  41 82 00 10 */	beq .L_800C8618
/* 800C860C 000C51EC  3B 18 00 01 */	addi r24, r24, 1
/* 800C8610 000C51F0  3A D6 00 10 */	addi r22, r22, 0x10
/* 800C8614 000C51F4  48 00 00 2C */	b .L_800C8640
.L_800C8618:
/* 800C8618 000C51F8  80 BC 05 E8 */	lwz r5, 0x5e8(r28)
/* 800C861C 000C51FC  38 60 00 00 */	li r3, 0
/* 800C8620 000C5200  80 81 00 20 */	lwz r4, 0x20(r1)
/* 800C8624 000C5204  7C A5 B0 2E */	lwzx r5, r5, r22
/* 800C8628 000C5208  48 2B 47 C5 */	bl HSD_IDInsertToTable
/* 800C862C 000C520C  3B 18 00 01 */	addi r24, r24, 1
/* 800C8630 000C5210  3A D6 00 10 */	addi r22, r22, 0x10
/* 800C8634 000C5214  38 61 00 20 */	addi r3, r1, 0x20
/* 800C8638 000C5218  38 81 00 1C */	addi r4, r1, 0x1c
/* 800C863C 000C521C  4B FA 57 C5 */	bl ftAnim_GetNextJointInTree
.L_800C8640:
/* 800C8640 000C5220  80 01 00 20 */	lwz r0, 0x20(r1)
/* 800C8644 000C5224  28 00 00 00 */	cmplwi r0, 0
/* 800C8648 000C5228  40 82 FF B0 */	bne .L_800C85F8
/* 800C864C 000C522C  3B 60 00 00 */	li r27, 0
/* 800C8650 000C5230  92 E1 00 20 */	stw r23, 0x20(r1)
/* 800C8654 000C5234  3C 60 80 3C */	lis r3, ftMObj@ha
/* 800C8658 000C5238  93 61 00 1C */	stw r27, 0x1c(r1)
/* 800C865C 000C523C  57 5D 10 3A */	slwi r29, r26, 2
/* 800C8660 000C5240  3B E3 69 80 */	addi r31, r3, ftMObj@l
/* 800C8664 000C5244  3A C0 00 00 */	li r22, 0
/* 800C8668 000C5248  48 00 01 C0 */	b .L_800C8828
.L_800C866C:
/* 800C866C 000C524C  80 7C 00 04 */	lwz r3, 4(r28)
/* 800C8670 000C5250  7F 64 DB 78 */	mr r4, r27
/* 800C8674 000C5254  4B FA C9 F9 */	bl ftParts_8007506C
/* 800C8678 000C5258  28 03 00 00 */	cmplwi r3, 0
/* 800C867C 000C525C  41 82 00 10 */	beq .L_800C868C
/* 800C8680 000C5260  3B 7B 00 01 */	addi r27, r27, 1
/* 800C8684 000C5264  3A D6 00 10 */	addi r22, r22, 0x10
/* 800C8688 000C5268  48 00 01 A0 */	b .L_800C8828
.L_800C868C:
/* 800C868C 000C526C  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 800C8690 000C5270  3A E0 00 00 */	li r23, 0
/* 800C8694 000C5274  80 61 00 20 */	lwz r3, 0x20(r1)
/* 800C8698 000C5278  7F 24 B0 2E */	lwzx r25, r4, r22
/* 800C869C 000C527C  80 63 00 10 */	lwz r3, 0x10(r3)
/* 800C86A0 000C5280  48 29 5B 15 */	bl HSD_DObjLoadDesc
/* 800C86A4 000C5284  7C 78 1B 79 */	or. r24, r3, r3
/* 800C86A8 000C5288  41 82 01 6C */	beq .L_800C8814
/* 800C86AC 000C528C  7F 23 CB 78 */	mr r3, r25
/* 800C86B0 000C5290  48 2A 95 3D */	bl HSD_JObjGetDObj
/* 800C86B4 000C5294  80 BC 05 E8 */	lwz r5, 0x5e8(r28)
/* 800C86B8 000C5298  38 96 00 09 */	addi r4, r22, 9
/* 800C86BC 000C529C  3A A3 00 00 */	addi r21, r3, 0
/* 800C86C0 000C52A0  7C 05 20 AE */	lbzx r0, r5, r4
/* 800C86C4 000C52A4  38 C0 00 01 */	li r6, 1
/* 800C86C8 000C52A8  50 C0 17 7A */	rlwimi r0, r6, 2, 0x1d, 0x1d
/* 800C86CC 000C52AC  7C 05 21 AE */	stbx r0, r5, r4
/* 800C86D0 000C52B0  38 78 00 00 */	addi r3, r24, 0
/* 800C86D4 000C52B4  80 81 00 20 */	lwz r4, 0x20(r1)
/* 800C86D8 000C52B8  80 84 00 10 */	lwz r4, 0x10(r4)
/* 800C86DC 000C52BC  48 29 5C 41 */	bl HSD_DObjResolveRefsAll
/* 800C86E0 000C52C0  28 15 00 00 */	cmplwi r21, 0
/* 800C86E4 000C52C4  40 82 00 4C */	bne .L_800C8730
/* 800C86E8 000C52C8  38 79 00 00 */	addi r3, r25, 0
/* 800C86EC 000C52CC  38 98 00 00 */	addi r4, r24, 0
/* 800C86F0 000C52D0  48 2A 95 35 */	bl HSD_JObjAddDObj
/* 800C86F4 000C52D4  48 00 00 50 */	b .L_800C8744
/* 800C86F8 000C52D8  48 00 00 38 */	b .L_800C8730
.L_800C86FC:
/* 800C86FC 000C52DC  28 15 00 00 */	cmplwi r21, 0
/* 800C8700 000C52E0  41 82 00 0C */	beq .L_800C870C
/* 800C8704 000C52E4  80 15 00 04 */	lwz r0, 4(r21)
/* 800C8708 000C52E8  48 00 00 08 */	b .L_800C8710
.L_800C870C:
/* 800C870C 000C52EC  38 00 00 00 */	li r0, 0
.L_800C8710:
/* 800C8710 000C52F0  28 00 00 00 */	cmplwi r0, 0
/* 800C8714 000C52F4  41 82 00 24 */	beq .L_800C8738
/* 800C8718 000C52F8  28 15 00 00 */	cmplwi r21, 0
/* 800C871C 000C52FC  41 82 00 0C */	beq .L_800C8728
/* 800C8720 000C5300  80 15 00 04 */	lwz r0, 4(r21)
/* 800C8724 000C5304  48 00 00 08 */	b .L_800C872C
.L_800C8728:
/* 800C8728 000C5308  38 00 00 00 */	li r0, 0
.L_800C872C:
/* 800C872C 000C530C  7C 15 03 78 */	mr r21, r0
.L_800C8730:
/* 800C8730 000C5310  28 15 00 00 */	cmplwi r21, 0
/* 800C8734 000C5314  40 82 FF C8 */	bne .L_800C86FC
.L_800C8738:
/* 800C8738 000C5318  38 75 00 00 */	addi r3, r21, 0
/* 800C873C 000C531C  38 98 00 00 */	addi r4, r24, 0
/* 800C8740 000C5320  4B F4 46 F1 */	bl lb_8000CE30
.L_800C8744:
/* 800C8744 000C5324  7F B9 EB 78 */	mr r25, r29
.L_800C8748:
/* 800C8748 000C5328  28 18 00 00 */	cmplwi r24, 0
/* 800C874C 000C532C  41 82 00 74 */	beq .L_800C87C0
/* 800C8750 000C5330  2C 1A 00 20 */	cmpwi r26, 0x20
/* 800C8754 000C5334  41 80 00 20 */	blt .L_800C8774
/* 800C8758 000C5338  38 7E 00 38 */	addi r3, r30, 0x38
/* 800C875C 000C533C  4C C6 31 82 */	crclr 6
/* 800C8760 000C5340  48 27 CF 49 */	bl OSReport
/* 800C8764 000C5344  38 7E 00 2C */	addi r3, r30, 0x2c
/* 800C8768 000C5348  38 80 00 F8 */	li r4, 0xf8
/* 800C876C 000C534C  38 AD 85 F4 */	addi r5, r13, ftCo_804D3C94@sda21
/* 800C8770 000C5350  48 2B FA B1 */	bl __assert
.L_800C8774:
/* 800C8774 000C5354  80 7C 20 40 */	lwz r3, 0x2040(r28)
/* 800C8778 000C5358  7F 03 C9 2E */	stwx r24, r3, r25
/* 800C877C 000C535C  80 18 00 08 */	lwz r0, 8(r24)
/* 800C8780 000C5360  28 00 00 00 */	cmplwi r0, 0
/* 800C8784 000C5364  7C 03 03 78 */	mr r3, r0
/* 800C8788 000C5368  41 82 00 0C */	beq .L_800C8794
/* 800C878C 000C536C  7F E4 FB 78 */	mr r4, r31
/* 800C8790 000C5370  48 2B 9C 71 */	bl hsdChangeClass
.L_800C8794:
/* 800C8794 000C5374  28 18 00 00 */	cmplwi r24, 0
/* 800C8798 000C5378  41 82 00 0C */	beq .L_800C87A4
/* 800C879C 000C537C  80 18 00 04 */	lwz r0, 4(r24)
/* 800C87A0 000C5380  48 00 00 08 */	b .L_800C87A8
.L_800C87A4:
/* 800C87A4 000C5384  38 00 00 00 */	li r0, 0
.L_800C87A8:
/* 800C87A8 000C5388  7C 18 03 78 */	mr r24, r0
/* 800C87AC 000C538C  3B 39 00 04 */	addi r25, r25, 4
/* 800C87B0 000C5390  3B BD 00 04 */	addi r29, r29, 4
/* 800C87B4 000C5394  3B 5A 00 01 */	addi r26, r26, 1
/* 800C87B8 000C5398  3A F7 00 01 */	addi r23, r23, 1
/* 800C87BC 000C539C  4B FF FF 8C */	b .L_800C8748
.L_800C87C0:
/* 800C87C0 000C53A0  2C 17 00 80 */	cmpwi r23, 0x80
/* 800C87C4 000C53A4  41 80 00 20 */	blt .L_800C87E4
/* 800C87C8 000C53A8  38 7E 00 5C */	addi r3, r30, 0x5c
/* 800C87CC 000C53AC  4C C6 31 82 */	crclr 6
/* 800C87D0 000C53B0  48 27 CE D9 */	bl OSReport
/* 800C87D4 000C53B4  38 7E 00 2C */	addi r3, r30, 0x2c
/* 800C87D8 000C53B8  38 80 01 06 */	li r4, 0x106
/* 800C87DC 000C53BC  38 AD 85 F4 */	addi r5, r13, ftCo_804D3C94@sda21
/* 800C87E0 000C53C0  48 2B FA 41 */	bl __assert
.L_800C87E4:
/* 800C87E4 000C53C4  80 BC 05 E8 */	lwz r5, 0x5e8(r28)
/* 800C87E8 000C53C8  38 96 00 0D */	addi r4, r22, 0xd
/* 800C87EC 000C53CC  38 7A FF FF */	addi r3, r26, -1
/* 800C87F0 000C53D0  7C 05 20 AE */	lbzx r0, r5, r4
/* 800C87F4 000C53D4  50 60 0E 3C */	rlwimi r0, r3, 1, 0x18, 0x1e
/* 800C87F8 000C53D8  38 76 00 09 */	addi r3, r22, 9
/* 800C87FC 000C53DC  7C 05 21 AE */	stbx r0, r5, r4
/* 800C8800 000C53E0  38 A0 00 01 */	li r5, 1
/* 800C8804 000C53E4  80 9C 05 E8 */	lwz r4, 0x5e8(r28)
/* 800C8808 000C53E8  7C 04 18 AE */	lbzx r0, r4, r3
/* 800C880C 000C53EC  50 A0 0F BC */	rlwimi r0, r5, 1, 0x1e, 0x1e
/* 800C8810 000C53F0  7C 04 19 AE */	stbx r0, r4, r3
.L_800C8814:
/* 800C8814 000C53F4  3B 7B 00 01 */	addi r27, r27, 1
/* 800C8818 000C53F8  3A D6 00 10 */	addi r22, r22, 0x10
/* 800C881C 000C53FC  38 61 00 20 */	addi r3, r1, 0x20
/* 800C8820 000C5400  38 81 00 1C */	addi r4, r1, 0x1c
/* 800C8824 000C5404  4B FA 55 DD */	bl ftAnim_GetNextJointInTree
.L_800C8828:
/* 800C8828 000C5408  80 01 00 20 */	lwz r0, 0x20(r1)
/* 800C882C 000C540C  28 00 00 00 */	cmplwi r0, 0
/* 800C8830 000C5410  40 82 FE 3C */	bne .L_800C866C
/* 800C8834 000C5414  93 5C 20 3C */	stw r26, 0x203c(r28)
/* 800C8838 000C5418  BA A1 00 2C */	lmw r21, 0x2c(r1)
/* 800C883C 000C541C  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800C8840 000C5420  38 21 00 58 */	addi r1, r1, 0x58
/* 800C8844 000C5424  7C 08 03 A6 */	mtlr r0
/* 800C8848 000C5428  4E 80 00 20 */	blr


.section .data
    .balign 8
.L_803C6CF8:
    .asciz "mobj has unexpected blending flags (0x%x)."
    .balign 4
.L_803C6D24:
    .asciz "ftmetal.c"
    .balign 4
    .asciz "fighter parts model dobj num over!\n"
    .balign 4
    .asciz "fighter dobj num over!\n"


.section .sdata
    .balign 8
ftCo_804D3C90:
    .4byte NULL
ftCo_804D3C94:
    .asciz "0"