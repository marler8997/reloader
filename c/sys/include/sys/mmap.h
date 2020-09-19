#ifndef _SYS_MMAP_H_
#define _SYS_MMAP_H_

#define PROT_READ  0x01
#define PROT_WRITE 0x02

#define MAP_PRIVATE   0x02
#define MAP_ANONYMOUS 0x20

static inline size_t mmap(void *addr, size_t len, unsigned prot, unsigned flags, int fd, size_t offset)
{
  return syscall6(SYS_mmap, (size_t)addr, len, prot, flags, fd, offset);
}

#endif
