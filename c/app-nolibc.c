#include <sys/runtime_check.h>
#include <sys/checked_write.h>
#include <sys/exit.h>

#include "reload.h"

unsigned char foopassthru(unsigned char);

#define write_string_literal(fd, lit) checked_write(fd, lit, sizeof(lit)-1)

void write_msg_unsigned(int fd, const char *prefix, unsigned value, const char *suffix)
{
  char msg[100];
  unsigned len = 0;
  len += format_str     (msg + len, prefix);
  len += format_unsigned(msg + len, value);
  len += format_str     (msg + len, suffix);
  return checked_write(fd, msg, len);
}

int main(int argc, char *argv[], char *envp[])
{
  sys_runtime_check();
  checkreload(argc, argv, &envp);
  write_msg_unsigned(1, "example message to print integer 1234: ", 1234, "\n");
  write_msg_unsigned(1, "foopassthru(123) = ", foopassthru(123), "\n");
  write_string_literal(1, "Success");
  return 0;
}
