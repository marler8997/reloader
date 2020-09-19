#include <sys/format.h>
#include <sys/exit.h>
#include <sys/write.h>
#include <sys/checked_write.h>

void checked_write(int fd, const void *buf, size_t len)
{
  size_t result = write(fd, buf, len);
  if (result != len) {
    // try to write an error
    char msg[100];
    unsigned msg_len = 0;
    msg_len += format_str   (msg + msg_len, "Error: write ");
    msg_len += format_size_t(msg + msg_len, len);
    msg_len += format_str   (msg + msg_len, " bytes failed, ");
    unsigned errno = syscall_errno(result);
    if (errno) {
      msg_len += format_str     (msg + msg_len, "errno=");
      msg_len += format_unsigned(msg + msg_len, errno);
    } else {
      msg_len += format_str     (msg + msg_len, "returned ");
      msg_len += format_size_t  (msg + msg_len, result);
      errno = 5; // EIO
    }
    msg_len += format_char(msg + msg_len, '\n');
    write(2, msg, msg_len);
    exit(errno);
  }
}
