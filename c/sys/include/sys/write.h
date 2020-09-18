#ifndef _SYS_WRITE_H_
#define _SYS_WRITE_H_

#include <sys/size_t.h>
#include <sys/ssize_t.h>
#include <sys/syscall.h>

static inline ssize_t write(int fd, const void *buf, size_t count)
{
    return syscall3(SYS_write, fd, (size_t)buf, count);
}

#endif
