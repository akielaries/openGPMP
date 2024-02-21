.globl asm_function
asm_function:
    // Assembly code to add two integers
    // Parameters are passed in registers: a in %edi, b in %esi
    // Result is stored in %eax
    // Load a into %eax
    mov %edi, %eax
    
    // Add b to %eax
    add %esi, %eax
    
    // Add c to %eax
    add %edx, %eax
    
    // Subtract d from %eax
    sub %ecx, %eax
    
    ret // Return

