#ifndef __STDDEF_H__
#define __STDDEF_H__

// Replaces src/MSL/stddef.h for the PC build.
//
// MSL hardcodes the GameCube's 32-bit model:
//
//     typedef unsigned int uintptr_t;
//     typedef unsigned long size_t;

typedef unsigned short wchar_t;
typedef __SIZE_TYPE__ size_t;
typedef signed int ssize_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

/// @todo Rename to @c size_t when #size_t is deleted.
typedef unsigned int usize_t;

typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#define offsetof(type, member) __builtin_offsetof(type, member)

#ifndef NULL
#define NULL 0L
#endif

#endif
