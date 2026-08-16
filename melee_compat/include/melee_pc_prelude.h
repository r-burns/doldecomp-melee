#ifndef MELEE_PC_PRELUDE_H
#define MELEE_PC_PRELUDE_H

// global header
// for some god-forsaken reason we use transitive includes from GC dolphin to provide some functions like memcpy
// i couldn't get the decomp to match when building for PPC without doing this... god forgive me
// Force-included (-include) into every translation unit of the PC build.
//
// due to aurora and dolphin's header structure being different the decomp actually expects
// to be able to transitivelly access some headers
//
// adding the includes to the sources themselves is NOT an option: doing so
// changes mwcc's codegen,
// This header keeps the fix entirely on
// the PC side, where it cannot affect the PPC build.

#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#include <melee_pc_gx.h>

#include <dolphin/os.h>
#include <dolphin/pad.h>

// HSD_Synth_804D6018 leaves an uninitialised audio heap handle, so this is able to
// tolerate it
void* melee_pc_alloc_from_heap(int heap, u32 size);
void melee_pc_free_to_heap(int heap, void* ptr);
#define OSAllocFromHeap melee_pc_alloc_from_heap
#define OSFreeToHeap melee_pc_free_to_heap

// Routes the async card calls through melee_compat/src/card_async.c, which
// defers the completion callback instead of running it inline, the reason being
// that melee expects to set a pending flag afterwards, which aurora on't do because
// it's synchronous, leading to a deadlock
struct CARDFileInfo;
struct CARDStat;
s32 melee_pc_card_read_async(const struct CARDFileInfo*, void*, s32, s32,
                             void (*)(s32, s32));
s32 melee_pc_card_write_async(const struct CARDFileInfo*, const void*, s32, s32,
                              void (*)(s32, s32));
s32 melee_pc_card_mount_async(s32, void*, void (*)(s32, s32),
                              void (*)(s32, s32));
s32 melee_pc_card_check_async(s32, void (*)(s32, s32));
s32 melee_pc_card_format_async(s32, void (*)(s32, s32));
s32 melee_pc_card_create_async(s32, const char*, u32, struct CARDFileInfo*,
                               void (*)(s32, s32));
s32 melee_pc_card_delete_async(s32, const char*, void (*)(s32, s32));
s32 melee_pc_card_rename_async(s32, const char*, const char*,
                               void (*)(s32, s32));
s32 melee_pc_card_set_status_async(s32, s32, const struct CARDStat*,
                                   void (*)(s32, s32));
// scripted controller input for testing and profit
struct PADStatus;
u32 melee_pc_pad_read(struct PADStatus* status);
#define PADRead melee_pc_pad_read

#define CARDReadAsync melee_pc_card_read_async
#define CARDWriteAsync melee_pc_card_write_async
#define CARDMountAsync melee_pc_card_mount_async
#define CARDCheckAsync melee_pc_card_check_async
#define CARDFormatAsync melee_pc_card_format_async
#define CARDCreateAsync melee_pc_card_create_async
#define CARDDeleteAsync melee_pc_card_delete_async
#define CARDRenameAsync melee_pc_card_rename_async
#define CARDSetStatusAsync melee_pc_card_set_status_async

float powf(float x, float y);
float tanf(float x);

#endif
