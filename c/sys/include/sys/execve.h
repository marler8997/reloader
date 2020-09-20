#ifndef _SYS_EXECVE_H
#define _SYS_EXECVE_H

// can't use 'execve' because this signature conflicts with the builtin definition
static inline size_t sys_execve(const char *pathname, char const *const argv[], char const *const envp[])
{
    return syscall3(SYS_execve, (size_t)pathname, (size_t)argv, (size_t)envp);
}

#endif
