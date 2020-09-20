# NOTE: can't get gcc to work, it's generating instructions that require the %fs register, but it's not
#       setup so I'm getting a segfault...not sure how to prevent it from doing that

cc=zig cc
# need -fno-stack-protector to avoid undefined reference to __stack_chk_fail
# TODO: when compiling with gcc, not sure how to get it to omit the .interp section but still work...
#cc=gcc -fno-stack-protector

cc_libfoo_runpath=-Wl,-rpath,$(realpath out),--enable-new-dtags

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
#all_files += out/app-withlibc
all: $(all_files)

nomain_files += sys/arch/x86_64/syscall.s
nomain_files += sys/format.c
nomain_files += sys/checked_write.c
out/nomain: out sys/examples/nomain.c $(nomain_files)
	$(cc) -static $(flags) -nolibc -nostartfiles $(sys_cflags) -oout/nomain sys/examples/nomain.c $(nomain_files)

argv_example_files += sys/arch/x86_64/syscall.s
argv_example_files += sys/arch/x86_64/start.s
argv_example_files += sys/format.c
argv_example_files += sys/stringlen.c
argv_example_files += sys/checked_write.c
out/argv-example: out sys/examples/argv-example.c $(argv_example_files)
	$(cc) -static $(flags) -nolibc -nostartfiles $(sys_cflags) -oout/argv-example sys/examples/argv-example.c $(argv_example_files)

reload_files += sys/streq.c
reload_files += sys/stringlen.c
reload_files += sys/format.c
reload_files += sys/arch/x86_64/syscall.s
reload_files += sys/checked_write.c
reload_files += reload.c

out/app-nolibc: out app-nolibc.c out/libfoo.so.0
	$(cc) -o$@ $(flags) $(sys_cflags) $(reloadable_c_ld_flags) $(reload_files) $(cc_libfoo_runpath) -Lout -lfoo app-nolibc.c -nolibc -nostartfiles sys/arch/x86_64/start.s

out/app-withlibc: out app-withlibc.c out/libfoo.so.0
	$(cc) -nostartfiles -o$@ $(flags) $(sys_cflags) $(reloadable_c_ld_flags) $(reload_files) -Lout -lfoo app-withlibc.c -nostartfiles $(app_withlibc_files)
	# Not sure how to get the linker not to include the ELF interpreter section when using libc
	#objcopy --remove-section .interp out/app-withlibc

out/o/reload.o: out/o reload.c
	$(cc) -nostdlib -c -oout/o/reload.o reload.c

out/libfoo.so.0 out/libfoo.so: out out/o/foo.o
	$(cc) -shared -o out/libfoo.so.0 -Wl,-soname,libfoo.so.0 out/o/foo.o
	ln -sf libfoo.so.0 out/libfoo.so

out/o/foo.o: out/o foo.c
	$(cc) -c -oout/o/foo.o foo.c

out/o: out
	mkdir -p out/o

out:
	mkdir -p out

clean:
	rm -rf out
