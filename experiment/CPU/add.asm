
section .data
    ; call printf from C stdio.h
    msg db "Sum is: %d", 10, 0 
    n1 dd 10
    n2 dd 20

section .text
    global _start

_start: 
    ; load n1 into eax
    mov eax, [n1]
    ; add n2 to eax
    add eax, [n2]

    ;<-- print sum -->
    ; push sum -> stack
    push eax
    ; push msg -> stack
    push dword msg
    ; call printf
    call printf
    ; clear stack
    add esp, 8 ; how?

    ;<-- EXIT PROGRAM -->
    ; syscall for exit
    mov eax, 1
    ; exit 0
    xor ebx, ebx
    ; kernel call
    int 0x80
    

