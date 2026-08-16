#ifndef MELEE_COMPAT_CTYPE_H
#define MELEE_COMPAT_CTYPE_H

// Replaces src/MSL/ctype.h for the PC build.
//
// MSL defines these as plain `inline`. mwcc emits that as a single shared
// definition, but under -fgnu89-inline (which this build needs, so that the
// tree's other header helpers get out-of-line definitions the way mwcc emits
// them) clang emits a *strong external* definition in every translation unit,
// giving 911 copies of each and a multiple-definition link failure.
//
// `static inline` gives every TU its own internal copy instead, which is what
// was intended. This header deliberately does not chain to MSL's.

// MSL implements these against its own __ctype_map table, which lives in
// src/MSL/ctype.c -- a file the PC build does not compile. These are the same
// classifications for the 7-bit range the game actually uses.

#define EOF -1L

static inline int isdigit(int c) { return c >= '0' && c <= '9'; }
static inline int isupper(int c) { return c >= 'A' && c <= 'Z'; }
static inline int islower(int c) { return c >= 'a' && c <= 'z'; }
static inline int isalpha(int c) { return isupper(c) || islower(c); }
static inline int isspace(int c)
{
    return c == ' ' || (c >= '\t' && c <= '\r');
}
static inline int isxdigit(int c)
{
    return isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

int toupper(int c);
int tolower(int c);

#endif
