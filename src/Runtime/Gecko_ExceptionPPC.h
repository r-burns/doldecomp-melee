#ifndef RUNTIME_GECKO_EXCEPTIONPPC_H
#define RUNTIME_GECKO_EXCEPTIONPPC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __eti_init_info {
    void* eti_start;
    void* eti_end;
    void* code_start;
    unsigned long code_size;
} __eti_init_info;

int __register_fragment(__eti_init_info*, char* TOC);
void __unregister_fragment(int fragmentID);

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_GECKO_EXCEPTIONPPC_H
