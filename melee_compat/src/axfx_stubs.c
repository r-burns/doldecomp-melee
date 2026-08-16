// audio effects stubs

#include "compat_report.h"

#include <dolphin/axfx.h>

int AXFXChorusInit(struct AXFX_CHORUS* c) { COMPAT_STUB(); (void) c; return 0; }
int AXFXChorusShutdown(struct AXFX_CHORUS* c) { (void) c; return 0; }
int AXFXChorusSettings(struct AXFX_CHORUS* c) { (void) c; return 0; }
void AXFXChorusCallback(struct AXFX_BUFFERUPDATE* b, struct AXFX_CHORUS* c)
{
    (void) b; (void) c;
}

int AXFXDelayInit(struct AXFX_DELAY* d) { COMPAT_STUB(); (void) d; return 0; }
int AXFXDelayShutdown(struct AXFX_DELAY* d) { (void) d; return 0; }
int AXFXDelaySettings(struct AXFX_DELAY* d) { (void) d; return 0; }
void AXFXDelayCallback(struct AXFX_BUFFERUPDATE* b, struct AXFX_DELAY* d)
{
    (void) b; (void) d;
}

int AXFXReverbHiInit(struct AXFX_REVERBHI* r) { COMPAT_STUB(); (void) r; return 0; }
int AXFXReverbHiShutdown(struct AXFX_REVERBHI* r) { (void) r; return 0; }
int AXFXReverbHiSettings(struct AXFX_REVERBHI* r) { (void) r; return 0; }
void AXFXReverbHiCallback(struct AXFX_BUFFERUPDATE* b, struct AXFX_REVERBHI* r)
{
    (void) b; (void) r;
}

int AXFXReverbStdInit(struct AXFX_REVERBSTD* r) { COMPAT_STUB(); (void) r; return 0; }
int AXFXReverbStdShutdown(struct AXFX_REVERBSTD* r) { (void) r; return 0; }
int AXFXReverbStdSettings(struct AXFX_REVERBSTD* r) { (void) r; return 0; }
void AXFXReverbStdCallback(struct AXFX_BUFFERUPDATE* b, struct AXFX_REVERBSTD* r)
{
    (void) b; (void) r;
}

void AXFXSetHooks(void* (*alloc_hook)(unsigned long), void (*free_hook)(void*))
{
    (void) alloc_hook; (void) free_hook;
}
