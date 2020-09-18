#ifndef _SYS_RUNTIME_CHECK_H_
#define _SYS_RUNTIME_CHECK_H_

#include <sys/arch.h>
#include <sys/size_t.h>
#include <sys/write.h>
#include <sys/exit.h>
#include <sys/format.h>

#define write_literal(fd, lit) write(fd, lit, sizeof(lit)-1)

static inline void sys_runtime_check()
{
  if (sizeof(size_t) != ARCH_SIZEOF_WORD) {
    char msg[100];
    unsigned len = 0;
    len += format_str     (msg + len, "Error: expected sizeof(size_t) to be ");
    len += format_unsigned(msg + len, ARCH_SIZEOF_WORD);
    len += format_str     (msg + len, " but is ");
    len += format_unsigned(msg + len, sizeof(size_t));
    len += format_char    (msg + len, '\n');
    write(2, msg, len);
    exit(1);
  }
}

#endif
