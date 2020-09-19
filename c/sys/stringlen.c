#include <sys/stringlen.h>

size_t stringlen(const char *s)
{
  for (size_t i = 0; ; i++) {
    if (s[i] == 0)
      return i;
  }
}
