#include <sys/streq.h>
#include <sys/write.h>

#define write_string_literal(fd, lit) write(fd, lit, sizeof(lit)-1)

static void *alloc(size_t size)
{
  // TODO: not implemented
  return 0;
}

void reload(char *argv[], char *envp[], const char *loader)
{
}

void checkedReload(char *argv[], char **envp[])
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

    reload(argv, *envp, loader);
}
