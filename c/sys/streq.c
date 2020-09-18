#include <sys/streq.h>

int streq(const char *a, const char *b)
{
  for (;;a++,b++) {
    if (a[0] != b[0])
      return 0;
    if (a[0] == 0)
      return 1;
  }
}
