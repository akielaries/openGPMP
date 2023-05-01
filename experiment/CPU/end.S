.globl _start

_start:
    movq $60, %rax
    movq $2, %rdi
    syscall

