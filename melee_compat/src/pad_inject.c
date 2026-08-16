// Scripted controller input, for driving the game without a human.
//
// Most of what is left to port sits behind menus, and reaching it by hand
// is a bit of a pain specially if you are running multiple copies of the game to try for data races
// This wraps PADRead and ORs in button presses from a script, so a run can be told to
// press Start at frame 300 and A at frame 420

#include "compat_report.h"

// The prelude renames PADRead; this file needs the real one.
#undef PADRead

#include <dolphin/pad.h>

char* getenv(const char* name);
int melee_pc_printf(const char* fmt, ...);

// How many frames a scripted press is held. Long enough for the game to sample
// it on any reasonable poll cadence, short enough to read as a distinct tap.
#define PRESS_FRAMES 8

#define MAX_EVENTS 32

typedef struct {
    unsigned long frame;
    u16 button;
} PadEvent;

static PadEvent events[MAX_EVENTS];
static int held[MAX_EVENTS];
static int event_count;
static int parsed;
static unsigned long call_count;

static u16 button_from_name(const char* s, int len)
{
    struct {
        const char* name;
        u16 bit;
    } names[] = {
        { "START", PAD_BUTTON_START }, { "A", PAD_BUTTON_A },
        { "B", PAD_BUTTON_B },         { "X", PAD_BUTTON_X },
        { "Y", PAD_BUTTON_Y },         { "Z", PAD_TRIGGER_Z },
        { "UP", PAD_BUTTON_UP },       { "DOWN", PAD_BUTTON_DOWN },
        { "LEFT", PAD_BUTTON_LEFT },   { "RIGHT", PAD_BUTTON_RIGHT },
    };
    int i, j;

    for (i = 0; i < (int) (sizeof(names) / sizeof(names[0])); i++) {
        const char* n = names[i].name;
        for (j = 0; j < len && n[j] != '\0'; j++) {
            char c = s[j];
            if (c >= 'a' && c <= 'z') {
                c = (char) (c - 'a' + 'A');
            }
            if (c != n[j]) {
                break;
            }
        }
        if (j == len && n[j] == '\0') {
            return names[i].bit;
        }
    }
    return 0;
}

// "frame:BUTTON,frame:BUTTON,..."
static void parse_script(void)
{
    const char* s = getenv("MELEE_PC_INPUT");

    parsed = 1;
    if (s == NULL) {
        return;
    }

    while (*s != '\0' && event_count < MAX_EVENTS) {
        unsigned long frame = 0;
        const char* name;
        int len = 0;
        u16 bit;

        while (*s == ' ' || *s == ',') {
            s++;
        }
        if (*s < '0' || *s > '9') {
            break;
        }
        while (*s >= '0' && *s <= '9') {
            frame = frame * 10 + (unsigned long) (*s - '0');
            s++;
        }
        if (*s != ':') {
            break;
        }
        s++;

        name = s;
        while (*s != '\0' && *s != ',') {
            s++;
            len++;
        }
        bit = button_from_name(name, len);
        if (bit == 0) {
            melee_pc_printf("melee_pc: unknown button in MELEE_PC_INPUT\n");
            continue;
        }
        events[event_count].frame = frame;
        events[event_count].button = bit;
        event_count++;
    }

    if (event_count > 0) {
        melee_pc_printf("melee_pc: scripted input, %d event(s)\n", event_count);
    }
}

u32 melee_pc_pad_read(PADStatus* status)
{
    extern unsigned long melee_pc_retrace_count(void);
    u32 ret = PADRead(status);
    unsigned long now;
    int i;

    if (!parsed) {
        parse_script();
    }
    if (event_count == 0 || status == NULL) {
        return ret;
    }

    call_count++;
    now = melee_pc_retrace_count();
    for (i = 0; i < event_count; i++) {
        // The hold is counted in PADRead calls, not retraces: the game does
        // not poll the pad once per retrace (it polls from its own loop, at a
        // cadence that varies with what it is doing), so a window expressed in
        // retraces can open and close without a single read landing inside it.
        if (held[i] == 0 && now < events[i].frame) {
            continue;
        }
        if (held[i] >= PRESS_FRAMES) {
            continue;
        }
        held[i]++;
        // Port 0 only: melee reads all four but only the first is bound to
        // anything on a keyboard-less test run.
        status[0].button |= events[i].button;
        status[0].err = 0;
        if (held[i] == 1 || held[i] == PRESS_FRAMES) {
            melee_pc_printf("melee_pc: inject %s btn=0x%x at retrace=%lu "
                            "(read #%lu, hold %d/%d)\n",
                            held[i] == 1 ? "start" : "end",
                            (unsigned) events[i].button, now, call_count,
                            held[i], PRESS_FRAMES);
        }
    }
    return ret;
}

// Reports how much the game is actually polling, so a run that injects nothing
// can be told apart from a run that injects into a pad nobody reads.
void melee_pc_pad_report(void)
{
    if (event_count != 0) {
        melee_pc_printf("melee_pc: pad reads=%lu, events=%d\n", call_count,
                        event_count);
    }
}
