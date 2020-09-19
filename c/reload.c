#include <sys/exit.h>
#include <sys/stringlen.h>
#include <sys/streq.h>
#include <sys/format.h>
#include <sys/mmap.h>
#include <sys/write.h>
#include <sys/checked_write.h>

#define write_string_literal(fd, lit) checked_write(fd, lit, sizeof(lit)-1)

// exits and esures code will be non-zero
_Noreturn void exit_non_zero(unsigned char c)
{
  exit(c ? c : 0xff);
}

static void *alloc(size_t size)
{
  size_t addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  {
    const unsigned errno = syscall_errno(addr);
    if (errno) {
      char msg[100];
      unsigned msg_len = 0;
      msg_len += format_str     (msg+msg_len, "Error: mmap ");
      msg_len += format_size_t  (msg+msg_len, size);
      msg_len += format_str     (msg+msg_len, " failed, errno=");
      msg_len += format_unsigned(msg+msg_len, errno);
      msg_len += format_char    (msg+msg_len, '\n');
      write(2, msg, msg_len);
      exit_non_zero((unsigned char)errno);
    }
  }
  return (void*)addr;
}

_Noreturn void reload(int argc, char *argv[], char *envp[], const char *loader)
{
    write_string_literal(1, "RELOADER: reloading with this loader: ");
    checked_write(1, loader, stringlen(loader));
    checked_write(1, "\n", 1);

    //need to allocate a new argv
    const char **new_argc = alloc(sizeof(char*) * (argc + 2));

    write_string_literal(1, "RELOADER: not fully implemented");
    exit(1);
}

void checkreload(int argc, char *argv[], char **envp[])
{
    write_string_literal(2, "RELOADER: called\n");

    // TODO: need a way to check if we have already been reloaded
    //       there is probably a way to check this by inspecting the dll function addresses
    //       but for now I'm just going to use an environment variable as a proof of concept
    if (streq((*envp)[0], "__RELOADED__=1")) {
      // remove __RELOADED__=1 environment variable
      *envp = (*envp) + 1;
      return;
    }

    // just hardcode the loader for now
    const char *loader = "/nix/store/xg6ilb9g9zhi2zg1dpi4zcp288rhnvns-glibc-2.30/lib/ld-linux-x86-64.so.2";

    reload(argc, argv, *envp, loader);
}
