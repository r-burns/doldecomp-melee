#ifndef MELEE_PC_GX_H
#define MELEE_PC_GX_H

#include <dolphin/types.h>

// Due to unified memory the GC's GPU walked the
// array by index and never needed to know where it ended. Aurora must copy the
// array into a GPU buffer, so it needs a size in GXSetArray and DAT-loaded vertex
// data carries no size anywhere in the file format.
//
// aurora uses the value two ways: as a bounds
// check on indexed loads, and as the upload length. So an over-estimate is
// safe, it wastes upload bandwidth, while an under-estimate trips the
// bounds assert or silently truncates geometry.
//
// This returns an upper bound derived from the index width: a GX_INDEX8 array
// can address at most 256 entries and a GX_INDEX16 array at most 65536, so
// (max_index + 1) * stride bounds the addressable range no matter how the data
// is laid out. It is then clamped to the end of MEM1 so the upload can never
// read off the end of mapped memory.


u32 melee_pc_array_size(int attr_type, u16 stride, const void* data);

void melee_pc_set_mem1(const void* start, u32 size);

bool melee_pc_in_mem1(const void* p);
void melee_pc_mem1_allow_all(void);

#endif
