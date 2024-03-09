.globl asm_function
asm_function:

    // a + b + c - d - e + f + g - h
    // Parameters are passed in registers: a in %rdi, b in %rsi
    // Result is stored in %rax
    // Load a into %rax
    mov %rdi, %rax
    
    // Add b to %rax
    add %rsi, %rax
    
    // Add c to %rax
    add %rdx, %rax
    
    // Subtract d from %rax
    sub %rcx, %rax

    // subtract e from %rax
    sub %r8, %rax
    
    ret // Return

