#include "melee_pc_gx.h"

#include "compat_report.h"

#include <dolphin/gx.h>
#include <dolphin/os.h>

// If pc_main.c never reported a size, assume the GameCube's 24 MB.
#define MEM1_FALLBACK (24 * 1024 * 1024)

static const u8* mem1_start;
static const u8* mem1_end;
static u32 mem1_size;

void melee_pc_set_mem1(const void* start, u32 size)
{
    mem1_size = size;
    if (start != NULL) {
        mem1_start = start;
        mem1_end = (const u8*) start + size;
    }
}

// The base is resolved lazily because pc_main.c records it before handing off
// to the game, and aurora only sets OSBaseAddress inside OSInit, which melee
// calls later
static void ensure_mem1(void)
{
    if (mem1_start == NULL && OSBaseAddress != 0) {
        mem1_start = (const u8*) OSBaseAddress;
        mem1_end = mem1_start + (mem1_size != 0 ? mem1_size : MEM1_FALLBACK);
    }
}

// Set only by melee_pc_dat_selftest(). Its inputs are synthetic descriptors in
// .rodata rather than archive data in MEM1, so the bounds check, which is
// there to stop the converter following a float or a small integer as an
// address, would reject every one of them and hand back nullptr
static bool mem1_check_off;

void melee_pc_mem1_allow_all(void) { mem1_check_off = true; }

bool melee_pc_in_mem1(const void* p)
{
    if (mem1_check_off) {
        return true;
    }
    ensure_mem1();
    return mem1_start != NULL && (const u8*) p >= mem1_start &&
           (const u8*) p < mem1_end;
}

u32 melee_pc_array_size(int attr_type, u16 stride, const void* data)
{
    u32 entries;
    u32 size;

    if (stride == 0) {
        return 0;
    }

    switch (attr_type) {
    case GX_INDEX8:
        entries = 1u << 8;
        break;
    case GX_INDEX16:
        entries = 1u << 16;
        break;
    default:
        // GX_DIRECT arrays are not indexed, so nothing reads through a base.
        return 0;
    }

    size = entries * (u32) stride;

    // Clamp so the upload cannot run past mapped memory. Data outside MEM1
    // (a static array in the executable, say) is left alone, the caller
    // passed a real size for those.
    ensure_mem1();
    if (mem1_start != NULL && (const u8*) data >= mem1_start &&
        (const u8*) data < mem1_end)
    {
        u32 avail = (u32) (mem1_end - (const u8*) data);
        if (size > avail) {
            size = avail;
        }
    }

    return size;
}
