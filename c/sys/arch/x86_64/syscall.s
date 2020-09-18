        .global asm_syscall0
        .global asm_syscall1
        .global asm_syscall2
        .global asm_syscall3
        .text
_syscall_fix_arg_4:
        mov %rcx, %r10
_syscall:
        syscall
        ret
asm_syscall0:
        mov %rdi,%rax
        jmp _syscall
asm_syscall1:
        mov %rsi,%rax
        jmp _syscall
asm_syscall2:
        mov %rdx,%rax
        jmp _syscall
asm_syscall3:
        mov %rcx,%rax
        jmp _syscall
