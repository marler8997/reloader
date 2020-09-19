        .global asm_syscall0
        .global asm_syscall1
        .global asm_syscall2
        .global asm_syscall3
        .global asm_syscall4
        .global asm_syscall5
        .global asm_syscall6
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
asm_syscall4:
        mov %r8,%rax
        jmp _syscall_fix_arg_4
asm_syscall5:
        mov %r9,%rax
        jmp _syscall_fix_arg_4
asm_syscall6:
        mov 8(%rsp),%rax
        jmp _syscall_fix_arg_4
