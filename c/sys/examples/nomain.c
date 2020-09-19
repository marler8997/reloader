#include <sys/checked_write.h>
#include <sys/exit.h>

#define MSG "Success!\n"

_Noreturn void _start()
{
  // NOTE: set fd to an bad value to test error messages
  checked_write(1, MSG, sizeof(MSG) - 1);
  exit(0);
}
