#ifndef _SYS_CHECKED_WRITE_H
#define _SYS_CHECKED_WRITE_H

#include <sys/size_t.h>

// writes len bytes to fd, on error will attempt to print an
// error to stderr, then exit with an errno or at least non-zero exit code
void checked_write(int fd, const void *buf, size_t len);

#endif
