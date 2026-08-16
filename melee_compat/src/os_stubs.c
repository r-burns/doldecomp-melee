// OS / VI / GX entry points aurora declares but does not implement.
//
// These are not panic stubs: they sit on the boot and per-frame paths, so
// leaving them to tools/gen_undefined_stubs.py would kill the game instantly.
// Each does the least that is correct on a PC.

#include "compat_report.h"
#include "compat_pc.h"

#include <stdarg.h>

#include <math.h>

// MSL's headers do not declare these; the PC build links the host libc.
// (stdout rather than stderr: `stderr` is a macro in MSL's stdio.h, and
// avoiding FILE* keeps this independent of which stdio.h wins.)
void abort(void);
void exit(int status);
void melee_pc_arq_drain(void);
void melee_pc_alarms_poll(void);
void melee_pc_card_drain(void);
void melee_pc_vi_poll(void);
int vprintf(const char* format, va_list arg);
int fflush(void* stream);

// MSL's math.h has fabs but not sqrt or fabsf. Declared here rather than
// pulling in the host's math.h, which collides with MSL's helper macros.
double sqrt(double x);
float fabsf(float x);

#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

// --- Reporting ------------------------------------------------------------
//
// Aurora declares OSReport/OSVReport weak but never defines them, so without
// these every call resolves to address 0 and segfaults -- including the ones
// inside OSPanic, which turned every panic into a null-pointer crash with the
// actual message lost.

// Flushed on every call: this is the game's only voice, and without a flush
// everything it said since the last newline-buffered write is lost whenever
// the process is killed rather than exiting cleanly -- which is exactly the
// case you most want the log for.
void OSReport(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    fflush(0);
}

void OSVReport(const char* msg, va_list list)
{
    vprintf(msg, list);
    fflush(0);
}

// --- Panic ----------------------------------------------------------------
//
// Aurora declares OSPanic (weak) but does not define it. It is the tree's
// fatal-error path -- HSD_ASSERT, NOT_IMPLEMENTED under BUGFIX, and every
// generated stub in undefined_stubs.c end up here.

void OSPanic(const char* file, int line, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    OSReport("melee_pc: PANIC at %s:%d: ", file, line);
    OSVReport(msg, args);
    va_end(args);
    OSReport("\n");
    fflush(0);  // abort() does not flush, and the message is the whole point
    abort();
}

// --- Interrupts -----------------------------------------------------------
//
// The game guards short critical sections with these, expecting its own
// interrupt handlers to be held off in between. There is no interrupt
// controller here, so "delivery" means running the work at the point where
// hardware would have interrupted: the moment interrupts become enabled again.
//
// Per-thread, and delivery restricted to the game's own thread.
//
// aurora runs disc reads on a worker thread and calls
// melee's DVD completion callbacks from it, so two threads interleave here, which resulted
// in a big deadlock
//
//   main:   OSDisableInterrupts()      prev=true,  irq=false
//   worker: OSDisableInterrupts()      prev=false, irq=false
//   main:   OSRestoreInterrupts(true)              irq=true
//   worker: OSRestoreInterrupts(false)             irq=false   <- cock
//
// Thread-local state makes each thread's nesting self-consistent. Delivery
// still only happens on the game's thread: the completions run melee code that
// is single-threaded by construction, and running it from the worker is the
// race this is trying to contain, not something to spread further.
static __thread bool irq_enabled = true;
static __thread bool is_game_thread;

// Called from melee_pc's entry point before melee_main().
void melee_pc_mark_game_thread(void) { is_game_thread = true; }

// Counters for the crash/hang snapshot in pc_main.c. A hang that leaves these
// frozen means the game is spinning somewhere that never re-enables
// interrupts, so nothing queued can ever be delivered.
unsigned long melee_pc_dbg_deliver;
unsigned long melee_pc_dbg_deliver_blocked;

static void deliver_interrupts(void)
{
    static bool in_delivery;
    // never deliver interrupts outside the gamet hread, this prevents
    // deadlocks
    if (!is_game_thread) {
        return;
    }

    melee_pc_arq_drain();     // stands in for the ARAM DMA completion

    if (in_delivery) {
        melee_pc_dbg_deliver_blocked++;
        return;
    }
    in_delivery = true;
    melee_pc_dbg_deliver++;
    melee_pc_card_drain();    // stands in for the memory card's EXI completion
    melee_pc_alarms_poll();   // stands in for the decrementer/alarm interrupt
    melee_pc_vi_poll();       // stands in for the VI vertical-retrace interrupt
    in_delivery = false;
}

BOOL OSDisableInterrupts(void)
{
    BOOL prev = irq_enabled;
    irq_enabled = false;
    return prev;
}

BOOL OSRestoreInterrupts(BOOL level)
{
    BOOL prev = irq_enabled;
    irq_enabled = level;
    if (level) {
        deliver_interrupts();
    }
    return prev;
}

BOOL OSEnableInterrupts(void)
{
    BOOL prev = irq_enabled;
    irq_enabled = true;
    deliver_interrupts();
    return prev;
}

// The alarm and VI schedulers need a clock, and aurora's OSGetTime() is the
// wrong one to use for it, for two reasons, it's expensive as hell and it's not monotonic.

struct melee_pc_timespec {
    long tv_sec;
    long tv_nsec;
};
int clock_gettime(int clk_id, struct melee_pc_timespec* tp);
#define MELEE_PC_CLOCK_MONOTONIC 1

static OSTime melee_pc_now(void)
{
    struct melee_pc_timespec ts;

    if (clock_gettime(MELEE_PC_CLOCK_MONOTONIC, &ts) != 0) {
        return 0;
    }
    return (OSTime) ts.tv_sec * (OSTime) OS_TIMER_CLOCK +
           (OSTime) ts.tv_nsec * (OSTime) OS_TIMER_CLOCK / 1000000000LL;
}

#define MAX_ALARMS 16

static struct {
    OSAlarm* alarm;         // identity; NULL means the slot is free
    OSTime next;            // absolute time of the next firing
    OSTime period;          // 0 for a one-shot
    OSAlarmHandler handler;
} alarm_slots[MAX_ALARMS];

static int alarm_slot(OSAlarm* alarm)
{
    int i, free_slot = -1;
    for (i = 0; i < MAX_ALARMS; i++) {
        if (alarm_slots[i].alarm == alarm) {
            return i;
        }
        if (free_slot < 0 && alarm_slots[i].alarm == NULL) {
            free_slot = i;
        }
    }
    return free_slot;
}

static void alarm_arm(OSAlarm* alarm, OSTime first, OSTime period,
                      OSAlarmHandler handler)
{
    int i = alarm_slot(alarm);
    if (i < 0) {
        OSReport("melee_pc: out of alarm slots (max %d)\n", MAX_ALARMS);
        return;
    }
    alarm_slots[i].alarm = alarm;
    alarm_slots[i].next = melee_pc_now() + first;
    alarm_slots[i].period = period;
    alarm_slots[i].handler = handler;
}

// Fires every alarm that has come due. Called from interrupt delivery, so it
// must not be re-entered, deliver_interrupts() guarantees that.
void melee_pc_alarms_poll(void)
{
    OSTime now = melee_pc_now();
    int i;

    for (i = 0; i < MAX_ALARMS; i++) {
        OSAlarmHandler handler;

        if (alarm_slots[i].alarm == NULL || alarm_slots[i].next > now) {
            continue;
        }

        handler = alarm_slots[i].handler;
        if (alarm_slots[i].period > 0) {
            // Reschedule from *now*, not from the missed deadline. Advancing
            // by whole periods would queue up every tick missed while the game
            // was loading an archive and then fire them back to back.
            alarm_slots[i].next = now + alarm_slots[i].period;
        } else {
            alarm_slots[i].alarm = NULL;
        }

        if (handler != NULL) {
            // Melee installs handlers cast from void(void) (lb_0195.c:116)
            // the extra arguments are simply ignored on every ABI here.
            handler(alarm_slots[i].alarm, NULL);
        }
    }
}

void OSInitAlarm(void) {}

void OSCreateAlarm(OSAlarm* alarm)
{
    int i = alarm_slot(alarm);
    if (i >= 0 && alarm_slots[i].alarm == alarm) {
        alarm_slots[i].alarm = NULL; // re-created: drop any previous schedule
    }
}

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler)
{
    alarm_arm(alarm, tick, 0, handler);
}

void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period,
                        OSAlarmHandler handler)
{
    alarm_arm(alarm, start, period, handler);
}

void OSCancelAlarm(OSAlarm* alarm)
{
    int i;
    for (i = 0; i < MAX_ALARMS; i++) {
        if (alarm_slots[i].alarm == alarm) {
            alarm_slots[i].alarm = NULL;
        }
    }
}

// --- System state ---------------------------------------------------------

s32 OSCheckActiveThreads(void) { return 0; }
u32 OSGetConsoleSimulatedMemSize(void) { return 24 * 1024 * 1024; }
u32 OSGetResetCode(void) { return 0; }
BOOL OSGetResetSwitchState(void) { return false; }
void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu)
{
    COMPAT_STUB();
    (void) reset; (void) resetCode; (void) forceMenu;
}
u32 OSSaveContext(OSContext* context) { (void) context; return 0; }

// Console settings that live in the GameCube's RTC/SRAM. Fixed values here.
u32 OSGetSoundMode(void) { return 1; }            // stereo
void OSSetSoundMode(u32 mode) { (void) mode; }
u32 OSGetProgressiveMode(void) { return 0; }
void OSSetProgressiveMode(u32 on) { (void) on; }

// --- VI -------------------------------------------------------------------
//
// Retrace is an *interrupt* here, not something the game waits on. sysdolphin
// runs a double-buffer state machine (HSD_VIPreRetraceCB/HSD_VIPostRetraceCB
// in video.c) that advances only from those callbacks, and melee's frame loop
// ends at HSD_VICopyXFBAsync without ever calling VIWaitForRetrace.
//
// So VI is modelled as a third interrupt source, polled alongside ARQ and the
// alarms: a 60 Hz tick that pumps aurora and then runs the game's callbacks.

#define VI_PERIOD_TICKS (OS_TIMER_CLOCK / 60)

static VIRetraceCallback pre_retrace_cb;
static VIRetraceCallback post_retrace_cb;
static u32 retrace_count;
static OSTime vi_next;

// One simulated vertical retrace: finish the frame the game just drew, pump
// aurora's events, open the next frame, then hand the callbacks their tick.
static void vi_retrace(void)
{
    melee_pc_frame_pump();

    retrace_count++;
    if (pre_retrace_cb != NULL) {
        pre_retrace_cb(retrace_count);
    }
    if (post_retrace_cb != NULL) {
        post_retrace_cb(retrace_count);
    }
}

// Guarded separately from deliver_interrupts() because VIWaitForRetrace()
// polls this directly: a callback that re-enables interrupts must not be able
// to recurse into another retrace partway through this one.
// True while a simulated retrace is being serviced. File scope because
// VIWaitForRetrace() has to know: waiting for a retrace from inside one can
// never be satisfied.
static bool in_retrace;

void melee_pc_vi_poll(void)
{
    OSTime now = melee_pc_now();

    if (in_retrace) {
        return;
    }
    if (vi_next == 0) {
        vi_next = now + VI_PERIOD_TICKS;
        return;
    }
    if (now < vi_next) {
        return;
    }

    // Scheduled from now rather than by advancing whole periods, so a long
    // archive load does not leave a burst of retraces owing.
    vi_next = now + VI_PERIOD_TICKS;

    in_retrace = true;
    vi_retrace();
    in_retrace = false;
}

// Used during boot (dbinit.c, initialize.c) and by HSD_VIWaitXFBFlush. Polls
// the interrupt sources directly rather than going through the irq-enable
// gate: a wait-for-retrace is inherently a poll, and the callers may well hold
// a critical section.
void VIWaitForRetrace(void)
{
    u32 start = retrace_count;
    OSTime deadline;

    // Already servicing a retrace. melee's pre-retrace callback does real work
    // and calls back into the game (video.c:115), and HSD_VIWaitXFBFlush()
    // waits here in a loop, so this nests in practice. melee_pc_vi_poll()
    // refuses to re-enter, so retrace_count could never advance and this
    // spun forever -- the intermittent hang just after boot. On hardware you
    // are inside an interrupt handler here and cannot wait for the next
    // interrupt either, so returning immediately is also the honest answer.
    if (in_retrace) {
        return;
    }

    // A retrace is due every 1/60s. If one has not arrived in a second
    // something is wrong, and a diagnostic beats a freeze.
    deadline = melee_pc_now() + (OSTime) OS_TIMER_CLOCK;

    while (retrace_count == start) {
        melee_pc_arq_drain();
        melee_pc_alarms_poll();
        melee_pc_vi_poll();

        if (melee_pc_now() > deadline) {
            OSReport("melee_pc: no VI retrace for a second; giving up on the "
                     "wait (retrace_count=%u)\n", retrace_count);
            return;
        }
    }
}
int melee_pc_dbg_in_retrace(void) { return in_retrace ? 1 : 0; }

int melee_pc_dbg_irq_enabled(void) { return irq_enabled ? 1 : 0; }

void melee_pc_dbg_vi_state(long long* now, long long* next, long long* period)
{
    *now = (long long) melee_pc_now();
    *next = (long long) vi_next;
    *period = (long long) VI_PERIOD_TICKS;
}

u32 VIGetNextField(void) { return retrace_count & 1; }

// Frames since boot, for melee_compat/src/pad_inject.c.
unsigned long melee_pc_retrace_count(void) { return retrace_count; }
u32 VIGetDTVStatus(void) { return 0; }
void VISetBlack(BOOL black) { (void) black; }
void VISetNextFrameBuffer(void* fb) { (void) fb; }

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb)
{
    VIRetraceCallback old = pre_retrace_cb;
    pre_retrace_cb = cb;
    return old;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb)
{
    VIRetraceCallback old = post_retrace_cb;
    post_retrace_cb = cb;
    return old;
}

// --- GX -------------------------------------------------------------------

void GXSetCopyClamp(GXFBClamp clamp) { (void) clamp; }
void GXSetMisc(GXMiscToken token, u32 val) { (void) token; (void) val; }

// Progressive-scan render mode. Aurora declares the symbol but only defines
// the interlaced modes; copy the 480i geometry.
GXRenderModeObj GXNtsc480Prog;

double __frsqrte(double x) { return 1.0 / sqrt(x); }
double __fabs(double x) { return __builtin_fabs(x); }
float __fabsf(float x) { return __builtin_fabsf(x); }
float __fnmsubs(float a, float b, float c) { return -(a * b - c); }
