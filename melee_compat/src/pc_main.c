// PC entry point
// this sets up aurora and any ancilliary stuff and then hands it off to the real
// game main()

#include <aurora/aurora.h>
#include <aurora/dvd.h>
#include <aurora/event.h>
#include <aurora/main.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <execinfo.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>

#include "compat_pc.h"

#include <dolphin/os.h>

// Declared here rather than via <melee_pc_gx.h>: this file is built with normal libc
// and melee_compat/include carries the MSL-shadowing headers that
// the game sources need but this one must not see.
void melee_pc_set_mem1(const void* start, unsigned int size);
void melee_pc_arq_drain(void);
void melee_pc_alarms_poll(void);
void melee_pc_mark_game_thread(void);
int melee_pc_dat_selftest(void);

// gmmain.c's main(), renamed by -Dmain=melee_main.
int melee_main(void);

static AuroraInfo aurora_info;

// The GameCube's OS globals, mapped at the address the hardware puts them.
//
// Some parts of the code read the clock directly from memory, so the page is
// simply mapped where they expect it.
//
// On hardware these bytes are the start of MEM1. Here they are a separate
// mapping, because MEM1 itself has to live below 2GB,
//
// MAP_FIXED_NOREPLACE rather than MAP_FIXED so a collision is reported
// instead of silently unmapping something.
#define OS_GLOBALS_BASE ((void*) 0x80000000UL)
#define OS_GLOBALS_SIZE 0x4000

static void crash_handler(int sig)
{
    void* frames[32];
    int n = backtrace(frames, (int) (sizeof(frames) / sizeof(frames[0])));
    const char* name = sig == SIGSEGV   ? "SIGSEGV"
                       : sig == SIGABRT ? "SIGABRT"
                       : sig == SIGBUS  ? "SIGBUS"
                       : sig == SIGFPE  ? "SIGFPE"
                                        : "signal";

    write(STDOUT_FILENO, "\nmelee_pc: caught ", 18);
    write(STDOUT_FILENO, name, strlen(name));
    write(STDOUT_FILENO, ", backtrace:\n", 13);

    // Interrupt-delivery snapshot
    {
        extern unsigned long melee_pc_dbg_deliver;
        extern unsigned long melee_pc_dbg_deliver_blocked;
        extern unsigned long melee_pc_arq_pending(void);
        extern unsigned long melee_pc_dbg_arq_posted;
        extern unsigned long melee_pc_dbg_arq_done;
        melee_pc_printf("melee_pc: deliver=%lu blocked=%lu  arq pending=%lu "
                        "posted=%lu done=%lu\n",
                        melee_pc_dbg_deliver, melee_pc_dbg_deliver_blocked,
                        melee_pc_arq_pending(), melee_pc_dbg_arq_posted,
                        melee_pc_dbg_arq_done);
    }
    {
        // Whether the simulated retrace is still ticking separates "the game
        // is spinning on something we never complete" from "the retrace that
        // would feed it has itself stalled".
        extern unsigned long melee_pc_retrace_count(void);
        extern int melee_pc_dbg_in_retrace(void);
        extern void melee_pc_pad_report(void);
        extern void melee_pc_dbg_vi_state(long long*, long long*, long long*);
        long long vnow, vnext, vperiod;
        melee_pc_dbg_vi_state(&vnow, &vnext, &vperiod);
        melee_pc_printf("melee_pc: retrace=%lu in_retrace=%d now=%lld "
                        "next=%lld delta=%lld period=%lld\n",
                        melee_pc_retrace_count(), melee_pc_dbg_in_retrace(),
                        vnow, vnext, vnow - vnext, vperiod);
        melee_pc_pad_report();
    }
    backtrace_symbols_fd(frames, n, STDOUT_FILENO);

    // Restore the default and re-raise so the exit status and any core dump
    // still reflect the original fault.
    signal(sig, SIG_DFL);
    raise(sig);
}

static void install_crash_handler(void)
{
    signal(SIGSEGV, crash_handler);
    signal(SIGBUS, crash_handler);
    signal(SIGFPE, crash_handler);
    signal(SIGABRT, crash_handler);
}

static void map_os_globals(void)
{
    void* p = mmap(OS_GLOBALS_BASE, OS_GLOBALS_SIZE, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);

    if (p == MAP_FAILED || p != OS_GLOBALS_BASE) {
        melee_pc_printf("melee_pc: could not map OS globals at %p; reads of "
                        "0x800000F8 will crash\n", OS_GLOBALS_BASE);
        return;
    }

    // The two clocks aurora also reports through __OSBusClock/__OSCoreClock.
    // Everything else stays zero, which is what a fresh page gives us.
    *(unsigned int*) 0x800000F8 = 162000000u;      // bus clock
    *(unsigned int*) 0x800000FC = 162000000u * 3u; // core clock
}

static bool exiting;
static bool frame_open;

// Called once per frame from VIWaitForRetrace (os_stubs.c), which is where
// melee blocks waiting for the video interface.
void melee_pc_frame_pump(void)
{
    const AuroraEvent* event;

    // ARQ completions stand in for the DMA interrupt that would deliver them
    // on hardware. Alarms are normally delivered from OSRestoreInterrupts, but
    // a frame the game spends blocked on VI rather than on the pad queue would
    // otherwise let their schedule drift.
    melee_pc_arq_drain();
    melee_pc_alarms_poll();

    if (frame_open) {
        aurora_end_frame();
        frame_open = false;
    }

    for (event = aurora_update(); event != NULL && event->type != AURORA_NONE;
         ++event) {
        switch (event->type) {
        case AURORA_EXIT:
            exiting = true;
            break;
        case AURORA_WINDOW_RESIZED:
            aurora_info.windowSize = event->windowSize;
            break;
        default:
            break;
        }
    }

    if (exiting) {
        aurora_shutdown();
        exit(0);
    }

    frame_open = aurora_begin_frame();

    // Progress marker: distinguishes "running the game loop" from "hung".
    // The draw counters are temporary diagnostics patched into aurora's command proccessor
    {
        extern unsigned long melee_pc_dbg_draw_prim;
        extern unsigned long melee_pc_dbg_draw_verts;
        extern unsigned long melee_pc_dbg_vtxsize0;
        extern unsigned long melee_pc_dbg_setproj;
        extern unsigned long melee_pc_dbg_setvp;
        extern float melee_pc_dbg_vp[6];
        extern float melee_pc_dbg_proj[16];
        extern int melee_pc_dbg_projtype;
        extern unsigned long melee_pc_dbg_posmtx;
        extern float melee_pc_dbg_pm[12];
        extern unsigned long melee_pc_dbg_setarray;
        extern unsigned long melee_pc_dbg_arr_size0;
        extern unsigned long melee_pc_dbg_last_arr_size;
        extern unsigned long melee_pc_dbg_last_arr_stride;
        extern const void* melee_pc_dbg_last_arr_data;
        // Off unless MELEE_PC_DBG_RENDER is set
        static int want = -1;
        static unsigned long frames;
        if (want < 0) {
            want = getenv("MELEE_PC_DBG_RENDER") != NULL;
        }
        if (++frames % 60 == 0 && want) {
            extern void melee_pc_pad_report(void);
            melee_pc_pad_report();
            melee_pc_printf("melee_pc: %lu frames, draws=%lu verts=%lu "
                            "vtxsize0=%lu\n",
                            frames, melee_pc_dbg_draw_prim,
                            melee_pc_dbg_draw_verts, melee_pc_dbg_vtxsize0);
            melee_pc_printf("           proj=%lu vp=%lu [%.1f %.1f %.1f %.1f "
                            "%.2f %.2f]\n",
                            melee_pc_dbg_setproj, melee_pc_dbg_setvp,
                            melee_pc_dbg_vp[0], melee_pc_dbg_vp[1],
                            melee_pc_dbg_vp[2], melee_pc_dbg_vp[3],
                            melee_pc_dbg_vp[4], melee_pc_dbg_vp[5]);
            melee_pc_printf("           projtype=%d "
                            "[%.3f %.3f %.3f %.3f | %.3f %.3f %.3f %.3f | "
                            "%.3f %.3f %.3f %.3f | %.3f %.3f %.3f %.3f]\n",
                            melee_pc_dbg_projtype,
                            melee_pc_dbg_proj[0], melee_pc_dbg_proj[1],
                            melee_pc_dbg_proj[2], melee_pc_dbg_proj[3],
                            melee_pc_dbg_proj[4], melee_pc_dbg_proj[5],
                            melee_pc_dbg_proj[6], melee_pc_dbg_proj[7],
                            melee_pc_dbg_proj[8], melee_pc_dbg_proj[9],
                            melee_pc_dbg_proj[10], melee_pc_dbg_proj[11],
                            melee_pc_dbg_proj[12], melee_pc_dbg_proj[13],
                            melee_pc_dbg_proj[14], melee_pc_dbg_proj[15]);
            melee_pc_printf("           posmtx=%lu pm=[%.2f %.2f %.2f %.2f | "
                            "%.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f]\n",
                            melee_pc_dbg_posmtx,
                            melee_pc_dbg_pm[0], melee_pc_dbg_pm[1],
                            melee_pc_dbg_pm[2], melee_pc_dbg_pm[3],
                            melee_pc_dbg_pm[4], melee_pc_dbg_pm[5],
                            melee_pc_dbg_pm[6], melee_pc_dbg_pm[7],
                            melee_pc_dbg_pm[8], melee_pc_dbg_pm[9],
                            melee_pc_dbg_pm[10], melee_pc_dbg_pm[11]);
            melee_pc_printf("           setarray=%lu size0=%lu last=%p "
                            "size=%lu stride=%lu\n",
                            melee_pc_dbg_setarray, melee_pc_dbg_arr_size0,
                            melee_pc_dbg_last_arr_data,
                            melee_pc_dbg_last_arr_size,
                            melee_pc_dbg_last_arr_stride);
        }
    }
}

int melee_pc_printf(const char* fmt, ...)
{
    va_list args;
    int n;
    va_start(args, fmt);
    n = vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
    return n;
}

static void log_callback(AuroraLogLevel level, const char* module,
                         const char* message, unsigned int len)
{
    static const char* names[] = { "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };
    (void) len;
    melee_pc_printf("[%s] [%s] %s\n",
                    level <= LOG_FATAL ? names[level] : "?", module, message);
}

static const char* find_disc(int argc, char* argv[])
{
    const char* env;
    int i;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            return argv[i];
        }
    }

    env = getenv("MELEE_ISO");
    return env;
}

int main(int argc, char* argv[])
{
    const char* disc = find_disc(argc, argv);

    const AuroraConfig config = {
        .appName = "Super Smash Bros. Melee",
        .logCallback = &log_callback,
        .logLevel = LOG_INFO,
        .vsync = true,
        .windowWidth = 1280,
        .windowHeight = 1056,
        .mem1Size = MEM1_DEFAULT_SIZE,
        // ARAM is emulated by us, so aurora does not need to reserve its own.
        .mem2Size = 0,
    };

    if (disc == NULL) {
        melee_pc_printf(
            "usage: melee_pc <path-to-GALE01.iso>   (or set $MELEE_ISO)\n");
        return 1;
    }

    // Keep every host allocation in the low 2GB.
    //
    // The game stores pointers in u32 fields well beyond the DAT format:
    //
    // glibc satisfies large requests with mmap (which can land anywhere) and
    // small ones from the brk heap, which sits just above the executable --
    // low, because this is linked -no-pie. Raising the mmap threshold keeps
    // everything on brk without giving up malloc/free semantics.
    mallopt(M_MMAP_THRESHOLD, 512 * 1024 * 1024);
    mallopt(M_TRIM_THRESHOLD, 512 * 1024 * 1024);

    install_crash_handler();

    // Before any game code runs: seven sites read the bus clock from a
    // literal low-memory address.
    map_os_globals();

    aurora_info = aurora_initialize(argc, argv, &config);

    // Where MEM1 landed, so melee_pc_array_size() can clamp uploads to it.
    melee_pc_set_mem1((const void*) OSBaseAddress, config.mem1Size);

    // Must precede DVDInit(), which melee calls from its own main.
    if (!aurora_dvd_open(disc)) {
        melee_pc_printf("melee_pc: could not open disc image: %s\n", disc);
        return 1;
    }
    melee_pc_printf("melee_pc: disc opened: %s\n", disc);

    if (getenv("MELEE_PC_DAT_SELFTEST") != NULL) {
        return melee_pc_dat_selftest() == 0 ? 0 : 1;
    }

    melee_pc_mark_game_thread();

    return melee_main();
}
