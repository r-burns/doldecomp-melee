#ifndef MELEE_COMPAT_PC_H
#define MELEE_COMPAT_PC_H

void melee_pc_frame_pump(void);

// printf to the host's stdout, cannot use the actual printf function because
// the game uses the MSL
int melee_pc_printf(const char* fmt, ...);

#endif
