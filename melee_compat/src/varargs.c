// MSL's __va_arg for x86-64.
//
// mwcc's varargs walk a PowerPC gpr/fpr/save-area struct, and __va_arg returns
// a pointer *into* it -- which is why callers write
// `*(t*) __va_arg(list, ...)`. There is no general way to reproduce that on
// x86-64, where the argument may live in either the register save area or the
// overflow area depending on its class.
//
// Every current caller (src/melee/ef/efalt.c) fetches a pointer, so this
// handles pointer-sized arguments only: it pulls the next one with the real
// builtin and hands back the address of a slot holding it.

#include <stdarg.h>

static void* slot;

void* __va_arg(va_list v_list, unsigned char type)
{
    (void) type;
    slot = __builtin_va_arg(v_list, void*);
    return &slot;
}
