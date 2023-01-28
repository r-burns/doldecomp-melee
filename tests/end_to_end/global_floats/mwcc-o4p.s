.include "macros.inc"

.section .text  # 0x0 - 0x70

.global test
test:
/* 00000000 00000000  3C A0 00 00 */	lis r5, D_410160@ha
/* 00000004 00000004  3C 80 00 00 */	lis r4, D_400120@ha
/* 00000008 00000008  54 66 10 3A */	slwi r6, r3, 2
/* 0000000C 0000000C  38 65 00 00 */	addi r3, r5, D_410160@l
/* 00000010 00000010  38 04 00 00 */	addi r0, r4, D_400120@l
/* 00000014 00000014  7C 83 32 14 */	add r4, r3, r6
/* 00000018 00000018  7C 60 32 14 */	add r3, r0, r6
/* 0000001C 0000001C  C0 24 00 00 */	lfs f1, 0(r4)
/* 00000020 00000020  C0 03 00 00 */	lfs f0, 0(r3)
/* 00000024 00000024  3C 60 00 00 */	lis r3, D_410170@ha
/* 00000028 00000028  38 03 00 00 */	addi r0, r3, D_410170@l
/* 0000002C 0000002C  EC 01 00 2A */	fadds f0, f1, f0
/* 00000030 00000030  7C 80 32 14 */	add r4, r0, r6
/* 00000034 00000034  3C 60 00 00 */	lis r3, D_40012C@ha
/* 00000038 00000038  38 03 00 00 */	addi r0, r3, D_40012C@l
/* 0000003C 0000003C  D0 04 00 00 */	stfs f0, 0(r4)
/* 00000040 00000040  7C 60 32 14 */	add r3, r0, r6
/* 00000044 00000044  C0 20 00 00 */	lfs f1, $$25@sda21(r13)
/* 00000048 00000048  C0 64 00 00 */	lfs f3, 0(r4)
/* 0000004C 0000004C  C0 03 00 00 */	lfs f0, 0(r3)
/* 00000050 00000050  EC 21 00 F2 */	fmuls f1, f1, f3
/* 00000054 00000054  C0 40 00 00 */	lfs f2, D_410150@sda21(r2)
/* 00000058 00000058  EC 01 00 2A */	fadds f0, f1, f0
/* 0000005C 0000005C  EC 02 00 32 */	fmuls f0, f2, f0
/* 00000060 00000060  D0 00 00 00 */	stfs f0, D_410150@sda21(r2)
/* 00000064 00000064  C0 00 00 00 */	lfs f0, D_410150@sda21(r2)
/* 00000068 00000068  EC 20 18 24 */	fdivs f1, f0, f3
/* 0000006C 0000006C  4E 80 00 20 */	blr 

.section .rodata  # 0x0 - 0x20

.global D_400120
D_400120:
	.word 0x41200000
	.word 0x41300000
	.word 0x41400000

.global D_40012C
D_40012C:
	.word 0x41600000
	.word 0x41700000
	.word 0x41800000
	.word 0x41880000
	.word 0x41900000

.section .data  # 0x0 - 0x18

.global D_410154
D_410154:
	.word 0x40400000
	.word 0x40800000
	.word 0x40a00000

.global D_410160
D_410160:
	.word 0x40c00000
	.word 0x40e00000
	.word 0x41000000

.section .bss  # 0x0 - 0xc

.global D_410170
D_410170:
	.word 0x00000000
	.word 0x00000000
	.word 0x00000000

.section .sdata  # 0x0 - 0x4

.global D_410150
D_410150:
	.word 0x3f9d70a4

.section .sdata2  # 0x0 - 0x4

.global $$25
$$25:
	.word 0x40b570a4

