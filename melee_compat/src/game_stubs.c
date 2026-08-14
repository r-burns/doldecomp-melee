// This is for functions that do not have an x86 counterpart, ppc specific crash handlers, etc

#include "compat_report.h"

#include <dolphin/dvd.h>
#include <baselib/gobj.h>
#include <baselib/sobjlib.h>

// These decode a PowerPC exception context and paint a
// register dump on screen, which is not a thing on x86 for obvious reasons

void db_SetupCrashHandler(void) {}
void db_ClearFPUExceptions(void) {}

// No idea what these are, so i'm just gonna ignore it since they appear to be insecuential

#define MN_NAME_SLOTS 64

static char mn_name_empty[] = "";

char* mnNameNew_803EE720[MN_NAME_SLOTS] = { 0 };
char* mnNameNew_803EE724[MN_NAME_SLOTS] = { 0 };

// a static initialiser cannot reference
// mn_name_empty in a portable way for every entry.
static void melee_pc_init_name_tables(void) __attribute__((constructor));
static void melee_pc_init_name_tables(void)
{
    int i;
    for (i = 0; i < MN_NAME_SLOTS; i++) {
        mnNameNew_803EE720[i] = mn_name_empty;
        mnNameNew_803EE724[i] = mn_name_empty;
    }
}

// melee's audio bring-up, runs partially for
// real, so the audio filename and the SFX bank sizes are set up properly.
// What is stubbed is the loading of SFX banks
//
// Returning 0 queues nothing, so the pending counter stays zero.
int HSD_SynthSFXLoad(const char* filename, int bankID, int (*cb)(int, int),
                     int mode)
{
    COMPAT_STUB();
    (void) filename; (void) bankID; (void) cb; (void) mode;
    return 0;
}

// And the matching wait. lbAudioAx_80027648() spins
//
//     while (fn_80027488() == 1) HSD_SynthSFXWaitForLoadCompletion(...);
//
// until every queued bank reports in. Nothing ever does with the load stubbed,
// and the inner wait returns immediately because its pending counter is zero,
// so the loop never even pumps interrupts, a closed spin with no way in from
// outside. It has to be skipped rather than satisfied.
void lbAudioAx_80027648(void)
{
    COMPAT_STUB();
}


// Video decoder stub

void lbMthp_8001F410(const char* filename, u32* rate_table, void* buf,
                     size_t heap_size, int loop)
{
    COMPAT_STUB();
    (void) filename; (void) rate_table; (void) buf; (void) heap_size;
    (void) loop;
}

void lbMthp_8001F578(void) {}
s32 lbMthp_8001F5C4(void) { return 0; }
s32 lbMthp_8001F5D4(void) { return 0; }
s32 lbMthp_8001F5E4(void) { return 0; }
s32 lbMthp_8001F5F4(void) { return 0; }
s32 lbMthp_8001F604(void) { return 0; } // not playing
void lbMthp_8001F614(s32 arg0) { (void) arg0; }
HSD_SObj* lbMthp_8001F624(HSD_GObj* gobj, int w, int h)
{
    (void) gobj; (void) w; (void) h;
    return NULL;
}
void lbMthp_8001F67C(HSD_GObj* gobj, int arg1) { (void) gobj; (void) arg1; }
void lbMthp_8001F800(void) {}
void lbMthp_8001F87C(void) {}
