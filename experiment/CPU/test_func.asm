section .data
    hello: db 'test-message', 10, 11
    helloLen: equ $-hello

section .text
    GLOBAL test_func

test_func:
    ; - syscall : sys_write
    ; - eax     : Extented Accumulator (32-bits, rax = 64-bits)
    ;             X = H or L , 8 bit registers, High-Order or Low-Order bytes
    mov rax, 4      ; puts sys_swite in eax accumulator register
    ; - ebx     : Extended Base
    ;   - used as callee-saved register or base pointer
    mov rbx, 1      ; puts sys_exit in ebx base register
    mov rcx, hello
    mov rdx, helloLen
    ; interrupt
    int 80h
    ; return control
    ret
    
