#ifndef _STDARG_H_
#define _STDARG_H_

// Replaces src/MSL/stdarg.h

typedef __builtin_va_list va_list;
typedef __builtin_va_list __va_list;

#define va_start(ap, fmt) __builtin_va_start(ap, fmt)
#define va_arg(ap, t) __builtin_va_arg(ap, t)
// Deliberately does not evaluate `ap`, matching MSL
#define va_end(ap) ((void) 0)
#define va_copy(dst, src) __builtin_va_copy(dst, src)

// Some sources (src/melee/ef/efalt.c) bypass va_arg and use MSL's internals
// directly, as `*(t*) __va_arg(list, _var_arg_typeof(t))`. 
// See melee_compat/src/varargs.c for the limits of this
#ifndef _var_arg_typeof
#define _var_arg_typeof(e) 0
#endif

void* __va_arg(va_list v_list, unsigned char type);

#endif
