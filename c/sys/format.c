#include <sys/format.h>

unsigned format_str(char *buf, const char *s)
{
  for (unsigned i = 0; ; i++) {
    const char c = s[i];
    if (c == 0)
      return i;
    buf[i] = c;
  }
}

static void reverse(char *x, unsigned len)
{
  for (unsigned i = 0; i < len/2; i++) {
    char tmp = x[i];
    x[i] = x[len-i-1];
    x[len-i-1] = tmp;
  }
}

unsigned format_size_t(char *buf, size_t x)
{
  unsigned i = 0;
  do {
    buf[i++] = '0' + (x % 10);
    x /= 10;
  } while (x != 0);
  reverse(buf, i);
  return i;
}
