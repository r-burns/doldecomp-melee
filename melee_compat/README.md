# melee_compat

Compatibility layer for the CMake/aurora PC build.

Aurora covers most of the GameCube SDK, but not all of it, and where it does
cover something its API sometimes differs from the original. This compatibility layer fixes that, but does nothing else.

`include/` is placed **before** aurora on the include path, and its headers use
`#include_next`, so aurora still wins wherever it has a real declaration.

## `include/` — declarations

| Header | Adds missing |
| --- | --- |
| `melee_pc_prelude.h` | globally included into every TU |
| `dolphin/types.h` | `ARRAY_SIZE` |
| `dolphin/pad.h` | melee's pad input |
| `dolphin/gx.h` | various missing graphics functions |
| `dolphin/vi.h` | `VIPadFrameBufferWidth` |
| `dolphin/card.h` | `CARDFormatAsync`; rewrites `CARDInit()` to pass melee's game/maker codes |
| `dolphin/thp.h` | `THPDec_8032FD40_Data` |
| `dolphin/axfx.h` | Vendored from `extern/dolphin` |
| `dolphin.h`, `dolphin/vi/vifuncs.h`, `dolphin/card/CARDBios.h` | Redirects for extern/dolphin paths some sources include directly |
| `ctype.h` | Replaces MSL's, which needs `__ctype_map` from a file the PC build does not compile |
| `math_ppc.h` | implements missing ppc specific math stuff |
| `stdarg.h` | Replaces MSL's, which is built on mwcc's PowerPC varargs ABI |
| `stddef.h` | Replaces MSL's, which hardcodes `uintptr_t` as `unsigned int` |

### The prelude

`melee_pc_prelude.h` is force-included (`-include`) into every translation
unit. Under mwcc many sources reach declarations for `memset`/`memcpy`/`str*`
and parts of the OS and PAD APIs *transitively*, through extern/dolphin's
header graph; aurora's headers have a different shape, so those go missing.

Fixing that by adding `#include`s to the sources themselves is **not an
option**: it changes mwcc's codegen. That was measured — adding
`<string.h>`/`<math.h>` to 22 files altered the object bytes of 8 of them.
Header *order* matters too: re-sorting one include block in `lbarchive.c`
changed which `size_t` won and broke the mwcc build outright.

## `src/` — implementations

Stubs for the SDK modules aurora does not implement at all. Every stub reports
once on first call (`COMPAT_STUB()`), so missing functionality is visible in
the log rather than silent.

| File | Module | Behaviour |
| --- | --- | --- |
| `ar_stubs.c` | AR / ARQ | ARAM emulated with a 16 MiB static block; ARQ DMA becomes a synchronous `memcpy` with an immediate completion callback |
| `ax_stubs.c` | AX | Silent audio. Voices come from a fixed pool so the game's bookkeeping works; nothing is mixed or played |
| `axfx_stubs.c` | AXFX | No-ops returning success |
| `ai_stubs.c` | AI | No-ops |
| `misc_stubs.c` | MCC, THP, DB, GX, VI, cache ops | MCC always "not connected"; THP reports end-of-stream; no debugger; `DCFlushRange` and friends are real no-ops, since they are on every DMA path |
| `os_stubs.c` | OS, VI, GX | `OSReport`/`OSVReport`/`OSPanic` (aurora declares these weak and never defines them), interrupts, alarms, RTC settings, retrace, PPC math intrinsics |
| `inline_defs.c` | N/A | The single out-of-line definition of each header `inline` function, which C99 otherwise leaves undefined |
| `varargs.c` | N/A | MSL's `__va_arg` for x86-64; pointer arguments only |
| `pc_main.c` | N/A | The new main |
| `game_stubs.c` | N/A | stubs functions that make no sense on x86 (like ppc specific ones) |

One important thing to note is that `#include_next` is a GCC/Clang extension. MSVC would need something else, but we'll do that when we get there.
