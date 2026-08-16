include(${CMAKE_CURRENT_LIST_DIR}/sources.cmake)

option(MELEE_PC_ABI32 "Build with the 32-bit GameCube-compatible ABI" OFF)

add_library(melee_pc_abi INTERFACE)
if(MELEE_PC_ABI32)
  if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    message(FATAL_ERROR "MELEE_PC_ABI32 requires GCC or Clang")
  endif()
  target_compile_options(melee_pc_abi INTERFACE -m32 -malign-double)
  target_link_options(melee_pc_abi INTERFACE -m32)
else()
  # Struct layouts will not match the GameCube ABI. Everything still compiles;
  # DAT-loaded data will be read at the wrong offsets until the relocating
  # loader exists. See docs/cmake_pc_port.md.
endif()

# Aurora's dolphin headers are narrower than extern/dolphin's in a few places
# (see melee_compat/README.md). melee_compat fixes that, it is
# placed *before* aurora on the include path and uses #include_next so aurora
# still wins wherever it has a real declaration.
add_library(melee_compat INTERFACE)
target_include_directories(melee_compat SYSTEM INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/melee_compat/include
  ${CMAKE_CURRENT_SOURCE_DIR}/extern/aurora/include
)

add_library(melee_pc_warnings INTERFACE)
target_compile_options(melee_pc_warnings INTERFACE
  -Wall
  -Wextra
  -Werror=implicit-function-declaration
  -Werror=implicit-int
  -Werror=incompatible-pointer-types
  -Werror=strict-prototypes
  -Wno-bitfield-constant-conversion
  -Wno-builtin-macro-redefined
  -Wno-format
  -Wno-missing-braces
  -Wno-missing-field-initializers
  -Wno-return-type
  -Wno-sign-compare
  -Wno-switch
  -Wno-unknown-pragmas          # there's a bunch of mwcc only pragmas, so ignore those
  -Wno-unused-but-set-variable
  -Wno-unused-function
  -Wno-unused-parameter
  -Wno-unused-value
  -Wno-unused-variable
)
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  target_compile_options(melee_pc_warnings INTERFACE
    -Wno-for-loop-analysis
    -Wno-gnu-folding-constant
    -Wno-incompatible-library-redeclaration
    -Wno-self-assign
    -Wno-sometimes-uninitialized
    -Wno-tautological-compare
    -Wno-undefined-internal
    -Wno-uninitialized
    -Wno-unsequenced
  )
endif()

add_library(melee_pc_options INTERFACE)
target_compile_options(melee_pc_options INTERFACE
  -include ${CMAKE_CURRENT_SOURCE_DIR}/melee_compat/include/melee_pc_prelude.h
  -fno-short-enums      # matches mwcc; enums are int-sized
  # Inline the functions the tree marks `inline`, at every optimisation level.
  #
  # many functions are defined `inline` inside .c files (GObj_SetFlag2_inline
  # and friends). Under C99 a plain inline definition provides NO external
  # definition, so at -O0, where nothing is inlined, every call to one is an
  # undefined symbol and the link fails. mwcc, using C89 semantics emits a definition
  # instead, which is why the matching build never notices
  #
  # -fgnu89-inline would restore mwcc's behaviour but overshoots: the 12 plain
  # `inline` functions in *headers* would then get a strong definition in each
  # of the 900+ TUs that include them. Inlining them instead sidesteps the whole
  # question, and only affects functions the source explicitly hinted.
  #
  # NOTE: this has no effect at -O0, where clang marks every function `optnone`
  # and the inliner never runs. Debug builds must use -Og; see the check below.
  -finline-hint-functions
  -fno-strict-aliasing  # the tree type-puns constantly
  -ffp-contract=off     # matches `-fp_contract off` in the mwcc SDK build
  -fwrapv
)
target_compile_definitions(melee_pc_options INTERFACE
  BUGFIX      # the PC build wants the bug fixes, and real OSPanic bodies
  MELEE_PC    # guards the handful of unavoidable host-only source changes
  AURORA
  TARGET_PC
)

target_include_directories(melee_pc_options SYSTEM INTERFACE
  # MUST come first: several compat headers replace same-named MSL headers
  # and the ordering is what decides which one wins.
  ${CMAKE_CURRENT_SOURCE_DIR}/melee_compat/include
  ${CMAKE_CURRENT_SOURCE_DIR}/extern/aurora/include
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/MSL
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Runtime      # platform.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sysdolphin
)
target_include_directories(melee_pc_options INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/melee
  ${CMAKE_CURRENT_SOURCE_DIR}/src/melee/ft/chara
)
target_link_libraries(melee_pc_options INTERFACE
  melee_pc_abi melee_compat melee_pc_warnings
)

# Sources known not to compile yet. Tracked explicitly rather than silently
# dropped, so the number is visible and shrinks over time.
include(${CMAKE_CURRENT_LIST_DIR}/pc_excluded.cmake)

set(_melee_all ${MELEE_SOURCES_GAME} ${MELEE_SOURCES_HSD})
list(REMOVE_ITEM _melee_all ${MELEE_PC_EXCLUDED})

add_library(melee_game OBJECT ${_melee_all})
target_link_libraries(melee_game PRIVATE melee_pc_options)

set_source_files_properties(src/sysdolphin/baselib/synth.c
  TARGET_DIRECTORY melee_game
  PROPERTIES COMPILE_DEFINITIONS "HSD_SynthSFXLoad=HSD_SynthSFXLoad_disabled")

set_source_files_properties(src/melee/lb/lbaudio_ax.c
  TARGET_DIRECTORY melee_game
  PROPERTIES COMPILE_DEFINITIONS "lbAudioAx_80027648=lbAudioAx_80027648_disabled")

# aurora has to initialise first and the disc has to be open before DVDInit.
# We rename it lets so pc_main.c can steal the entry point without editing the
# source.
set_source_files_properties(src/melee/gm/gmmain.c
  TARGET_DIRECTORY melee_game
  PROPERTIES COMPILE_DEFINITIONS "main=melee_main")

set_source_files_properties(src/melee/it/items/ithitodeman.c
  TARGET_DIRECTORY melee_game
  PROPERTIES COMPILE_DEFINITIONS "sqrtf=melee_pc_sqrtf_ithitodeman")

# These two files each define their own `extern inline float sqrtf` in the .c
# file itself. Under C99 that is an *external* definition, so the two collide
# at link time (C89 tolerates it)

set_source_files_properties(src/melee/ft/chara/ftCommon/ftCo_ThrownKirby.c
  TARGET_DIRECTORY melee_game
  PROPERTIES COMPILE_DEFINITIONS "sqrtf=melee_pc_sqrtf_ftCoThrownKirby")

# Stubs for the SDK modules aurora does not implement, AR/ARQ, AX,
# AXFX, AI, MCC, THP, DB + the individual GX/VI/CARD entry points.
# ARAM is emulated with a heap block and ARQ DMA with memcpy.
add_library(melee_compat_impl STATIC
  melee_compat/src/ai_stubs.c
  melee_compat/src/audio_heap.c
  melee_compat/src/card_work.c
  melee_compat/src/card_async.c
  melee_compat/src/pad_inject.c
  melee_compat/src/ar_stubs.c
  melee_compat/src/ax_stubs.c
  melee_compat/src/axfx_stubs.c
  melee_compat/src/inline_defs.c
  melee_compat/src/misc_stubs.c
  melee_compat/src/os_stubs.c
  melee_compat/src/game_stubs.c
  melee_compat/src/gx_arrays.c
  melee_compat/src/dat_reloc.c
  melee_compat/src/varargs.c
)
target_link_libraries(melee_compat_impl PRIVATE melee_pc_options)

# The PC entry point needs the real libc
# headers, so it gets its own target rather than MSL's (src/MSL/stdint.h
# shadows the host's and breaks <inttypes.h>, which aurora's headers include).
add_library(melee_pc_entry STATIC melee_compat/src/pc_main.c)
target_include_directories(melee_pc_entry SYSTEM PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/extern/aurora/include)
target_include_directories(melee_pc_entry PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/melee_compat/src)

# This may appear incorrect, but it's actually not, they do genuinely reference eachother
# and apparently cmake allows it???
target_link_libraries(melee_pc_entry PUBLIC melee_compat_impl)
target_link_libraries(melee_compat_impl PUBLIC melee_pc_entry)

list(LENGTH _melee_all _n_built)
list(LENGTH MELEE_PC_EXCLUDED _n_excluded)
message(STATUS "melee PC: building ${_n_built} sources, ${_n_excluded} excluded")
