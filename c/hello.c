#include <sys/write.h>
#include <sys/exit.h>
#include <sys/format.h>

#define MSG "Hello!\n"

_Noreturn void _start()
{
  // NOTE: set fd and len to invalid values to test error handling
  size_t written = write(1, MSG, sizeof(MSG) - 1);
  if (written != sizeof(MSG)-1) {
    char msg[100];
    unsigned len = 0;
    len += format_str(msg + len, "write failed, ");
    unsigned errno = syscall_errno(written);
    if (errno) {
      len += format_str     (msg + len, "errno=");
      len += format_unsigned(msg + len, errno);
    } else {
      len += format_str     (msg + len, "returned ");
      len += format_size_t  (msg + len, written);
      len += format_str     (msg + len, " but expected ");
      len += format_unsigned(msg + len, sizeof(MSG)-1);
    }
    len += format_char    (msg + len, '\n');
    write(2, msg, len);
    exit(written);
  }
  exit(0);
}
