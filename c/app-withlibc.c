#include <stdio.h>
#include "reload.h"

unsigned char foopassthru(unsigned char);

int main(int argc, char *argv[], char *envp[])
{
  checkreload(argc, argv, &envp);
  printf("foopassthru(123) = %u\n", foopassthru(123));
  printf("Success\n");
}
