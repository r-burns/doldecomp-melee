// Remaining SDK stuff aurora does not provide.
//
// MCC: the modem/expansion-port API. Melee's HSD layer references it but no
// THP: video playback
// DB: hardware debugger
// GX / VI / CARD: individual methods missing from aurora

#include "compat_report.h"

#include <dolphin/card.h>
#include <dolphin/db.h>
#include <dolphin/gx.h>
#include <dolphin/mcc.h>
#include <dolphin/thp.h>
#include <dolphin/vi.h>

// --- DB -------------------------------------------------------------------

BOOL DBIsDebuggerPresent(void) { return false; }

// --- MCC ------------------------------------------------------------------

int MCCInit(enum MCC_EXI ch, u8 timeout, MCC_CBSysEvent cb)
{
    COMPAT_STUB();
    (void) ch; (void) timeout; (void) cb;
    return -1;
}
void MCCExit(void) {}
int MCCEnumDevices(MCC_CBEnumDevices cb) { (void) cb; return -1; }
u8 MCCGetFreeBlocks(enum MCC_MODE mode) { (void) mode; return 0; }
u8 MCCGetLastError(void) { return 0; }
int MCCGetConnectionStatus(enum MCC_CHANNEL ch, enum MCC_CONNECT* connect)
{
    (void) ch; (void) connect;
    return -1;
}
int MCCNotify(enum MCC_CHANNEL ch, u32 notify) { (void) ch; (void) notify; return -1; }
int MCCStreamOpen(enum MCC_CHANNEL ch, u8 blockSize) { (void) ch; (void) blockSize; return -1; }

// --- THP ------------------------------------------------------------------

BOOL THPInit(void) { COMPAT_STUB(); return false; }
s32 THPDec_8032F8D4(u32 file, void* out) { (void) file; (void) out; return -1; }
s32 THPDec_8032FD40(THPDec_8032FD40_Data* arg0, u16 height)
{
    (void) arg0; (void) height;
    return -1;
}
void THPDec_80331340(s32 a, void* b, void* c, void* d)
{
    (void) a; (void) b; (void) c; (void) d;
}
void THPDec_803313D0(s32 a, void* b, void* c, void* d, u32 e)
{
    (void) a; (void) b; (void) c; (void) d; (void) e;
}
s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* work)
{
    (void) file; (void) tileY; (void) tileU; (void) tileV; (void) work;
    return -1;
}

// --- GX -------------------------------------------------------------------

void GXSetTevClampMode(int tev_stage, int mode)
{
    // Fixed-function TEV clamping; aurora's shader-based TEV always clamps.
    (void) tev_stage; (void) mode;
}

void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, f32 projmtx[4][4])
{
    COMPAT_STUB();
    (void) table; (void) width; (void) projmtx;
}

void GXWaitDrawDone(void)
{
    // Aurora submits synchronously, so there is nothing to wait on.
}

void GXMatrixIndex1u8(u8 index)
{
    COMPAT_STUB();
    (void) index;
}

// --- missing functions ----------------------------------------------------

char* getenv(const char* name);

// Called by every stub in the generated undefined_stubs.c.
void melee_pc_missing(const char* name)
{
    static int lenient = -1;
    static const char* seen[512];
    static int n_seen;
    int i;

    if (lenient < 0) {
        lenient = getenv("MELEE_PC_STUB_CONTINUE") != NULL;
    }
    if (!lenient) {
        OSPanic(__FILE__, __LINE__,
                "melee_pc: unimplemented function: %s", name);
    }

    for (i = 0; i < n_seen; i++) {
        if (seen[i] == name) {
            return;
        }
    }
    if (n_seen < (int) (sizeof(seen) / sizeof(seen[0]))) {
        seen[n_seen++] = name;
    }
    OSReport("melee_pc: MISSING %s\n", name);
}

// --- PAD ------------------------------------------------------------------

void PADSetSamplingRate(u32 msec)
{
    // noop on PC (perhaps for the GC adapter?)
    (void) msec;
}

// --- Cache maintenance ----------------------------------------------------
//
// memory on pc is cache-coherent so there is nothing to do

void DCFlushRange(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }
void DCStoreRange(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }
void DCInvalidateRange(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }
void DCFlushRangeNoSync(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }
void DCStoreRangeNoSync(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }
void DCZeroRange(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }
void ICInvalidateRange(void* addr, u32 nBytes) { (void) addr; (void) nBytes; }

// --- VI -------------------------------------------------------------------

u32 VIPadFrameBufferWidth(u32 width)
{
    // The VI reads framebuffers in 16-pixel units.
    return (width + 15) & ~15u;
}
