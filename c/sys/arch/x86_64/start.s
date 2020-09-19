        .global _start
        .text
# STACK (Low to High)
# ------------------------------
# RSP  --> | argc              |
# argv --> | argv[0]           |
#          | argv[1]           |
#          | ...               |
#          | argv[argc] (NULL) |
# envp --> | envp[0]           |
#          | envp[1]           |
#          | ...               |
#          | (NULL)            |
_start:
    xor %rbp, %rbp  # zero the frame pointer register
                    # I think this helps backtraces know the call stack is over
    #
    # set argc
    #
    pop %rdi        # RDI(first arg to main) = argc
    #
    # set argv
    #
    mov %rsp, %rsi  # RSI(second arg to main) = argv (pointer to stack)
    #
    # set envp
    #
    mov %rdi, %rdx  # first put the argc count into rdx (where env will go)
    add $1, %rdx    # add 1 to value from argc (handle on NULL pointer after argv)
    shl $3, %rdx    # multiple argc by 8 (get offset of envp)
    add %rsp, %rdx  # offset this value from the current stack pointer
    #
    # prepare stack for main
    #
    add $-8, %rsp   # move stack pointer below argc
    and $0xf8, %spl # align stack pointer on 8-byte boundary
    call main
    #
    # exit syscall
    #
    mov %rax, %rdi  # syscall param 1 = rax (return value of main)
    mov $60, %rax
    syscall
