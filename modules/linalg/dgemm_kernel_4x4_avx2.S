/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

.data
ALPHA_VAR: .double 0.0
BETA_VAR:  .double 0.0
C_VAR:     .quad 0


.text
.globl dgemm_kernel_asm
.type dgemm_kernel_asm, @function

dgemm_kernel_asm:
    
    /***************************************************************************
    * CPP FUNC: 
    * dgemm_kernel_asm(const double *A,
    *                  const double *B,
    *                  double *C,
    *                  const double *nextA,
    *                  const double *nextB,
    *                  long kl,
    *                  long kb,
    *                  long incRowC,
    *                  long incColC,
    *                  double alpha,
    *                  double beta);
    * INPUT PARAMETERS:
    * <--ARGUMENT REGISTERS-->
    * - A       :   %rdi
    * - B       :   %rsi
    * - C       :   %rdx
    * - nextA   :   %rcx
    * - nextB   :   %r8
    * - kl      :   %r9
    * <--STACK-->
    * - kb      :   %rsp + 8
    * - alpha   :   %rsp + 80
    * - beta    :   %rsp + 102
    * - incRowC :   %rsp + 16
    * - incColC :   %rsp + 24
    ***************************************************************************/

    // move addr of A (1st param=rdi register) to rax reg
    movq    %rdi,       %rax

    // move kl to rdi reg
    movq    %r9,        %rdi

    // move addr of B (2nd param=rsi register) to rbx reg
    movq    %rsi,       %rbx

    // move kb to rsi reg
    movq 8(%rsp),      %rsi

    // move addr of nextA (4th param=rcx) to r9 reg
    movq    %rcx,       %r9

    // move addr of nextB (5th param=r8) to r10 reg
    movq    %r8,        %r10


    /***************************************************************************
    * AFTER INITIALIZING PARAMS @ BEGINNING:
    * - A       :   %rax
    * - B       :   %rbx
    * - C       :   %rdx
    * - nextA   :   %r9
    * - nextB   :   %r10
    * - kl      :   %rdi
    * <--STACK-->
    * - kb      :   %rsi
    * - alpha   :   %rsp + 88
    * - beta    :   %rsp + 64
    * - incRowC :   %rsp + 48
    * - incColC :   %rsp + 40
    ***************************************************************************/
    // adjust addresses?
    addq    $256,   %rax
    addq    $256,   %rbx

    // Load data into YMM registers
    // tmp0 = _mm256_load_pd(A)
    vmovapd -256(%rax), %ymm0
    // tmp1 = _mm256_load_pd(A+4)
    vmovapd -224(%rax), %ymm1
    // tmp2 = _mm256_load_pd(B)
    vmovapd -256(%rbx), %ymm2

    // Initialize YMM registers
    // ab_00_11 = _mm256_setzero_pd()
    vxorpd   %ymm8,  %ymm8,  %ymm8
    // ab_20_31 = _mm256_setzero_pd()
    vxorpd   %ymm9,  %ymm9,  %ymm9
    // ab_01_10 = _mm256_setzero_pd()
    vxorpd   %ymm10, %ymm10, %ymm10
    // ab_21_30 = _mm256_setzero_pd()
    vxorpd   %ymm11, %ymm11, %ymm11
    // ab_02_13 = _mm256_setzero_pd()
    vxorpd   %ymm12, %ymm12, %ymm12
    // ab_22_33 = _mm256_setzero_pd()
    vxorpd   %ymm13, %ymm13, %ymm13
    // ab_03_12 = _mm256_setzero_pd()
    vxorpd   %ymm14, %ymm14, %ymm14
    // ab_23_32 = _mm256_setzero_pd()
    vxorpd   %ymm15, %ymm15, %ymm15

    // tmp3 = _mm256_setzero_pd
    vxorpd   %ymm3,  %ymm3,  %ymm3
    // tmp4 = _mm256_setzero_pd
    vxorpd   %ymm4,  %ymm4,  %ymm4
    // tmp5 = _mm256_setzero_pd
    vxorpd   %ymm5,  %ymm5,  %ymm5
    // tmp6 = _mm256_setzero_pd
    vxorpd   %ymm6,  %ymm6,  %ymm6
    // tmp7 = _mm256_setzero_pd
    vxorpd   %ymm7,  %ymm7,  %ymm7

    // if kl==0 writeback to AB
    testq     %rdi,   %rdi    

    // TESTS K1
    // check if kb==0 to handle remaining kl
    testq %rsi, %rsi

    // jump to label .DCONSIDERLEFT if kb is zero
    je .DCONSIDERLEFT

    // Loop label
    .DLOOP:

    // prefetch
    // Prefetch memory location calculated using base address in %rax
    // Prefetching is a technique used to load data into the cache before it 
    // is actually accesses it can help improve performance by reducing the 
    // latency of memory accesses
    prefetcht0 (4*35+1)*8(%rax)

    // *** 1. update

    // ab_02_13 = _mm256_add_pd(ab_02_13, tmp3)
    vaddpd  %ymm3, %ymm12, %ymm12
    // tmp3     = _mm256_load_pd(B+2)
    vmovaps -224(%rbx), %ymm3
    // ab_22_33 = _mm256_add_pd(ab_22_33, tmp6)
    vaddpd  %ymm6, %ymm13, %ymm13
    // tmp6     = tmp2
    vmovaps %ymm2, %ymm6  
    // tmp4     = _mm256_shuffle_pd(tmp2, tmp2, _MM_SHUFFLE2(0, 1))
    vpermilpd  $78, %ymm2, %ymm4
    // Multiply tmp2 by tmp0
    vmulpd  %ymm0, %ymm2, %ymm2
    // Multiply tmp6 by tmp1
    vmulpd  %ymm1, %ymm6, %ymm6
    // Add tmp5 to ab_03_12
    vaddpd  %ymm5, %ymm14, %ymm14
    // Add tmp7 to ab_23_32
    vaddpd  %ymm7, %ymm15, %ymm15
    // Move tmp4 to tmp7
    vmovaps %ymm4, %ymm7
    // Multiply tmp4 by tmp0
    vmulpd  %ymm0, %ymm4, %ymm4
    // Multiply tmp7 by tmp1
    vmulpd  %ymm1, %ymm7, %ymm7
    // Add tmp2 to ab_00_11
    vaddpd  %ymm2, %ymm8, %ymm8
    // Load values from memory (B+4) into tmp2
    vmovaps -96(%rbx), %ymm2
    // Add tmp6 to ab_20_31
    vaddpd  %ymm6, %ymm9, %ymm9
    // Move tmp3 to tmp6
    vmovaps %ymm3, %ymm6
    // Shuffle tmp3 and store result in tmp5
    vpermilpd $78, %ymm3, %ymm5
    // Multiply tmp3 by tmp0
    vmulpd  %ymm0, %ymm3, %ymm3
    // Multiply tmp6 by tmp1
    vmulpd  %ymm1, %ymm6, %ymm6
    // Add tmp4 to ab_01_10
    vaddpd  %ymm4, %ymm10, %ymm10
    // Add tmp7 to ab_21_30
    vaddpd  %ymm7, %ymm11, %ymm11
    // Move tmp5 to tmp7
    vmovaps %ymm5, %ymm7
    // Multiply tmp5 by tmp0
    vmulpd  %ymm0, %ymm5, %ymm5
    // Load values from memory (A+4) into tmp0
    vmovaps -96(%rax), %ymm0
    // Multiply tmp7 by tmp1
    vmulpd  %ymm1, %ymm7, %ymm7
    // Load values from memory (A+6) into tmp1
    vmovaps -80(%rax), %ymm1

    // *** 2. update

    // Add tmp3 to ab_02_13
    addpd %xmm3, %xmm12        // ab_02_13 = _mm_add_pd(ab_02_13, tmp3)

    // Load values from memory (B+6) into tmp3
    movaps -80(%rbx), %xmm3    // tmp3 = _mm_load_pd(B+6)

    // Add tmp6 to ab_22_33
    addpd %xmm6, %xmm13        // ab_22_33 = _mm_add_pd(ab_22_33, tmp6)

    // Move tmp2 to tmp6
    movaps %xmm2, %xmm6        // tmp6 = tmp2

    // Shuffle tmp2 and store result in tmp4
    pshufd $78,%xmm2, %xmm4    // tmp4 = _mm_shuffle_pd(tmp2, tmp2, _MM_SHUFFLE2(0, 1))

    // Multiply tmp2 by tmp0
    mulpd %xmm0, %xmm2         // tmp2 = _mm_mul_pd(tmp2, tmp0);

    // Multiply tmp6 by tmp1
    mulpd %xmm1, %xmm6         // tmp6 = _mm_mul_pd(tmp6, tmp1);

    // Add tmp5 to ab_03_12
    addpd %xmm5, %xmm14        // ab_03_12 = _mm_add_pd(ab_03_12, tmp5)

    // Add tmp7 to ab_23_32
    addpd %xmm7, %xmm15        // ab_23_32 = _mm_add_pd(ab_23_32, tmp7)

    // Move tmp4 to tmp7
    movaps %xmm4, %xmm7        // tmp7 = tmp4

    // Multiply tmp4 by tmp0
    mulpd %xmm0, %xmm4         // tmp4 = _mm_mul_pd(tmp4, tmp0)

    // Multiply tmp7 by tmp1
    mulpd %xmm1, %xmm7         // tmp7 = _mm_mul_pd(tmp7, tmp1)

    // Add tmp2 to ab_00_11
    addpd %xmm2, %xmm8         // ab_00_11 = _mm_add_pd(ab_00_11, tmp2)

    // Load values from memory (B+8) into tmp2
    movaps -64(%rbx), %xmm2    // tmp2 = _mm_load_pd(B+8)

    // Add tmp6 to ab_20_31
    addpd %xmm6, %xmm9         // ab_20_31 = _mm_add_pd(ab_20_31, tmp6)

    // Move tmp3 to tmp6
    movaps %xmm3, %xmm6        // tmp6 = tmp3

    // Shuffle tmp3 and store result in tmp5
    pshufd $78,%xmm3, %xmm5    // tmp5 = _mm_shuffle_pd(tmp3, tmp3, _MM_SHUFFLE2(0, 1))

    // Multiply tmp3 by tmp0
    mulpd %xmm0, %xmm3         // tmp3 = _mm_mul_pd(tmp3, tmp0)

    // Multiply tmp6 by tmp1
    mulpd %xmm1, %xmm6         // tmp6 = _mm_mul_pd(tmp6, tmp1)

    // Add tmp4 to ab_01_10
    addpd %xmm4, %xmm10        // ab_01_10 = _mm_add_pd(ab_01_10, tmp4)

    // Add tmp7 to ab_21_30
    addpd %xmm7, %xmm11        // ab_21_30 = _mm_add_pd(ab_21_30, tmp7)

    // Move tmp5 to tmp7
    movaps %xmm5, %xmm7        // tmp7 = tmp5

    // Multiply tmp5 by tmp0
    mulpd %xmm0, %xmm5         // tmp5 = _mm_mul_pd(tmp5, tmp0)

    // Load values from memory (A+8) into tmp0
    movaps -64(%rax), %xmm0    // tmp0 = _mm_load_pd(A+8)

    // Multiply tmp7 by tmp1
    mulpd %xmm1, %xmm7         // tmp7 = _mm_mul_pd(tmp7, tmp1)

    // Load values from memory (A+10) into tmp1
    movaps -48(%rax), %xmm1    // tmp1 = _mm_load_pd(A+10)

    // Prefetch memory location calculated using base address in %rax
    prefetcht0 (4*37+1)*8(%rax)

    // *** 3. update
    
    // Add tmp3 to ab_02_13
    addpd %xmm3, %xmm12        // ab_02_13 = _mm_add_pd(ab_02_13, tmp3)

    // Load values from memory (B+10) into tmp3
    movaps -48(%rbx), %xmm3    // tmp3 = _mm_load_pd(B+10)

    // Add tmp6 to ab_22_33
    addpd %xmm6, %xmm13        // ab_22_33 = _mm_add_pd(ab_22_33, tmp6)

    // Move tmp2 to tmp6
    movaps %xmm2, %xmm6        // tmp6 = tmp2

    // Shuffle tmp2 and store result in tmp4
    pshufd $78,%xmm2, %xmm4    // tmp4 = _mm_shuffle_pd(tmp2, tmp2, _MM_SHUFFLE2(0, 1))

    // Multiply tmp2 by tmp0
    mulpd %xmm0, %xmm2         // tmp2 = _mm_mul_pd(tmp2, tmp0);

    // Multiply tmp6 by tmp1
    mulpd %xmm1, %xmm6         // tmp6 = _mm_mul_pd(tmp6, tmp1);

    // Add tmp5 to ab_03_12
    addpd %xmm5, %xmm14        // ab_03_12 = _mm_add_pd(ab_03_12, tmp5)

    // Add tmp7 to ab_23_32
    addpd %xmm7, %xmm15        // ab_23_32 = _mm_add_pd(ab_23_32, tmp7)

    // Move tmp4 to tmp7
    movaps %xmm4, %xmm7        // tmp7 = tmp4

    // Multiply tmp4 by tmp0
    mulpd %xmm0, %xmm4         // tmp4 = _mm_mul_pd(tmp4, tmp0)

    // Multiply tmp7 by tmp1
    mulpd %xmm1, %xmm7         // tmp7 = _mm_mul_pd(tmp7, tmp1)

    // Add tmp2 to ab_00_11
    addpd %xmm2, %xmm8         // ab_00_11 = _mm_add_pd(ab_00_11, tmp2)

    // Load values from memory (B+12) into tmp2
    movaps -32(%rbx), %xmm2    // tmp2 = _mm_load_pd(B+12)

    // Add tmp6 to ab_20_31
    addpd %xmm6, %xmm9         // ab_20_31 = _mm_add_pd(ab_20_31, tmp6)

    // Move tmp3 to tmp6
    movaps %xmm3, %xmm6        // tmp6 = tmp3

    // Shuffle tmp3 and store result in tmp5
    pshufd $78,%xmm3, %xmm5    // tmp5 = _mm_shuffle_pd(tmp3, tmp3, _MM_SHUFFLE2(0, 1))

    // Multiply tmp3 by tmp0
    mulpd %xmm0, %xmm3         // tmp3 = _mm_mul_pd(tmp3, tmp0)

    // Multiply tmp6 by tmp1
    mulpd %xmm1, %xmm6         // tmp6 = _mm_mul_pd(tmp6, tmp1)

    // Add tmp4 to ab_01_10
    addpd %xmm4, %xmm10        // ab_01_10 = _mm_add_pd(ab_01_10, tmp4)

    // Add tmp7 to ab_21_30
    addpd %xmm7, %xmm11        // ab_21_30 = _mm_add_pd(ab_21_30, tmp7)

    // Move tmp5 to tmp7
    movaps %xmm5, %xmm7        // tmp7 = tmp5

    // Multiply tmp5 by tmp0
    mulpd %xmm0, %xmm5         // tmp5 = _mm_mul_pd(tmp5, tmp0)

    // Load values from memory (A+12) into tmp0
    movaps -32(%rax), %xmm0    // tmp0 = _mm_load_pd(A+12)

    // Multiply tmp7 by tmp1
    mulpd %xmm1, %xmm7         // tmp7 = _mm_mul_pd(tmp7, tmp1)

    // Load values from memory (A+14) into tmp1
    movaps -16(%rax), %xmm1    // tmp1 = _mm_load_pd(A+14)

    
    // *** 4. update

    // Add tmp3 to ab_02_13
    addpd %xmm3, %xmm12        // ab_02_13 = _mm_add_pd(ab_02_13, tmp3)

    // Load values from memory (B+14) into tmp3
    movaps -16(%rbx), %xmm3    // tmp3 = _mm_load_pd(B+14)

    // Add tmp6 to ab_22_33
    addpd %xmm6, %xmm13        // ab_22_33 = _mm_add_pd(ab_22_33, tmp6)

    // Move tmp2 to tmp6
    movaps %xmm2, %xmm6        // tmp6 = tmp2

    // Shuffle tmp2 and store result in tmp4
    pshufd $78,%xmm2, %xmm4    // tmp4 = _mm_shuffle_pd(tmp2, tmp2, _MM_SHUFFLE2(0, 1))

    // Multiply tmp2 by tmp0
    mulpd %xmm0, %xmm2         // tmp2 = _mm_mul_pd(tmp2, tmp0);

    // Multiply tmp6 by tmp1
    mulpd %xmm1, %xmm6         // tmp6 = _mm_mul_pd(tmp6, tmp1);

    // Adjust pointer A
    subq $-32*4, %rax          // A += 16;

    // Add tmp5 to ab_03_12
    addpd %xmm5, %xmm14        // ab_03_12 = _mm_add_pd(ab_03_12, tmp5)

    // Add tmp7 to ab_23_32
    addpd %xmm7, %xmm15        // ab_23_32 = _mm_add_pd(ab_23_32, tmp7)

    // Move tmp4 to tmp7
    movaps %xmm4, %xmm7        // tmp7 = tmp4

    // Multiply tmp4 by tmp0
    mulpd %xmm0, %xmm4         // tmp4 = _mm_mul_pd(tmp4, tmp0)

    // Multiply tmp7 by tmp1
    mulpd %xmm1, %xmm7         // tmp7 = _mm_mul_pd(tmp7, tmp1)

    // Adjust pointer nextB
    subq $-128, %r10           // nextB += 16

    // Add tmp2 to ab_00_11
    addpd %xmm2, %xmm8         // ab_00_11 = _mm_add_pd(ab_00_11, tmp2)

    // Load values from memory (B+16) into tmp2
    movaps (%rbx),%xmm2        // tmp2 = _mm_load_pd(B+16)

    // Add tmp6 to ab_20_31
    addpd %xmm6, %xmm9         // ab_20_31 = _mm_add_pd(ab_20_31, tmp6)

    // Move tmp3 to tmp6
    movaps %xmm3, %xmm6        // tmp6 = tmp3

    // Shuffle tmp3 and store result in tmp5
    pshufd $78,%xmm3, %xmm5    // tmp5 = _mm_shuffle_pd(tmp3, tmp3, _MM_SHUFFLE2(0, 1))

    // Multiply tmp3 by tmp0
    mulpd %xmm0, %xmm3         // tmp3 = _mm_mul_pd(tmp3, tmp0)

    // Multiply tmp6 by tmp1
    mulpd %xmm1, %xmm6         // tmp6 = _mm_mul_pd(tmp6, tmp1)

    // Adjust pointer B
    subq $-32*4, %rbx          // B += 16;

    // Add tmp4 to ab_01_10
    addpd %xmm4, %xmm10        // ab_01_10 = _mm_add_pd(ab_01_10, tmp4)

    // Add tmp7 to ab_21_30
    addpd %xmm7, %xmm11        // ab_21_30 = _mm_add_pd(ab_21_30, tmp7)

    // Move tmp5 to tmp7
    movaps %xmm5, %xmm7        // tmp7 = tmp5

    // Multiply tmp5 by tmp0
    mulpd %xmm0, %xmm5         // tmp5 = _mm_mul_pd(tmp5, tmp0)

    // Load values from memory (A+16) into tmp0
    movaps -128(%rax),%xmm0    // tmp0 = _mm_load_pd(A+16)

    // Multiply tmp7 by tmp1
    mulpd %xmm1, %xmm7         // tmp7 = _mm_mul_pd(tmp7, tmp1)

    // Load values from memory (A+18) into tmp1
    movaps -112(%rax), %xmm1   // tmp1 = _mm_load_pd(A+18)

    
    // prefetch nextB[0]
    prefetcht2        0(%r10)
    // prefetch nextB[8]
    prefetcht2       64(%r10)

    // --l decrement
    decq      %rsi
    // if l>= 1 go back
    jne       .DLOOP

    // If kl==0, writeback to AB
    .DCONSIDERLEFT:

    testq     %rdi,   %rdi         // if kl==0 writeback to AB
    je        .DPOSTACCUMULATE

    
    // Loop for kl remaining iterations
    .DLOOPLEFT:                   // for l = kl,..,1 do

    addpd     %xmm3,  %xmm12       // ab_02_13 = _mm_add_pd(ab_02_13, tmp3)
    movapd -112(%rbx),%xmm3        // tmp3     = _mm_load_pd(B+2)
    addpd     %xmm6,  %xmm13       // ab_22_33 = _mm_add_pd(ab_22_33, tmp6)
    movapd    %xmm2,  %xmm6        // tmp6     = tmp2
    pshufd $78,%xmm2, %xmm4        // tmp4     = _mm_shuffle_pd(tmp2, tmp2, _MM_SHUFFLE2(0, 1))
    
    mulpd     %xmm0,  %xmm2        // tmp2     = _mm_mul_pd(tmp2, tmp0);
    mulpd     %xmm1,  %xmm6        // tmp6     = _mm_mul_pd(tmp6, tmp1);

    addpd     %xmm5,  %xmm14       // ab_03_12 = _mm_add_pd(ab_03_12, tmp5)
    addpd     %xmm7,  %xmm15       // ab_23_32 = _mm_add_pd(ab_23_32, tmp7)
    movapd    %xmm4,  %xmm7        // tmp7     = tmp4
    mulpd     %xmm0,  %xmm4        // tmp4     = _mm_mul_pd(tmp4, tmp0)
    mulpd     %xmm1,  %xmm7        // tmp7     = _mm_mul_pd(tmp7, tmp1)

    addpd     %xmm2,  %xmm8        // ab_00_11 = _mm_add_pd(ab_00_11, tmp2)
    movapd -96(%rbx), %xmm2        // tmp2     = _mm_load_pd(B+4)
    addpd     %xmm6,  %xmm9        // ab_20_31 = _mm_add_pd(ab_20_31, tmp6)
    movapd    %xmm3,  %xmm6        // tmp6     = tmp3
    pshufd $78,%xmm3, %xmm5        // tmp5     = _mm_shuffle_pd(tmp3, tmp3, _MM_SHUFFLE2(0, 1))

    mulpd     %xmm0,  %xmm3        // tmp3     = _mm_mul_pd(tmp3, tmp0)
    mulpd     %xmm1,  %xmm6        // tmp6     = _mm_mul_pd(tmp6, tmp1)

    addpd     %xmm4,  %xmm10       // ab_01_10 = _mm_add_pd(ab_01_10, tmp4)
    addpd     %xmm7,  %xmm11       // ab_21_30 = _mm_add_pd(ab_21_30, tmp7)
    movapd    %xmm5,  %xmm7        // tmp7     = tmp5
    mulpd     %xmm0,  %xmm5        // tmp5     = _mm_mul_pd(tmp5, tmp0)
    movapd -96(%rax), %xmm0        // tmp0     = _mm_load_pd(A+4)
    mulpd     %xmm1,  %xmm7        // tmp7     = _mm_mul_pd(tmp7, tmp1)
    movapd -80(%rax), %xmm1        // tmp1     = _mm_load_pd(A+6)

    addq      $32,     %rax        // A += 4;
    addq      $32,     %rbx        // B += 4;
 
    
    decq      %rdi                // --l
    jne       .DLOOPLEFT         // if l>= 1 go back

    .DPOSTACCUMULATE:            // Update remaining ab_*_* registers

    addpd    %xmm3,   %xmm12      // ab_02_13 = _mm_add_pd(ab_02_13, tmp3)
    addpd    %xmm6,   %xmm13      // ab_22_33 = _mm_add_pd(ab_22_33, tmp6)

    addpd    %xmm5,   %xmm14      // ab_03_12 = _mm_add_pd(ab_03_12, tmp5)
    addpd    %xmm7,   %xmm15      // ab_23_32 = _mm_add_pd(ab_23_32, tmp7)

    //  Update C <- beta*C + alpha*AB

    //movsd  4,                     %xmm0  // load alpha
    //movsd  88(%rsp),                %xmm0  // load alpha
    // THIS WORKS IN NON-OOP ENV
    //movsd   88(%rsp),               %xmm0
    movsd   80(%rsp),               %xmm0
    
    //movsd  5,                     %xmm1  // load beta
    //movsd  64(%rsp),                %xmm1  // load beta
    movsd   102(%rsp),               %xmm1

    //movq   6,                     %rcx   // Address of C stored in %rcx
    //movq    56(%rsp),                %rcx   // Address of C stored in %rcx

    // move 3rd param (C) into rcx register
    movq    %rdx,                   %rcx

    //movq   7,                     %r8    // load incRowC
    movq   16(%rsp),                %r8    // load incRowC
    // movq x(%rsp),                %r8

    leaq   (,%r8,8),                %r8    // incRowC *= sizeof(double)

    //movq   8,                     %r9    // load incColC
    movq   24(%rsp),                %r9    // load incColC
    // movq x(%rsp),                %r9

    leaq   (,%r9,8),                %r9    // incRowC *= sizeof(double)

    leaq    (%rcx,%r9),          %r10  // Store addr of C01 in %r10
    leaq    (%rcx,%r8,2),        %rdx  // Store addr of C20 in %rdx
    leaq    (%rdx,%r9),          %r11  // Store addr of C21 in %r11

    unpcklpd %xmm0,               %xmm0 // duplicate alpha
    unpcklpd %xmm1,               %xmm1 // duplicate beta

    movlpd  (%rcx),               %xmm3 // load (C00,
    movhpd  (%r10,%r8),          %xmm3 //       C11)
    mulpd   %xmm0,               %xmm8 // scale ab_00_11 by alpha
    mulpd   %xmm1,               %xmm3 // scale (C00, C11) by beta
    addpd   %xmm8,               %xmm3 // add results

    movlpd  %xmm3,               (%rcx) // write back (C00,
    movhpd  %xmm3,               (%r10,%r8) //             C11)

    movlpd  (%rdx),               %xmm4 // load (C20,
    movhpd  (%r11,%r8),          %xmm4 //       C31)
    mulpd   %xmm0,               %xmm9 // scale ab_20_31 by alpha
    mulpd   %xmm1,               %xmm4 // scale (C20, C31) by beta
    addpd   %xmm9,               %xmm4 // add results
    movlpd  %xmm4,               (%rdx) // write back (C20,
    movhpd  %xmm4,               (%r11,%r8) //             C31)

    movlpd  (%r10),               %xmm3 // load (C01,
    movhpd  (%rcx,%r8),          %xmm3 //       C10)
    mulpd   %xmm0,               %xmm10 // scale ab_01_10 by alpha
    mulpd   %xmm1,               %xmm3  // scale (C01, C10) by beta
    addpd   %xmm10,              %xmm3  // add results
    movlpd  %xmm3,               (%r10) // write back (C01,
    movhpd  %xmm3,               (%rcx,%r8) //             C10)

    movlpd  (%r11),               %xmm4 // load (C21,
    movhpd  (%rdx,%r8),          %xmm4 //       C30)
    mulpd   %xmm0,               %xmm11 // scale ab_21_30 by alpha
    mulpd   %xmm1,               %xmm4  // scale (C21, C30) by beta
    addpd   %xmm11,              %xmm4  // add results
    movlpd  %xmm4,               (%r11) // write back (C21,
    movhpd  %xmm4,               (%rdx,%r8) //             C30)
        
    leaq    (%rcx,%r9,2),      %rcx  // Store addr of C02 in %rcx
    leaq    (%r10,%r9,2),      %r10  // Store addr of C03 in %r10
    leaq    (%rdx,%r9,2),      %rdx  // Store addr of C22 in $rdx
    leaq    (%r11,%r9,2),      %r11  // Store addr of C23 in %r11

    movlpd  (%rcx),             %xmm3 // load (C02,
    movhpd  (%r10,%r8),        %xmm3 //       C13)
    mulpd   %xmm0,              %xmm12 // scale ab_02_13 by alpha
    mulpd   %xmm1,              %xmm3  // scale (C02, C13) by beta
    addpd   %xmm12,             %xmm3  // add results
    movlpd  %xmm3,        (%rcx)       // write back (C02,
    movhpd  %xmm3,        (%r10,%r8)  //             C13)

    movlpd  (%rdx),             %xmm4 // load (C22,
    movhpd  (%r11,%r8),        %xmm4 //       C33)
    mulpd   %xmm0,              %xmm13 // scale ab_22_33 by alpha
    mulpd   %xmm1,              %xmm4  // scale (C22, C33) by beta
    addpd   %xmm13,             %xmm4  // add results
    movlpd  %xmm4,              (%rdx) // write back (C22,
    movhpd  %xmm4,        (%r11,%r8) //             C33)

    movlpd  (%r10),             %xmm3 // load (C03,
    movhpd  (%rcx,%r8),        %xmm3 //       C12)
    mulpd   %xmm0,              %xmm14 // scale ab_03_12 by alpha
    mulpd   %xmm1,              %xmm3  // scale (C03, C12) by beta
    addpd   %xmm14,             %xmm3  // add results
    movlpd  %xmm3,        (%r10)      // write back (C03,
    movhpd  %xmm3,        (%rcx,%r8) //             C12)

    movlpd  (%r11),             %xmm4 // load (C23,
    movhpd  (%rdx,%r8),        %xmm4 //       C32)
    mulpd   %xmm0,              %xmm15 // scale ab_23_32 by alpha
    mulpd   %xmm1,              %xmm4  // scale (C23, C32) by beta
    addpd   %xmm15,             %xmm4  // add results
    movlpd  %xmm4,        (%r11)      // write back (C23,
    movhpd  %xmm4,        (%rdx,%r8) //             C32)

    # specify the input and output operands
    # input
    #.section .rodata
    #.align 8

    // return
    ret


