#ifndef _SYS_ARCH_SYSCALL_H_
#define _SYS_ARCH_SYSCALL_H_

#ifdef SYS_ARCH_X86_64
    #include <sys/arch/x86_64/syscallnums.h>
#else
    #error SYS_ARCH_* is not defined
#endif


#endif
