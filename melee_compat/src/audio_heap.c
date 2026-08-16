// Workaround for the HSD_Synth_804D6018
//
// synth.static.h defines the audio heap handle as private to synth.c, while initialize.c
// declares the same name `extern` and stores the heap it creates into it.
// They result in two different objects, so HSD_OSInit creates the audio heap and
// synth.c never sees it, the first HSD_AudioMalloc calls
// and gets nullptr.
//
// The real fix is to make that one shared global, which changes what the
// decomp asserts about the original symbol.

#include "compat_report.h"

// The prelude renames these; this file needs the real ones.
#undef OSAllocFromHeap
#undef OSFreeToHeap

#include <dolphin/os.h>

// Allocated with mmap(MAP_32BIT), not malloc, for two reasons.
//
// For alignemnt the OSAllocFromHeap hands back 32-byte-aligned blocks and the DMA
// layer relies on it, HSD_DevComRequest asserts `dest % 32 == 0`.
// Host malloc only guarantees 16.
//
// Address range: the synth narrows an audio-heap pointer to 32 bits when it
// uses one as a transfer destination --
//
// so a block above 4GB comes back truncated and the DVD layer writes to a
// garbage address. so the mapping is made explicitly low here.
//
// The size is stashed in a 32-byte shadow variable so free() can unmap exactly.
#include <sys/mman.h>

#define AUDIO_SHADOW_SIZE 32

static void* audio_alloc(size_t size)
{
    size_t total = size + AUDIO_SHADOW_SIZE;
    void* base = mmap(NULL, total, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
    if (base == MAP_FAILED) {
        return NULL;
    }
    *(size_t*) base = total;
    return (u8*) base + AUDIO_SHADOW_SIZE;
}

static void audio_free(void* p)
{
    u8* base;
    if (p == NULL) {
        return;
    }
    base = (u8*) p - AUDIO_SHADOW_SIZE;
    munmap(base, *(size_t*) base);
}

// Heap handles are indices, so a negative one was never initialised.
static bool bad_heap(OSHeapHandle heap) { return heap < 0; }

void* melee_pc_alloc_from_heap(OSHeapHandle heap, u32 size)
{
    if (bad_heap(heap)) {
        void* p;
        COMPAT_STUB();
        p = audio_alloc(size);
        if (p == NULL) {
            OSReport("melee_pc: audio heap fallback failed for %u bytes\n",
                     (unsigned) size);
        }
        return p;
    }
    return OSAllocFromHeap(heap, size);
}

void melee_pc_free_to_heap(OSHeapHandle heap, void* ptr)
{
    if (bad_heap(heap)) {
        audio_free(ptr);
        return;
    }
    OSFreeToHeap(heap, ptr);
}
