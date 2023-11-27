section .text
global matrix_multiply

matrix_multiply:
    ; Input:
    ;   rdi: pointer to matrix A
    ;   rsi: pointer to matrix B
    ;   rdx: pointer to matrix C (result)
    ;   rcx: matrix dimensions (rows of A, columns of B, columns of C)
    ; Output:
    ;   Matrix C is updated with the result

    mov     r8, rcx        ; r8 = dimension
    xor     r9, r9         ; r9 = i

outer_loop:
    xor     r10, r10       ; r10 = j
inner_loop:
    movsd   xmm0, [rdi + r9 * r8 * 8 + r10 * 8] ; load A[i][j] into xmm0
    mov     r11, r10
    imul    r11, r8        ; r11 = j * dimension
    add     r11, r9        ; r11 = i + j * dimension
    imul    r11, 8         ; r11 = (i + j * dimension) * sizeof(double)
    movsd   xmm1, [rsi + r11] ; load B[j][i] into xmm1 (transposed access)
    mulsd   xmm0, xmm1     ; multiply A[i][j] by B[j][i]
    addsd   xmm0, [rdx + r9 * r8 * 8 + r10 * 8] ; add the result to C[i][j]
    movsd   [rdx + r9 * r8 * 8 + r10 * 8], xmm0 ; store the result back in C[i][j]

    inc     r10
    cmp     r10, r8
    jl      inner_loop

inc     r9
cmp     r9, r8
jl      outer_loop

    ret

