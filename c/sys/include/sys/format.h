#ifndef _SYS_FORMAT_H_
#define _SYS_FORMAT_H_

#include <sys/size_t.h>

static inline unsigned format_char(char *buf, char c)
{
  buf[0] = c;
  return 1;
}
unsigned format_str(char *buf, const char *s);
unsigned format_size_t(char *buf, size_t x);
static inline unsigned format_unsigned(char *buf, unsigned x)
{
  return format_size_t(buf, x);
}

#endif
