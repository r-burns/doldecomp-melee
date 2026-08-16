// The memory-card work area, laid out as one contiguous block.

#include <dolphin/types.h>

// 0x10 + 0x1200 + 0x300 + 0x828 + 0x824. Aligned well past anything in here:
u8 melee_pc_card_work[0x255C] __attribute__((aligned(32)));

// clang-format off
__asm__(".globl hsd_804D1138\n\t.set hsd_804D1138, melee_pc_card_work+0x0000");
__asm__(".globl hsd_804D1148\n\t.set hsd_804D1148, melee_pc_card_work+0x0010");
__asm__(".globl hsd_804D2348\n\t.set hsd_804D2348, melee_pc_card_work+0x1210");
__asm__(".globl hsd_804D2648\n\t.set hsd_804D2648, melee_pc_card_work+0x1510");
__asm__(".globl hsd_804D2E70\n\t.set hsd_804D2E70, melee_pc_card_work+0x1D38");
// clang-format on

u8 melee_pc_card_state[0x20] __attribute__((aligned(32)));

// clang-format off
__asm__(".globl hsd_804D7980\n\t.set hsd_804D7980, melee_pc_card_state+0x00");
__asm__(".globl hsd_804D7984\n\t.set hsd_804D7984, melee_pc_card_state+0x04");
__asm__(".globl hsd_804D7988\n\t.set hsd_804D7988, melee_pc_card_state+0x08");
__asm__(".globl hsd_804D798C\n\t.set hsd_804D798C, melee_pc_card_state+0x0C");
__asm__(".globl hsd_804D7990\n\t.set hsd_804D7990, melee_pc_card_state+0x10");
__asm__(".globl hsd_804D7994\n\t.set hsd_804D7994, melee_pc_card_state+0x14");
__asm__(".globl hsd_804D7998\n\t.set hsd_804D7998, melee_pc_card_state+0x18");
__asm__(".globl hsd_804D799C\n\t.set hsd_804D799C, melee_pc_card_state+0x1C");
// clang-format on
