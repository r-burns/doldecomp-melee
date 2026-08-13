cmake_minimum_required(VERSION 3.20)

project(melee LANGUAGES C)

include(Sources.txt)

add_executable(melee ${SOURCES})

target_include_directories(melee PRIVATE
    extern/aurora/include
    src
    src/Runtime
    src/melee
    src/melee/ft/chara
    src/sysdolphin
)
