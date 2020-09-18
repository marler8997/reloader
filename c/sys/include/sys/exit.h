#ifndef _SYS_EXIT_H_
#define _SYS_EXIT_H_

#include <sys/syscall.h>

static inline _Noreturn void exit(int code)
{
    syscall1(SYS_exit, code);
    __builtin_unreachable();
}

#endif
