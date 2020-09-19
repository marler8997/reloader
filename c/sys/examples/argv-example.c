#include <sys/stringlen.h>
#include <sys/format.h>
#include <sys/checked_write.h>

int main(int argc, char *argv[], char *envp[])
{
  {
    char msg[100];
    unsigned len = 0;
    len += format_str   (msg + len, "argc is ");
    len += format_size_t(msg + len, argc);
    len += format_str   (msg + len, "\n");
    checked_write(1, msg, len);
  }
  for (int i = 0; i < argc; i++) {
    char msg[100];
    unsigned len = 0;
    len += format_unsigned(msg + len, i);
    len += format_str     (msg + len, ": ");
    checked_write(1, msg, len);
    checked_write(1, argv[i], stringlen(argv[i]));
    msg[0] = '\n';
    checked_write(1, msg, 1);
  }
  for (char **next = envp; ; next++) {
    char *env = *next;
    if (!env) break;
    checked_write(1, env, stringlen(env));
    char msg[1] = {'\n'};
    checked_write(1, &msg, 1);
  }
  return 0;
}
