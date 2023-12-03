.section .text
.globl matrix_addition

matrix_addition:
    movq    %rdi, %r8         // r8 = pointer to matrix A
    movq    %rsi, %r9         // r9 = pointer to matrix B
    movq    %rdx, %rdi        // rdi = pointer to result matrix C
    movq    %rcx, %r10        // r10 = matrixSize

    // Loop through the matrices
row_loop:
    mov     %r10, %rcx        // Set column counter for each row
col_loop:
    movaps  (%r8), %xmm0      // Load 4 floats from A
    addps   (%r9), %xmm0      // Add 4 floats from B
    movaps  %xmm0, (%rdi)     // Store the result in C

    add     $16, %r8          // Move to the next column in A (4 floats = 16 bytes)
    add     $16, %r9          // Move to the next column in B
    add     $16, %rdi         // Move to the next column in C

    sub     $4, %rcx          // Decrement the column counter
    jnz     col_loop          // Jump if not zero

    add     $16, %r8          // Skip to the next row in A
    add     $16, %r9          // Skip to the next row in B
    add     $16, %rdi         // Skip to the next row in C

    sub     $1, %r10          // Decrement the row counter
    jnz     row_loop          // Jump if not zero

    ret

