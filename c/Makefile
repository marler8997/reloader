flags += -g
#flags += -flto
#flags += -fno-extern-tls-init
#flags += -fno-pie
#flags += -no-pie

# flags to compile against the sys library
sys_cflags += "-Isys/include"
sys_cflags += "-DSYS_ARCH_X86_64"


all_files += out/hello
all_files += out/static-app
all_files += out/dynamic-app
all: $(all_files)

hello_files += sys/arch/x86_64/syscall.s
hello_files += sys/format.c
# NOTE: can't get gcc to work, it's generating instructions that require the %fs register, but it's not
#       setup so I'm getting a segfault...not sure how to prevent it from doing that
out/hello: out hello.c $(hello_files)
	zig cc -static $(flags) -nostdlib $(sys_cflags) -oout/hello hello.c $(hello_files)

app_files += sys/arch/x86_64/syscall.s
app_files += sys/format.c
app_files += sys/streq.c
app_files += reload.c
out/static-app: out app.c $(app_files) out/o/foo.o
	zig cc $(flags) -nostdlib $(sys_cflags) app.c $(app_files) -oout/static-app -static out/o/foo.o

out/dynamic-app: out app.c out/libfoo.so
	zig cc $(flags) -nostdlib $(sys_cflags) app.c $(app_files) -oout/dynamic-app -Lout -lfoo

out/o/reload.o: out/o reload.c
	zig cc -nostdlib -c -oout/o/reload.o reload.c

out/libfoo.so: out out/o/foo.o
	zig cc -shared -o out/libfoo.so out/o/foo.o

out/o/foo.o: out/o foo.c
	zig cc -c -oout/o/foo.o foo.c

out/o: out
	mkdir -p out/o

out:
	mkdir -p out

clean:
	rm -rf out
