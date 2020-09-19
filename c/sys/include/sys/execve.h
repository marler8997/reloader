#ifndef _SYS_EXECVE_H
#define _SYS_EXECVE_H

static inline size_t execve(const char *pathname, char const *const argv[], char const *const envp[])
{
    return syscall3(SYS_execve, (size_t)pathname, (size_t)argv, (size_t)envp);
}

#endif
