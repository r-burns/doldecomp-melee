# because getting aurora to build on 32 bit linux is a pain (and 32 bit linux is a pain in general)
# we have decided to build it as an x86_64 executable, the bad news is that this means we have to write
# a special DAT loader that relocates and fixes things, but oh well

option(MELEE_PC_LINK "Link the melee_pc executable (requires a 64-bit build)" OFF)

if(NOT MELEE_PC_LINK)
  return()
endif()

if(MELEE_PC_ABI32)
  message(FATAL_ERROR
    "MELEE_PC_LINK requires MELEE_PC_ABI32=OFF: aurora's Dawn dependency has "
    "no 32-bit target for any platform.")
endif()

# Debug builds must not use -O0. C99 says a plain `inline` definition provides
# no external definition, and many functions in the game defined plain
# `inline` inside .c files. At -O0 clang inlines nothing, so each of those
# becomes an undefined symbol. -Og inlines them while keeping full line tables
# and variable info.
# Note CMake's default Debug flags are just "-g", -O0 is the compiler's
# implicit default rather than an explicit flag, so check for the *absence* of
# an optimisation level too.
string(TOUPPER "${CMAKE_BUILD_TYPE}" _cfg)
set(_cfg_flags "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${_cfg}}")
if(_cfg_flags MATCHES "-O0" OR NOT _cfg_flags MATCHES "-O[1-9gsz]")
  message(WARNING
    "melee PC: -O0 will not link, the tree defines 265 functions plain "
    "`inline` inside .c files, which C99 leaves without an external "
    "definition. Use -Og instead, e.g.\n"
    "  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS_DEBUG=\"-Og -g\"\n"
    "See docs/cmake_pc_port.md.")
endif()

# ---------------------------------------------------------------------------
# Aurora
# ---------------------------------------------------------------------------
#
# The top-level project declares only C (the game is C); aurora is C++20, and
# on Apple platforms also Objective-C.
enable_language(CXX)
if(APPLE)
  enable_language(OBJC)
endif()

set(AURORA_ENABLE_GX ON CACHE BOOL "" FORCE)
set(AURORA_ENABLE_DVD ON CACHE BOOL "" FORCE)   # melee loads from the disc image
set(AURORA_ENABLE_CARD ON CACHE BOOL "" FORCE)  # save files
add_subdirectory(extern/aurora aurora EXCLUDE_FROM_ALL)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------
#
# main() is src/melee/gm/gmmain.c:145. Aurora's <aurora/main.h> does
# `#define main aurora_main`, so including it is what makes the game's main the
# aurora entry point.
add_executable(melee_pc)

# Linked non-PIE so the executable's own data lands at a low, fixed address
# (~0x400000) instead of somewhere above 4 GB.
#
# The game stores pointers in s32 fields all over the place, the card command
# queue is `s32 cmd[9]` with `cmd[1] = (s32) state` (hsd_3A94.c:2326), and
# CardBufEntry/CardCmd are the same shape. Those slots are 32 bits wide by
# construction and cannot be widened without changing the layouts the matching
# build pins. A PIE build loads static data far above 4 GB, so every such store
# truncated and the pointer came back as garbage. Keeping the image low makes
# the truncation lossless: the addresses fit in 31 bits, so they survive both
# the narrowing and the sign extension on the way back.
#
# This is the same reasoning as MAP_32BIT for MEM1 (see the aurora patch); the
# two together mean every pointer the game round-trips through a 32-bit slot is
# either in MEM1 or in the image, and both are addressable in 32 bits.
set_target_properties(melee_pc PROPERTIES POSITION_INDEPENDENT_CODE OFF)
target_link_options(melee_pc PRIVATE -no-pie)

target_link_libraries(melee_pc PRIVATE
  melee_game
  melee_pc_entry
  melee_compat_impl
  aurora::core
  aurora::os
  aurora::gx
  aurora::gd
  aurora::main
  aurora::vi
  aurora::pad
  aurora::mtx
  aurora::si
  aurora::dvd
  aurora::card
)

# The decomp is incomplete, this scripts uses the build logs to grab
# functions in the files excluded from the PC build, plus functions nobody has
# decompiled yet. Each undefined symbol gets a stub that
# panics if it is ever actually reached.
#
# The list comes from the linker:
#
#   cmake --build <dir> --target melee_pc 2>&1 \
#     | python tools/gen_undefined_stubs.py -o <dir>/undefined_stubs.c
#   cmake <dir> && cmake --build <dir> --target melee_pc
set(_stubs ${CMAKE_CURRENT_BINARY_DIR}/undefined_stubs.c)
if(EXISTS ${_stubs})
  target_sources(melee_pc PRIVATE ${_stubs})
  set_source_files_properties(${_stubs} PROPERTIES
    COMPILE_OPTIONS "-Wno-strict-prototypes;-Wno-missing-prototypes")
  message(STATUS "melee PC: linking with generated undefined_stubs.c")
else()
  message(STATUS
    "melee PC: no undefined_stubs.c yet, the first link will fail with "
    "undefined symbols; see cmake/melee_link.cmake")
endif()
