#include <sys/runtime_check.h>
#include <sys/write.h>
#include <sys/exit.h>

#include "reload.h"

unsigned char foopassthru(unsigned char);

#define write_string_literal(fd, lit) write(fd, lit, sizeof(lit)-1)

size_t write_msg_unsigned(int fd, const char *prefix, unsigned value, const char *suffix)
{
  char msg[100];
  unsigned len = 0;
  len += format_str     (msg + len, prefix);
  len += format_unsigned(msg + len, value);
  len += format_str     (msg + len, suffix);
  return write(fd, msg, len);
}

//int main(int argc, char *argv[])
_Noreturn void _start()
{
  sys_runtime_check();
  write_string_literal(1, "in main\n");
  //checkedReload();
  
  //reloader();
  write_msg_unsigned(1, "example message to print integer 1234: ", 1234, "\n");
  write_msg_unsigned(1, "foopassthru(123) = ", foopassthru(123), "\n");
  write_string_literal(1, "Success");
  exit(0);
}
