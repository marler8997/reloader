flags += -g
#flags += -flto
#flags += -fno-extern-tls-init
#flags += -fno-pie
#flags += -no-pie

# TODO: not sure if I want this or not
#reloadable_c_ld_flags += -fPIE

# flags to compile against the sys library
sys_cflags += "-Isys/include"
sys_cflags += "-DSYS_ARCH_X86_64"

all_files += out/nomain
all_files += out/argv-example
all_files += out/app-nolibc
all_files += out/app-withlibc
all: $(all_files)

nomain_files += sys/arch/x86_64/syscall.s
nomain_files += sys/format.c
nomain_files += sys/checked_write.c
# NOTE: can't get gcc to work, it's generating instructions that require the %fs register, but it's not
#       setup so I'm getting a segfault...not sure how to prevent it from doing that
out/nomain: out sys/examples/nomain.c $(nomain_files)
	zig cc -static $(flags) -nostdlib $(sys_cflags) -oout/nomain sys/examples/nomain.c $(nomain_files)

argv_example_files += sys/arch/x86_64/syscall.s
argv_example_files += sys/arch/x86_64/start.s
argv_example_files += sys/format.c
argv_example_files += sys/stringlen.c
argv_example_files += sys/checked_write.c
out/argv-example: out sys/examples/argv-example.c $(argv_example_files)
	zig cc -static $(flags) -nostdlib $(sys_cflags) -oout/argv-example sys/examples/argv-example.c $(argv_example_files)

# for now, libfoo.so.0 should be in the same directory as exe
libfoo_runpath += -Wl,-rpath,.

reload_files += sys/streq.c
reload_files += sys/stringlen.c
reload_files += sys/format.c
reload_files += sys/arch/x86_64/syscall.s
reload_files += sys/checked_write.c
reload_files += reload.c

out/app-nolibc: out app-nolibc.c out/libfoo.so.0
	zig cc $(flags) -nostdlib $(sys_cflags) $(reloadable_c_ld_flags) $(reload_files) sys/arch/x86_64/start.s app-nolibc.c -oout/app-nolibc $(libfoo_runpath) -Lout -lfoo

out/app-withlibc: out app-withlibc.c out/libfoo.so.0
	zig cc $(flags) $(sys_cflags) $(reloadable_c_ld_flags) $(reload_files) app-withlibc.c $(app_withlibc_files) -oout/app-withlibc $(libfoo_runpath) -Lout -lfoo

out/o/reload.o: out/o reload.c
	zig cc -nostdlib -c -oout/o/reload.o reload.c

out/libfoo.so.0 out/libfoo.so: out out/o/foo.o
	zig cc -shared -o out/libfoo.so.0 out/o/foo.o
	ln -sf libfoo.so.0 out/libfoo.so

out/o/foo.o: out/o foo.c
	zig cc -c -oout/o/foo.o foo.c

out/o: out
	mkdir -p out/o

out:
	mkdir -p out

clean:
	rm -rf out
