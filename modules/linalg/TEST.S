	.file	"dgemm_nn.c"
	.text
.Ltext0:
	.file 0 "/home/akiel/Desktop/trunk/github/pub/openGPMP/modules/linalg" "dgemm_nn.c"
	.local	_A
	.comm	_A,1179648,16
	.local	_B
	.comm	_B,12582912,16
	.local	_C
	.comm	_C,128,16
	.type	pack_MRxk, @function
pack_MRxk:
.LFB4865:
	.file 1 "dgemm_nn.c"
	.loc 1 40 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movl	%ecx, -36(%rbp)
	movq	%r8, -48(%rbp)
	.loc 1 43 11
	movl	$0, -8(%rbp)
	.loc 1 43 5
	jmp	.L2
.L5:
	.loc 1 44 15
	movl	$0, -4(%rbp)
	.loc 1 44 9
	jmp	.L3
.L4:
	.loc 1 45 28
	movl	-4(%rbp), %eax
	imull	-24(%rbp), %eax
	cltq
	.loc 1 45 26
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	.loc 1 45 19
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	.loc 1 45 26
	movsd	(%rdx), %xmm0
	.loc 1 45 23
	movsd	%xmm0, (%rax)
	.loc 1 44 25 discriminator 3
	addl	$1, -4(%rbp)
.L3:
	.loc 1 44 20 discriminator 1
	cmpl	$3, -4(%rbp)
	jle	.L4
	.loc 1 47 16
	addq	$32, -48(%rbp)
	.loc 1 48 16
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rax, -32(%rbp)
	.loc 1 43 20 discriminator 2
	addl	$1, -8(%rbp)
.L2:
	.loc 1 43 16 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L5
	.loc 1 50 1
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4865:
	.size	pack_MRxk, .-pack_MRxk
	.type	pack_A, @function
pack_A:
.LFB4866:
	.loc 1 58 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	%r8d, -40(%rbp)
	movq	%r9, -48(%rbp)
	.loc 1 59 9
	movl	-20(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -12(%rbp)
	.loc 1 60 9
	movl	-20(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, -16(%rbp)
	.loc 1 64 11
	movl	$0, -4(%rbp)
	.loc 1 64 5
	jmp	.L7
.L8:
	.loc 1 65 9
	movq	-48(%rbp), %rdi
	movl	-40(%rbp), %ecx
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rsi
	movl	-24(%rbp), %eax
	movq	%rdi, %r8
	movl	%eax, %edi
	call	pack_MRxk
	.loc 1 66 21
	movl	-24(%rbp), %eax
	sall	$2, %eax
	cltq
	.loc 1 66 16
	salq	$3, %rax
	addq	%rax, -48(%rbp)
	.loc 1 67 21
	movl	-36(%rbp), %eax
	sall	$2, %eax
	cltq
	.loc 1 67 16
	salq	$3, %rax
	addq	%rax, -32(%rbp)
	.loc 1 64 21 discriminator 3
	addl	$1, -4(%rbp)
.L7:
	.loc 1 64 16 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L8
	.loc 1 69 8
	cmpl	$0, -16(%rbp)
	jle	.L16
	.loc 1 70 15
	movl	$0, -8(%rbp)
	.loc 1 70 9
	jmp	.L10
.L15:
	.loc 1 71 19
	movl	$0, -4(%rbp)
	.loc 1 71 13
	jmp	.L11
.L12:
	.loc 1 72 32
	movl	-4(%rbp), %eax
	imull	-36(%rbp), %eax
	cltq
	.loc 1 72 30
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	.loc 1 72 23
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	.loc 1 72 30
	movsd	(%rdx), %xmm0
	.loc 1 72 27
	movsd	%xmm0, (%rax)
	.loc 1 71 30 discriminator 3
	addl	$1, -4(%rbp)
.L11:
	.loc 1 71 24 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L12
	.loc 1 74 19
	movl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
	.loc 1 74 13
	jmp	.L13
.L14:
	.loc 1 75 23
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 75 27
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 74 31 discriminator 3
	addl	$1, -4(%rbp)
.L13:
	.loc 1 74 26 discriminator 1
	cmpl	$3, -4(%rbp)
	jle	.L14
	.loc 1 77 20
	addq	$32, -48(%rbp)
	.loc 1 78 20
	movl	-40(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rax, -32(%rbp)
	.loc 1 70 25 discriminator 2
	addl	$1, -8(%rbp)
.L10:
	.loc 1 70 20 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L15
.L16:
	.loc 1 81 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4866:
	.size	pack_A, .-pack_A
	.type	pack_kxNR, @function
pack_kxNR:
.LFB4867:
	.loc 1 89 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movl	%ecx, -36(%rbp)
	movq	%r8, -48(%rbp)
	.loc 1 92 11
	movl	$0, -4(%rbp)
	.loc 1 92 5
	jmp	.L18
.L21:
	.loc 1 93 15
	movl	$0, -8(%rbp)
	.loc 1 93 9
	jmp	.L19
.L20:
	.loc 1 94 28
	movl	-8(%rbp), %eax
	imull	-36(%rbp), %eax
	cltq
	.loc 1 94 26
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	.loc 1 94 19
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	.loc 1 94 26
	movsd	(%rdx), %xmm0
	.loc 1 94 23
	movsd	%xmm0, (%rax)
	.loc 1 93 25 discriminator 3
	addl	$1, -8(%rbp)
.L19:
	.loc 1 93 20 discriminator 1
	cmpl	$3, -8(%rbp)
	jle	.L20
	.loc 1 96 16
	addq	$32, -48(%rbp)
	.loc 1 97 16
	movl	-24(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rax, -32(%rbp)
	.loc 1 92 20 discriminator 2
	addl	$1, -4(%rbp)
.L18:
	.loc 1 92 16 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L21
	.loc 1 99 1
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4867:
	.size	pack_kxNR, .-pack_kxNR
	.type	pack_B, @function
pack_B:
.LFB4868:
	.loc 1 107 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	%r8d, -40(%rbp)
	movq	%r9, -48(%rbp)
	.loc 1 108 9
	movl	-24(%rbp), %eax
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -12(%rbp)
	.loc 1 109 9
	movl	-24(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, -16(%rbp)
	.loc 1 113 11
	movl	$0, -8(%rbp)
	.loc 1 113 5
	jmp	.L23
.L24:
	.loc 1 114 9
	movq	-48(%rbp), %rdi
	movl	-40(%rbp), %ecx
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rsi
	movl	-20(%rbp), %eax
	movq	%rdi, %r8
	movl	%eax, %edi
	call	pack_kxNR
	.loc 1 115 21
	movl	-20(%rbp), %eax
	sall	$2, %eax
	cltq
	.loc 1 115 16
	salq	$3, %rax
	addq	%rax, -48(%rbp)
	.loc 1 116 21
	movl	-40(%rbp), %eax
	sall	$2, %eax
	cltq
	.loc 1 116 16
	salq	$3, %rax
	addq	%rax, -32(%rbp)
	.loc 1 113 21 discriminator 3
	addl	$1, -8(%rbp)
.L23:
	.loc 1 113 16 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L24
	.loc 1 118 8
	cmpl	$0, -16(%rbp)
	jle	.L32
	.loc 1 119 15
	movl	$0, -4(%rbp)
	.loc 1 119 9
	jmp	.L26
.L31:
	.loc 1 120 19
	movl	$0, -8(%rbp)
	.loc 1 120 13
	jmp	.L27
.L28:
	.loc 1 121 32
	movl	-8(%rbp), %eax
	imull	-40(%rbp), %eax
	cltq
	.loc 1 121 30
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	.loc 1 121 23
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-48(%rbp), %rax
	addq	%rcx, %rax
	.loc 1 121 30
	movsd	(%rdx), %xmm0
	.loc 1 121 27
	movsd	%xmm0, (%rax)
	.loc 1 120 30 discriminator 3
	addl	$1, -8(%rbp)
.L27:
	.loc 1 120 24 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L28
	.loc 1 123 19
	movl	-16(%rbp), %eax
	movl	%eax, -8(%rbp)
	.loc 1 123 13
	jmp	.L29
.L30:
	.loc 1 124 23
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 124 27
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 123 31 discriminator 3
	addl	$1, -8(%rbp)
.L29:
	.loc 1 123 26 discriminator 1
	cmpl	$3, -8(%rbp)
	jle	.L30
	.loc 1 126 20
	addq	$32, -48(%rbp)
	.loc 1 127 20
	movl	-36(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rax, -32(%rbp)
	.loc 1 119 25 discriminator 2
	addl	$1, -4(%rbp)
.L26:
	.loc 1 119 20 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L31
.L32:
	.loc 1 130 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4868:
	.size	pack_B, .-pack_B
	.type	dgemm_micro_kernel, @function
dgemm_micro_kernel:
.LFB4869:
	.loc 1 141 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movq	%rdx, -48(%rbp)
	movsd	%xmm1, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movq	%r8, -72(%rbp)
	movq	%r9, -80(%rbp)
	.loc 1 142 10
	movq	-24(%rbp), %rax
	leaq	3(%rax), %rdx
	testq	%rax, %rax
	cmovs	%rdx, %rax
	sarq	$2, %rax
	movq	%rax, -8(%rbp)
	.loc 1 143 10
	movq	-24(%rbp), %rdx
	movq	%rdx, %rax
	sarq	$63, %rax
	shrq	$62, %rax
	addq	%rax, %rdx
	andl	$3, %edx
	subq	%rax, %rdx
	movq	%rdx, -16(%rbp)
	.loc 1 159 5
	movsd	-56(%rbp), %xmm0
	movq	-32(%rbp), %rdi
	movq	-16(%rbp), %r9
	movq	24(%rbp), %r8
	movq	16(%rbp), %rcx
	movq	-64(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	-40(%rbp), %rax
	subq	$8, %rsp
	pushq	-80(%rbp)
	pushq	-72(%rbp)
	pushq	-8(%rbp)
	movapd	%xmm0, %xmm1
	movq	%rdi, %xmm0
	movq	%rax, %rdi
	call	dgemm_kernel_asm@PLT
	addq	$32, %rsp
	.loc 1 164 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4869:
	.size	dgemm_micro_kernel, .-dgemm_micro_kernel
	.type	dgeaxpy, @function
dgeaxpy:
.LFB4870:
	.loc 1 556 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, -44(%rbp)
	movl	%r8d, -48(%rbp)
	movq	%r9, -56(%rbp)
	.loc 1 560 8
	movsd	.LC1(%rip), %xmm0
	ucomisd	-32(%rbp), %xmm0
	jp	.L46
	movsd	.LC1(%rip), %xmm0
	ucomisd	-32(%rbp), %xmm0
	je	.L35
.L46:
	.loc 1 561 15
	movl	$0, -8(%rbp)
	.loc 1 561 9
	jmp	.L37
.L40:
	.loc 1 562 19
	movl	$0, -4(%rbp)
	.loc 1 562 13
	jmp	.L38
.L39:
	.loc 1 563 18
	movl	-4(%rbp), %eax
	imull	16(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	imull	24(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm1
	.loc 1 563 52
	movl	-4(%rbp), %eax
	imull	-44(%rbp), %eax
	movl	%eax, %edx
	.loc 1 563 62
	movl	-8(%rbp), %eax
	imull	-48(%rbp), %eax
	.loc 1 563 60
	addl	%edx, %eax
	cltq
	.loc 1 563 50
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	.loc 1 563 48
	mulsd	-32(%rbp), %xmm0
	.loc 1 563 18
	movl	-4(%rbp), %eax
	imull	16(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	imull	24(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 563 40
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 562 28 discriminator 3
	addl	$1, -4(%rbp)
.L38:
	.loc 1 562 24 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L39
	.loc 1 561 24 discriminator 2
	addl	$1, -8(%rbp)
.L37:
	.loc 1 561 20 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L40
	.loc 1 573 1
	jmp	.L47
.L35:
	.loc 1 567 15
	movl	$0, -8(%rbp)
	.loc 1 567 9
	jmp	.L42
.L45:
	.loc 1 568 19
	movl	$0, -4(%rbp)
	.loc 1 568 13
	jmp	.L43
.L44:
	.loc 1 569 18
	movl	-4(%rbp), %eax
	imull	16(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	imull	24(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm1
	.loc 1 569 46
	movl	-4(%rbp), %eax
	imull	-44(%rbp), %eax
	movl	%eax, %edx
	.loc 1 569 56
	movl	-8(%rbp), %eax
	imull	-48(%rbp), %eax
	.loc 1 569 54
	addl	%edx, %eax
	cltq
	.loc 1 569 44
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	.loc 1 569 18
	movl	-4(%rbp), %eax
	imull	16(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	imull	24(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 569 40
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 568 28 discriminator 3
	addl	$1, -4(%rbp)
.L43:
	.loc 1 568 24 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L44
	.loc 1 567 24 discriminator 2
	addl	$1, -8(%rbp)
.L42:
	.loc 1 567 20 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L45
.L47:
	.loc 1 573 1
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4870:
	.size	dgeaxpy, .-dgeaxpy
	.type	dgescal, @function
dgescal:
.LFB4871:
	.loc 1 585 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movsd	%xmm0, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, -44(%rbp)
	movl	%r8d, -48(%rbp)
	.loc 1 588 8
	pxor	%xmm0, %xmm0
	ucomisd	-32(%rbp), %xmm0
	jp	.L60
	pxor	%xmm0, %xmm0
	ucomisd	-32(%rbp), %xmm0
	je	.L49
.L60:
	.loc 1 589 15
	movl	$0, -8(%rbp)
	.loc 1 589 9
	jmp	.L51
.L54:
	.loc 1 590 19
	movl	$0, -4(%rbp)
	.loc 1 590 13
	jmp	.L52
.L53:
	.loc 1 591 18
	movl	-4(%rbp), %eax
	imull	-44(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	imull	-48(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movl	-4(%rbp), %eax
	imull	-44(%rbp), %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	imull	-48(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 591 40
	mulsd	-32(%rbp), %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 590 28 discriminator 3
	addl	$1, -4(%rbp)
.L52:
	.loc 1 590 24 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L53
	.loc 1 589 24 discriminator 2
	addl	$1, -8(%rbp)
.L51:
	.loc 1 589 20 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L54
	.loc 1 601 1
	jmp	.L61
.L49:
	.loc 1 595 15
	movl	$0, -8(%rbp)
	.loc 1 595 9
	jmp	.L56
.L59:
	.loc 1 596 19
	movl	$0, -4(%rbp)
	.loc 1 596 13
	jmp	.L57
.L58:
	.loc 1 597 20
	movl	-4(%rbp), %eax
	imull	-44(%rbp), %eax
	movl	%eax, %edx
	.loc 1 597 30
	movl	-8(%rbp), %eax
	imull	-48(%rbp), %eax
	.loc 1 597 28
	addl	%edx, %eax
	cltq
	.loc 1 597 18
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 597 40
	pxor	%xmm0, %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 596 28 discriminator 3
	addl	$1, -4(%rbp)
.L57:
	.loc 1 596 24 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L58
	.loc 1 595 24 discriminator 2
	addl	$1, -8(%rbp)
.L56:
	.loc 1 595 20 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L59
.L61:
	.loc 1 601 1
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4871:
	.size	dgescal, .-dgescal
	.type	dgemm_macro_kernel, @function
dgemm_macro_kernel:
.LFB4872:
	.loc 1 616 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movl	%edi, -52(%rbp)
	movl	%esi, -56(%rbp)
	movl	%edx, -60(%rbp)
	movsd	%xmm0, -72(%rbp)
	movsd	%xmm1, -80(%rbp)
	movq	%rcx, -88(%rbp)
	movl	%r8d, -64(%rbp)
	movl	%r9d, -92(%rbp)
	.loc 1 617 20
	movl	-52(%rbp), %eax
	addl	$3, %eax
	.loc 1 617 9
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -28(%rbp)
	.loc 1 618 20
	movl	-56(%rbp), %eax
	addl	$3, %eax
	.loc 1 618 9
	leal	3(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$2, %eax
	movl	%eax, -32(%rbp)
	.loc 1 620 9
	movl	-52(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, -36(%rbp)
	.loc 1 621 9
	movl	-56(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$30, %eax
	addl	%eax, %edx
	andl	$3, %edx
	subl	%eax, %edx
	movl	%edx, -40(%rbp)
	.loc 1 629 11
	movl	$0, -8(%rbp)
	.loc 1 629 5
	jmp	.L63
.L73:
	.loc 1 630 23
	movl	-32(%rbp), %eax
	subl	$1, %eax
	.loc 1 630 42
	cmpl	%eax, -8(%rbp)
	jne	.L64
	.loc 1 630 26 discriminator 1
	cmpl	$0, -40(%rbp)
	je	.L64
	.loc 1 630 42 discriminator 3
	movl	-40(%rbp), %eax
	.loc 1 630 42 is_stmt 0
	jmp	.L65
.L64:
	.loc 1 630 42 discriminator 4
	movl	$4, %eax
.L65:
	.loc 1 630 15 is_stmt 1 discriminator 6
	movl	%eax, -44(%rbp)
	.loc 1 631 22
	movl	-8(%rbp), %eax
	imull	-60(%rbp), %eax
	.loc 1 631 25
	sall	$2, %eax
	.loc 1 631 15
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_B(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	.loc 1 633 15
	movl	$0, -4(%rbp)
	.loc 1 633 9
	jmp	.L66
.L72:
	.loc 1 634 27
	movl	-28(%rbp), %eax
	subl	$1, %eax
	.loc 1 634 46
	cmpl	%eax, -4(%rbp)
	jne	.L67
	.loc 1 634 30 discriminator 1
	cmpl	$0, -36(%rbp)
	je	.L67
	.loc 1 634 46 discriminator 3
	movl	-36(%rbp), %eax
	.loc 1 634 46 is_stmt 0
	jmp	.L68
.L67:
	.loc 1 634 46 discriminator 4
	movl	$4, %eax
.L68:
	.loc 1 634 19 is_stmt 1 discriminator 6
	movl	%eax, -48(%rbp)
	.loc 1 635 27
	movl	-4(%rbp), %eax
	addl	$1, %eax
	.loc 1 635 30
	imull	-60(%rbp), %eax
	.loc 1 635 33
	sall	$2, %eax
	.loc 1 635 19
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_A(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	.loc 1 637 22
	movl	-28(%rbp), %eax
	subl	$1, %eax
	.loc 1 637 16
	cmpl	%eax, -4(%rbp)
	jne	.L69
	.loc 1 638 23
	leaq	_A(%rip), %rax
	movq	%rax, -16(%rbp)
	.loc 1 639 31
	movl	-8(%rbp), %eax
	addl	$1, %eax
	.loc 1 639 34
	imull	-60(%rbp), %eax
	.loc 1 639 37
	sall	$2, %eax
	.loc 1 639 23
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_B(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	.loc 1 640 26
	movl	-32(%rbp), %eax
	subl	$1, %eax
	.loc 1 640 20
	cmpl	%eax, -8(%rbp)
	jne	.L69
	.loc 1 641 27
	leaq	_B(%rip), %rax
	movq	%rax, -24(%rbp)
.L69:
	.loc 1 645 16
	cmpl	$4, -48(%rbp)
	jne	.L70
	.loc 1 645 24 discriminator 1
	cmpl	$4, -44(%rbp)
	jne	.L70
	.loc 1 646 17
	movl	-92(%rbp), %eax
	movslq	%eax, %r9
	movl	-64(%rbp), %eax
	movslq	%eax, %r8
	.loc 1 648 43
	movl	-4(%rbp), %eax
	imull	-64(%rbp), %eax
	movl	%eax, %edx
	.loc 1 648 56
	movl	-8(%rbp), %eax
	imull	-92(%rbp), %eax
	.loc 1 648 51
	addl	%edx, %eax
	sall	$2, %eax
	cltq
	.loc 1 648 38
	leaq	0(,%rax,8), %rdx
	.loc 1 646 17
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	.loc 1 646 66
	movl	-8(%rbp), %eax
	imull	-60(%rbp), %eax
	.loc 1 646 69
	sall	$2, %eax
	.loc 1 646 61
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_B(%rip), %rax
	addq	%rax, %rdx
	.loc 1 646 52
	movl	-4(%rbp), %eax
	imull	-60(%rbp), %eax
	.loc 1 646 55
	sall	$2, %eax
	.loc 1 646 47
	cltq
	leaq	0(,%rax,8), %rsi
	leaq	_A(%rip), %rax
	addq	%rax, %rsi
	.loc 1 646 17
	movl	-60(%rbp), %eax
	cltq
	movsd	-80(%rbp), %xmm0
	movq	-72(%rbp), %rdi
	pushq	-24(%rbp)
	pushq	-16(%rbp)
	movapd	%xmm0, %xmm1
	movq	%rdi, %xmm0
	movq	%rax, %rdi
	call	dgemm_micro_kernel
	addq	$16, %rsp
	jmp	.L71
.L70:
	.loc 1 652 66
	movl	-8(%rbp), %eax
	imull	-60(%rbp), %eax
	.loc 1 652 69
	sall	$2, %eax
	.loc 1 652 61
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_B(%rip), %rax
	addq	%rax, %rdx
	.loc 1 652 52
	movl	-4(%rbp), %eax
	imull	-60(%rbp), %eax
	.loc 1 652 55
	sall	$2, %eax
	.loc 1 652 47
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	_A(%rip), %rax
	leaq	(%rcx,%rax), %rsi
	.loc 1 652 17
	movl	-60(%rbp), %eax
	cltq
	movq	-72(%rbp), %rdi
	pushq	-24(%rbp)
	pushq	-16(%rbp)
	movl	$4, %r9d
	movl	$1, %r8d
	leaq	_C(%rip), %rcx
	pxor	%xmm1, %xmm1
	movq	%rdi, %xmm0
	movq	%rax, %rdi
	call	dgemm_micro_kernel
	addq	$16, %rsp
	.loc 1 657 32
	movl	-4(%rbp), %eax
	imull	-64(%rbp), %eax
	movl	%eax, %edx
	.loc 1 657 45
	movl	-8(%rbp), %eax
	imull	-92(%rbp), %eax
	.loc 1 657 40
	addl	%edx, %eax
	sall	$2, %eax
	cltq
	.loc 1 657 27
	leaq	0(,%rax,8), %rdx
	.loc 1 656 17
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %r9
	movl	-92(%rbp), %ecx
	movl	-64(%rbp), %edx
	movq	-80(%rbp), %rdi
	movl	-44(%rbp), %esi
	movl	-48(%rbp), %eax
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%r9, %rdx
	movq	%rdi, %xmm0
	movl	%eax, %edi
	call	dgescal
	.loc 1 659 32
	movl	-4(%rbp), %eax
	imull	-64(%rbp), %eax
	movl	%eax, %edx
	.loc 1 659 45
	movl	-8(%rbp), %eax
	imull	-92(%rbp), %eax
	.loc 1 659 40
	addl	%edx, %eax
	sall	$2, %eax
	cltq
	.loc 1 659 27
	leaq	0(,%rax,8), %rdx
	.loc 1 658 17
	movq	-88(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	.LC1(%rip), %rdi
	movl	-44(%rbp), %esi
	movl	-48(%rbp), %eax
	movl	-92(%rbp), %edx
	pushq	%rdx
	movl	-64(%rbp), %edx
	pushq	%rdx
	movq	%rcx, %r9
	movl	$4, %r8d
	movl	$1, %ecx
	leaq	_C(%rip), %rdx
	movq	%rdi, %xmm0
	movl	%eax, %edi
	call	dgeaxpy
	addq	$16, %rsp
.L71:
	.loc 1 633 25 discriminator 2
	addl	$1, -4(%rbp)
.L66:
	.loc 1 633 20 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L72
	.loc 1 629 21 discriminator 2
	addl	$1, -8(%rbp)
.L63:
	.loc 1 629 16 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L73
	.loc 1 663 1
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4872:
	.size	dgemm_macro_kernel, .-dgemm_macro_kernel
	.globl	dgemm_nn
	.type	dgemm_nn, @function
dgemm_nn:
.LFB4873:
	.loc 1 682 1
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movl	%edi, -68(%rbp)
	movl	%esi, -72(%rbp)
	movl	%edx, -76(%rbp)
	movsd	%xmm0, -88(%rbp)
	movq	%rcx, -96(%rbp)
	movl	%r8d, -80(%rbp)
	movl	%r9d, -100(%rbp)
	movsd	%xmm1, -112(%rbp)
	.loc 1 683 19
	movl	-68(%rbp), %eax
	addl	$383, %eax
	.loc 1 683 9
	movslq	%eax, %rdx
	imulq	$715827883, %rdx, %rdx
	shrq	$32, %rdx
	movl	%edx, %ecx
	sarl	$6, %ecx
	cltd
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -16(%rbp)
	.loc 1 684 19
	movl	-72(%rbp), %eax
	addl	$4095, %eax
	.loc 1 684 9
	leal	4095(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$12, %eax
	movl	%eax, -20(%rbp)
	.loc 1 685 19
	movl	-76(%rbp), %eax
	addl	$383, %eax
	.loc 1 685 9
	movslq	%eax, %rdx
	imulq	$715827883, %rdx, %rdx
	shrq	$32, %rdx
	movl	%edx, %ecx
	sarl	$6, %ecx
	cltd
	movl	%ecx, %eax
	subl	%edx, %eax
	movl	%eax, -24(%rbp)
	.loc 1 687 9
	movl	-68(%rbp), %edx
	movslq	%edx, %rax
	imulq	$715827883, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$6, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%eax, %eax
	addl	%ecx, %eax
	sall	$7, %eax
	subl	%eax, %edx
	movl	%edx, -28(%rbp)
	.loc 1 688 9
	movl	-72(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$20, %eax
	addl	%eax, %edx
	andl	$4095, %edx
	subl	%eax, %edx
	movl	%edx, -32(%rbp)
	.loc 1 689 9
	movl	-76(%rbp), %edx
	movslq	%edx, %rax
	imulq	$715827883, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %ecx
	sarl	$6, %ecx
	movl	%edx, %eax
	sarl	$31, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	%eax, %eax
	addl	%ecx, %eax
	sall	$7, %eax
	subl	%eax, %edx
	movl	%edx, -36(%rbp)
	.loc 1 696 8
	pxor	%xmm0, %xmm0
	ucomisd	-88(%rbp), %xmm0
	jp	.L93
	pxor	%xmm0, %xmm0
	ucomisd	-88(%rbp), %xmm0
	je	.L75
.L93:
	.loc 1 696 20 discriminator 1
	cmpl	$0, -76(%rbp)
	jne	.L77
.L75:
	.loc 1 697 9
	movl	56(%rbp), %r8d
	movl	48(%rbp), %ecx
	movq	40(%rbp), %rdx
	movq	-112(%rbp), %rdi
	movl	-72(%rbp), %esi
	movl	-68(%rbp), %eax
	movq	%rdi, %xmm0
	movl	%eax, %edi
	call	dgescal
	.loc 1 698 9
	jmp	.L74
.L77:
	.loc 1 701 11
	movl	$0, -8(%rbp)
	.loc 1 701 5
	jmp	.L79
.L92:
	.loc 1 702 20
	movl	-20(%rbp), %eax
	subl	$1, %eax
	.loc 1 702 39
	cmpl	%eax, -8(%rbp)
	jne	.L80
	.loc 1 702 23 discriminator 1
	cmpl	$0, -32(%rbp)
	je	.L80
	.loc 1 702 39 discriminator 3
	movl	-32(%rbp), %eax
	.loc 1 702 39 is_stmt 0
	jmp	.L81
.L80:
	.loc 1 702 39 discriminator 4
	movl	$4096, %eax
.L81:
	.loc 1 702 12 is_stmt 1 discriminator 6
	movl	%eax, -40(%rbp)
	.loc 1 704 15
	movl	$0, -12(%rbp)
	.loc 1 704 9
	jmp	.L82
.L91:
	.loc 1 705 27
	movl	-24(%rbp), %eax
	subl	$1, %eax
	.loc 1 705 48
	cmpl	%eax, -12(%rbp)
	jne	.L83
	.loc 1 705 30 discriminator 1
	cmpl	$0, -36(%rbp)
	je	.L83
	.loc 1 705 48 discriminator 3
	movl	-36(%rbp), %eax
	.loc 1 705 48 is_stmt 0
	jmp	.L84
.L83:
	.loc 1 705 48 discriminator 4
	movl	$384, %eax
.L84:
	.loc 1 705 19 is_stmt 1 discriminator 6
	movl	%eax, -44(%rbp)
	.loc 1 706 35
	cmpl	$0, -12(%rbp)
	jne	.L85
	.loc 1 706 35 is_stmt 0 discriminator 1
	movsd	-112(%rbp), %xmm0
	jmp	.L86
.L85:
	.loc 1 706 35 discriminator 2
	movsd	.LC1(%rip), %xmm0
.L86:
	.loc 1 706 19 is_stmt 1 discriminator 4
	movsd	%xmm0, -56(%rbp)
	.loc 1 709 27
	movl	-12(%rbp), %eax
	imull	24(%rbp), %eax
	movl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$7, %eax
	movl	%eax, %edx
	.loc 1 709 40
	movl	-8(%rbp), %eax
	imull	32(%rbp), %eax
	sall	$12, %eax
	.loc 1 709 35
	addl	%edx, %eax
	cltq
	.loc 1 709 22
	leaq	0(,%rax,8), %rdx
	.loc 1 708 13
	movq	16(%rbp), %rax
	leaq	(%rdx,%rax), %rdi
	movl	32(%rbp), %ecx
	movl	24(%rbp), %edx
	movl	-40(%rbp), %esi
	movl	-44(%rbp), %eax
	leaq	_B(%rip), %r9
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%rdi, %rdx
	movl	%eax, %edi
	call	pack_B
	.loc 1 712 19
	movl	$0, -4(%rbp)
	.loc 1 712 13
	jmp	.L87
.L90:
	.loc 1 713 28
	movl	-16(%rbp), %eax
	subl	$1, %eax
	.loc 1 713 47
	cmpl	%eax, -4(%rbp)
	jne	.L88
	.loc 1 713 31 discriminator 1
	cmpl	$0, -28(%rbp)
	je	.L88
	.loc 1 713 47 discriminator 3
	movl	-28(%rbp), %eax
	.loc 1 713 47 is_stmt 0
	jmp	.L89
.L88:
	.loc 1 713 47 discriminator 4
	movl	$384, %eax
.L89:
	.loc 1 713 20 is_stmt 1 discriminator 6
	movl	%eax, -60(%rbp)
	.loc 1 716 31
	movl	-4(%rbp), %eax
	imull	-80(%rbp), %eax
	movl	%eax, %edx
	.loc 1 716 44
	movl	-12(%rbp), %eax
	imull	-100(%rbp), %eax
	.loc 1 716 39
	addl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$7, %eax
	cltq
	.loc 1 716 26
	leaq	0(,%rax,8), %rdx
	.loc 1 715 17
	movq	-96(%rbp), %rax
	leaq	(%rdx,%rax), %rdi
	movl	-100(%rbp), %ecx
	movl	-80(%rbp), %edx
	movl	-44(%rbp), %esi
	movl	-60(%rbp), %eax
	leaq	_A(%rip), %r9
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movq	%rdi, %rdx
	movl	%eax, %edi
	call	pack_A
	.loc 1 720 43
	movl	-4(%rbp), %eax
	imull	48(%rbp), %eax
	movl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	sall	$7, %eax
	movl	%eax, %edx
	.loc 1 720 56
	movl	-8(%rbp), %eax
	imull	56(%rbp), %eax
	sall	$12, %eax
	.loc 1 720 51
	addl	%edx, %eax
	cltq
	.loc 1 720 38
	leaq	0(,%rax,8), %rdx
	.loc 1 719 17
	movq	40(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	56(%rbp), %r9d
	movl	48(%rbp), %r8d
	movsd	-56(%rbp), %xmm0
	movq	-88(%rbp), %rdi
	movl	-44(%rbp), %edx
	movl	-40(%rbp), %esi
	movl	-60(%rbp), %eax
	movapd	%xmm0, %xmm1
	movq	%rdi, %xmm0
	movl	%eax, %edi
	call	dgemm_macro_kernel
	.loc 1 712 29 discriminator 2
	addl	$1, -4(%rbp)
.L87:
	.loc 1 712 24 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jl	.L90
	.loc 1 704 25 discriminator 2
	addl	$1, -12(%rbp)
.L82:
	.loc 1 704 20 discriminator 1
	movl	-12(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L91
	.loc 1 701 21 discriminator 2
	addl	$1, -8(%rbp)
.L79:
	.loc 1 701 16 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L92
.L74:
	.loc 1 725 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4873:
	.size	dgemm_nn, .-dgemm_nn
	.globl	fill_matrix
	.type	fill_matrix, @function
fill_matrix:
.LFB4874:
	.loc 1 730 51
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
.LBB2:
	.loc 1 731 14
	movl	$0, -4(%rbp)
	.loc 1 731 5
	jmp	.L95
.L96:
	.loc 1 732 26
	call	rand@PLT
	.loc 1 732 18 discriminator 1
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	.loc 1 732 12 discriminator 1
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 732 33 discriminator 1
	movsd	.LC2(%rip), %xmm1
	divsd	%xmm1, %xmm0
	.loc 1 732 16 discriminator 1
	movsd	%xmm0, (%rax)
	.loc 1 731 38 discriminator 3
	addl	$1, -4(%rbp)
.L95:
	.loc 1 731 30 discriminator 1
	movl	-28(%rbp), %eax
	imull	-32(%rbp), %eax
	.loc 1 731 23 discriminator 1
	cmpl	%eax, -4(%rbp)
	jl	.L96
.LBE2:
	.loc 1 734 1
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4874:
	.size	fill_matrix, .-fill_matrix
	.section	.rodata
.LC3:
	.string	"%.2f "
	.text
	.globl	print_matrix
	.type	print_matrix, @function
print_matrix:
.LFB4875:
	.loc 1 736 52
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
.LBB3:
	.loc 1 737 14
	movl	$0, -4(%rbp)
	.loc 1 737 5
	jmp	.L98
.L101:
.LBB4:
	.loc 1 738 18
	movl	$0, -8(%rbp)
	.loc 1 738 9
	jmp	.L99
.L100:
	.loc 1 739 35
	movl	-4(%rbp), %eax
	imull	-32(%rbp), %eax
	movl	%eax, %edx
	.loc 1 739 42
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	cltq
	.loc 1 739 32
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 739 13
	movq	(%rax), %rax
	movq	%rax, %xmm0
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	.loc 1 738 35 discriminator 3
	addl	$1, -8(%rbp)
.L99:
	.loc 1 738 27 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jl	.L100
.LBE4:
	.loc 1 741 9
	movl	$10, %edi
	call	putchar@PLT
	.loc 1 737 31 discriminator 2
	addl	$1, -4(%rbp)
.L98:
	.loc 1 737 23 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L101
.LBE3:
	.loc 1 743 1
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4875:
	.size	print_matrix, .-print_matrix
	.globl	naive_matrix_multiply
	.type	naive_matrix_multiply, @function
naive_matrix_multiply:
.LFB4876:
	.loc 1 745 71
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movl	%ecx, -60(%rbp)
.LBB5:
	.loc 1 746 14
	movl	$0, -4(%rbp)
	.loc 1 746 5
	jmp	.L103
.L108:
.LBB6:
	.loc 1 747 18
	movl	$0, -8(%rbp)
	.loc 1 747 9
	jmp	.L104
.L107:
.LBB7:
	.loc 1 748 20
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
.LBB8:
	.loc 1 749 22
	movl	$0, -20(%rbp)
	.loc 1 749 13
	jmp	.L105
.L106:
	.loc 1 750 28
	movl	-4(%rbp), %eax
	imull	-60(%rbp), %eax
	movl	%eax, %edx
	.loc 1 750 35
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	cltq
	.loc 1 750 25
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm1
	.loc 1 750 46
	movl	-20(%rbp), %eax
	imull	-60(%rbp), %eax
	movl	%eax, %edx
	.loc 1 750 53
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	cltq
	.loc 1 750 43
	leaq	0(,%rax,8), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	.loc 1 750 40
	mulsd	%xmm1, %xmm0
	.loc 1 750 21
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	.loc 1 749 39 discriminator 3
	addl	$1, -20(%rbp)
.L105:
	.loc 1 749 31 discriminator 1
	movl	-20(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L106
.LBE8:
	.loc 1 752 17
	movl	-4(%rbp), %eax
	imull	-60(%rbp), %eax
	movl	%eax, %edx
	.loc 1 752 24
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	cltq
	.loc 1 752 14
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 752 29
	movsd	-16(%rbp), %xmm0
	movsd	%xmm0, (%rax)
.LBE7:
	.loc 1 747 35 discriminator 2
	addl	$1, -8(%rbp)
.L104:
	.loc 1 747 27 discriminator 1
	movl	-8(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L107
.LBE6:
	.loc 1 746 31 discriminator 2
	addl	$1, -4(%rbp)
.L103:
	.loc 1 746 23 discriminator 1
	movl	-4(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L108
.LBE5:
	.loc 1 755 1
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4876:
	.size	naive_matrix_multiply, .-naive_matrix_multiply
	.section	.rodata
	.align 8
.LC4:
	.string	"Comparing element at index %d: %.2f vs %.2f\n"
.LC5:
	.string	"MISMATCHES  / TOTAL : %d/%d\n"
.LC6:
	.string	"MATCHES     / TOTAL : %d/%d\n"
	.text
	.globl	compare_matrices
	.type	compare_matrices, @function
compare_matrices:
.LFB4877:
	.loc 1 757 70
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, -40(%rbp)
	.loc 1 758 9
	movl	$0, -4(%rbp)
	.loc 1 759 9
	movl	$0, -8(%rbp)
	.loc 1 761 12
	movl	$0, -12(%rbp)
	.loc 1 761 5
	jmp	.L110
.L114:
	.loc 1 762 81
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 762 9
	movsd	(%rax), %xmm0
	.loc 1 762 72
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	.loc 1 762 9
	movq	(%rax), %rdx
	movl	-12(%rbp), %eax
	movapd	%xmm0, %xmm1
	movq	%rdx, %xmm0
	movl	%eax, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$2, %eax
	call	printf@PLT
	.loc 1 763 17
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	.loc 1 763 28
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm1
	.loc 1 763 12
	ucomisd	%xmm1, %xmm0
	jp	.L116
	ucomisd	%xmm1, %xmm0
	je	.L111
.L116:
	.loc 1 765 18
	addl	$1, -4(%rbp)
	jmp	.L113
.L111:
	.loc 1 768 20
	addl	$1, -8(%rbp)
.L113:
	.loc 1 761 34 discriminator 2
	addl	$1, -12(%rbp)
.L110:
	.loc 1 761 26 discriminator 1
	movl	-36(%rbp), %eax
	imull	-40(%rbp), %eax
	.loc 1 761 19 discriminator 1
	cmpl	%eax, -12(%rbp)
	jl	.L114
	.loc 1 771 5
	movl	-12(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 772 5
	movl	-12(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 773 12
	movl	$1, %eax
	.loc 1 774 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4877:
	.size	compare_matrices, .-compare_matrices
	.section	.rodata
.LC7:
	.string	"generating values for mtx"
	.align 8
.LC9:
	.string	"Naive implementation took %.6f seconds\n"
	.align 8
.LC10:
	.string	"Optimized implementation took %.6f seconds\n"
.LC11:
	.string	"dgemm_nn.c"
	.align 8
.LC12:
	.string	"compare_matrices(C_naive, C_optimized, N, N)"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4878:
	.loc 1 776 12
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	.loc 1 777 27
	movl	$131072, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 1 778 27
	movl	$131072, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	.loc 1 779 33
	movl	$8, %esi
	movl	$16384, %edi
	call	calloc@PLT
	movq	%rax, -24(%rbp)
	.loc 1 780 37
	movl	$8, %esi
	movl	$16384, %edi
	call	calloc@PLT
	movq	%rax, -32(%rbp)
	.loc 1 782 11
	movl	$0, %edi
	call	time@PLT
	.loc 1 782 5 discriminator 1
	movl	%eax, %edi
	call	srand@PLT
	.loc 1 784 5
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	.loc 1 785 5
	movq	-8(%rbp), %rax
	movl	$128, %edx
	movl	$128, %esi
	movq	%rax, %rdi
	call	fill_matrix
	.loc 1 786 5
	movq	-16(%rbp), %rax
	movl	$128, %edx
	movl	$128, %esi
	movq	%rax, %rdi
	call	fill_matrix
	.loc 1 789 27
	call	clock@PLT
	movq	%rax, -40(%rbp)
	.loc 1 790 5
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movq	-8(%rbp), %rax
	movl	$128, %ecx
	movq	%rax, %rdi
	call	naive_matrix_multiply
	.loc 1 791 25
	call	clock@PLT
	movq	%rax, -48(%rbp)
	.loc 1 792 44
	movq	-48(%rbp), %rax
	subq	-40(%rbp), %rax
	.loc 1 792 25
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	.loc 1 792 12
	movsd	.LC8(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -56(%rbp)
	.loc 1 795 31
	call	clock@PLT
	movq	%rax, -64(%rbp)
	.loc 1 796 5
	movq	-8(%rbp), %rdx
	movq	.LC1(%rip), %rax
	pushq	$1
	pushq	$128
	pushq	-32(%rbp)
	pushq	$1
	pushq	$128
	pushq	-16(%rbp)
	pxor	%xmm1, %xmm1
	movl	$1, %r9d
	movl	$128, %r8d
	movq	%rdx, %rcx
	movq	%rax, %xmm0
	movl	$128, %edx
	movl	$128, %esi
	movl	$128, %edi
	call	dgemm_nn
	addq	$48, %rsp
	.loc 1 797 29
	call	clock@PLT
	movq	%rax, -72(%rbp)
	.loc 1 798 52
	movq	-72(%rbp), %rax
	subq	-64(%rbp), %rax
	.loc 1 798 29
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	.loc 1 798 12
	movsd	.LC8(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -80(%rbp)
	.loc 1 800 5
	movq	-56(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	.loc 1 801 5
	movq	-80(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	.loc 1 811 5
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rax
	movl	$128, %ecx
	movl	$128, %edx
	movq	%rax, %rdi
	call	compare_matrices
	.loc 1 811 5 is_stmt 0 discriminator 1
	testl	%eax, %eax
	jne	.L118
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$811, %edx
	leaq	.LC11(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L118:
	.loc 1 814 5 is_stmt 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 815 5
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 816 5
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 817 5
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	.loc 1 819 12
	movl	$0, %eax
	.loc 1 820 1
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4878:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 5
__PRETTY_FUNCTION__.0:
	.string	"main"
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.align 8
.LC2:
	.long	-4194304
	.long	1105199103
	.align 8
.LC8:
	.long	0
	.long	1093567616
	.text
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/13/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/types/clock_t.h"
	.file 5 "/usr/include/x86_64-linux-gnu/bits/types/time_t.h"
	.file 6 "/usr/include/stdlib.h"
	.file 7 "/usr/include/assert.h"
	.file 8 "/usr/include/time.h"
	.file 9 "/usr/include/stdio.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xc9d
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0x17
	.long	.LASF75
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0xb
	.long	.LASF9
	.byte	0x2
	.byte	0xd6
	.byte	0x17
	.long	0x3a
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x18
	.byte	0x8
	.uleb128 0x6
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x6
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x6
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x19
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0xb
	.long	.LASF10
	.byte	0x3
	.byte	0x9c
	.byte	0x1b
	.long	0x6d
	.uleb128 0xb
	.long	.LASF11
	.byte	0x3
	.byte	0xa0
	.byte	0x1a
	.long	0x6d
	.uleb128 0x6
	.byte	0x1
	.byte	0x6
	.long	.LASF12
	.uleb128 0xe
	.long	0x8c
	.uleb128 0xb
	.long	.LASF13
	.byte	0x4
	.byte	0x7
	.byte	0x13
	.long	0x74
	.uleb128 0xb
	.long	.LASF14
	.byte	0x5
	.byte	0xa
	.byte	0x12
	.long	0x80
	.uleb128 0xc
	.long	0x93
	.uleb128 0x6
	.byte	0x8
	.byte	0x5
	.long	.LASF15
	.uleb128 0x6
	.byte	0x4
	.byte	0x4
	.long	.LASF16
	.uleb128 0x6
	.byte	0x8
	.byte	0x7
	.long	.LASF17
	.uleb128 0x6
	.byte	0x8
	.byte	0x4
	.long	.LASF18
	.uleb128 0xe
	.long	0xca
	.uleb128 0x6
	.byte	0x10
	.byte	0x4
	.long	.LASF19
	.uleb128 0x6
	.byte	0x2
	.byte	0x4
	.long	.LASF20
	.uleb128 0x6
	.byte	0x2
	.byte	0x4
	.long	.LASF21
	.uleb128 0xd
	.long	0xca
	.long	0xfe
	.uleb128 0x13
	.long	0x3a
	.long	0x23fff
	.byte	0
	.uleb128 0xf
	.string	"_A"
	.byte	0x14
	.long	0xeb
	.uleb128 0x9
	.byte	0x3
	.quad	_A
	.uleb128 0xd
	.long	0xca
	.long	0x124
	.uleb128 0x13
	.long	0x3a
	.long	0x17ffff
	.byte	0
	.uleb128 0xf
	.string	"_B"
	.byte	0x15
	.long	0x111
	.uleb128 0x9
	.byte	0x3
	.quad	_B
	.uleb128 0xd
	.long	0xca
	.long	0x147
	.uleb128 0x14
	.long	0x3a
	.byte	0xf
	.byte	0
	.uleb128 0xf
	.string	"_C"
	.byte	0x16
	.long	0x137
	.uleb128 0x9
	.byte	0x3
	.quad	_C
	.uleb128 0x15
	.long	.LASF22
	.value	0x238
	.long	0x16b
	.uleb128 0x3
	.long	0x48
	.byte	0
	.uleb128 0x1a
	.long	.LASF24
	.byte	0x7
	.byte	0x45
	.byte	0xd
	.long	0x18c
	.uleb128 0x3
	.long	0xb0
	.uleb128 0x3
	.long	0xb0
	.uleb128 0x3
	.long	0x41
	.uleb128 0x3
	.long	0xb0
	.byte	0
	.uleb128 0x1b
	.long	.LASF29
	.byte	0x8
	.byte	0x48
	.byte	0x10
	.long	0x98
	.uleb128 0x15
	.long	.LASF23
	.value	0x1c8
	.long	0x1a9
	.uleb128 0x3
	.long	0x41
	.byte	0
	.uleb128 0x1c
	.long	.LASF25
	.byte	0x8
	.byte	0x4c
	.byte	0xf
	.long	0xa4
	.long	0x1bf
	.uleb128 0x3
	.long	0x1bf
	.byte	0
	.uleb128 0xc
	.long	0xa4
	.uleb128 0x10
	.long	.LASF26
	.byte	0x6
	.value	0x22c
	.byte	0xe
	.long	0x48
	.long	0x1e0
	.uleb128 0x3
	.long	0x2e
	.uleb128 0x3
	.long	0x2e
	.byte	0
	.uleb128 0x10
	.long	.LASF27
	.byte	0x6
	.value	0x229
	.byte	0xe
	.long	0x48
	.long	0x1f7
	.uleb128 0x3
	.long	0x2e
	.byte	0
	.uleb128 0x10
	.long	.LASF28
	.byte	0x9
	.value	0x164
	.byte	0xc
	.long	0x66
	.long	0x20f
	.uleb128 0x3
	.long	0xb0
	.uleb128 0x1d
	.byte	0
	.uleb128 0x1e
	.long	.LASF30
	.byte	0x6
	.value	0x1c6
	.byte	0xc
	.long	0x66
	.uleb128 0x1f
	.long	.LASF31
	.byte	0x1
	.byte	0x1e
	.byte	0xd
	.long	0x260
	.uleb128 0x3
	.long	0x260
	.uleb128 0x3
	.long	0x260
	.uleb128 0x3
	.long	0x265
	.uleb128 0x3
	.long	0x260
	.uleb128 0x3
	.long	0x260
	.uleb128 0x3
	.long	0x6d
	.uleb128 0x3
	.long	0x6d
	.uleb128 0x3
	.long	0x6d
	.uleb128 0x3
	.long	0x6d
	.uleb128 0x3
	.long	0xca
	.uleb128 0x3
	.long	0xca
	.byte	0
	.uleb128 0xc
	.long	0xd1
	.uleb128 0xc
	.long	0xca
	.uleb128 0x20
	.long	.LASF46
	.byte	0x1
	.value	0x308
	.byte	0x5
	.long	0x66
	.quad	.LFB4878
	.quad	.LFE4878-.LFB4878
	.uleb128 0x1
	.byte	0x9c
	.long	0x337
	.uleb128 0x1
	.string	"A"
	.value	0x309
	.byte	0xd
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"B"
	.value	0x30a
	.byte	0xd
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x9
	.long	.LASF32
	.value	0x30b
	.byte	0xd
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x9
	.long	.LASF33
	.value	0x30c
	.byte	0xd
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x9
	.long	.LASF34
	.value	0x315
	.byte	0xd
	.long	0x98
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x9
	.long	.LASF35
	.value	0x317
	.byte	0xd
	.long	0x98
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x9
	.long	.LASF36
	.value	0x318
	.byte	0xc
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x9
	.long	.LASF37
	.value	0x31b
	.byte	0xd
	.long	0x98
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x9
	.long	.LASF38
	.value	0x31d
	.byte	0xd
	.long	0x98
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x9
	.long	.LASF39
	.value	0x31e
	.byte	0xc
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x21
	.long	.LASF76
	.long	0x347
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.0
	.byte	0
	.uleb128 0xd
	.long	0x93
	.long	0x347
	.uleb128 0x14
	.long	0x3a
	.byte	0x4
	.byte	0
	.uleb128 0xe
	.long	0x337
	.uleb128 0x22
	.long	.LASF77
	.byte	0x1
	.value	0x2f5
	.byte	0x5
	.long	0x66
	.quad	.LFB4877
	.quad	.LFE4877-.LFB4877
	.uleb128 0x1
	.byte	0x9c
	.long	0x3d7
	.uleb128 0x2
	.long	.LASF40
	.value	0x2f5
	.byte	0x1e
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.long	.LASF41
	.value	0x2f5
	.byte	0x2c
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x2
	.long	.LASF42
	.value	0x2f5
	.byte	0x36
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x2
	.long	.LASF43
	.value	0x2f5
	.byte	0x40
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x9
	.long	.LASF44
	.value	0x2f6
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x9
	.long	.LASF45
	.value	0x2f7
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"i"
	.value	0x2f8
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x23
	.long	.LASF47
	.byte	0x1
	.value	0x2e9
	.byte	0x6
	.quad	.LFB4876
	.quad	.LFE4876-.LFB4876
	.uleb128 0x1
	.byte	0x9c
	.long	0x4ad
	.uleb128 0x4
	.string	"A"
	.value	0x2e9
	.byte	0x24
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x4
	.string	"B"
	.value	0x2e9
	.byte	0x2f
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x4
	.string	"C"
	.value	0x2e9
	.byte	0x3a
	.long	0x265
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x2
	.long	.LASF48
	.value	0x2e9
	.byte	0x41
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0xa
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.uleb128 0x1
	.string	"i"
	.value	0x2ea
	.byte	0xe
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.quad	.LBB6
	.quad	.LBE6-.LBB6
	.uleb128 0x1
	.string	"j"
	.value	0x2eb
	.byte	0x12
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xa
	.quad	.LBB7
	.quad	.LBE7-.LBB7
	.uleb128 0x1
	.string	"sum"
	.value	0x2ec
	.byte	0x14
	.long	0xca
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xa
	.quad	.LBB8
	.quad	.LBE8-.LBB8
	.uleb128 0x1
	.string	"k"
	.value	0x2ed
	.byte	0x16
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x11
	.long	.LASF49
	.value	0x2e0
	.quad	.LFB4875
	.quad	.LFE4875-.LFB4875
	.uleb128 0x1
	.byte	0x9c
	.long	0x536
	.uleb128 0x4
	.string	"mat"
	.value	0x2e0
	.byte	0x1b
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.long	.LASF42
	.value	0x2e0
	.byte	0x24
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.long	.LASF43
	.value	0x2e0
	.byte	0x2e
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xa
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0x1
	.string	"i"
	.value	0x2e1
	.byte	0xe
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.uleb128 0x1
	.string	"j"
	.value	0x2e2
	.byte	0x12
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x11
	.long	.LASF50
	.value	0x2da
	.quad	.LFB4874
	.quad	.LFE4874-.LFB4874
	.uleb128 0x1
	.byte	0x9c
	.long	0x5a0
	.uleb128 0x4
	.string	"mat"
	.value	0x2da
	.byte	0x1a
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.long	.LASF42
	.value	0x2da
	.byte	0x23
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x2
	.long	.LASF43
	.value	0x2da
	.byte	0x2d
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xa
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x1
	.string	"i"
	.value	0x2db
	.byte	0xe
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x11
	.long	.LASF51
	.value	0x29c
	.quad	.LFB4873
	.quad	.LFE4873-.LFB4873
	.uleb128 0x1
	.byte	0x9c
	.long	0x745
	.uleb128 0x4
	.string	"m"
	.value	0x29c
	.byte	0x1e
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x4
	.string	"n"
	.value	0x29d
	.byte	0x22
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x4
	.string	"k"
	.value	0x29e
	.byte	0x22
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x2
	.long	.LASF52
	.value	0x29f
	.byte	0x22
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x4
	.string	"A"
	.value	0x2a0
	.byte	0x23
	.long	0x260
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x2
	.long	.LASF53
	.value	0x2a1
	.byte	0x22
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x2
	.long	.LASF54
	.value	0x2a2
	.byte	0x22
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -116
	.uleb128 0x4
	.string	"B"
	.value	0x2a3
	.byte	0x23
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2
	.long	.LASF55
	.value	0x2a4
	.byte	0x22
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x2
	.long	.LASF56
	.value	0x2a5
	.byte	0x22
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x2
	.long	.LASF57
	.value	0x2a6
	.byte	0x22
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x4
	.string	"C"
	.value	0x2a7
	.byte	0x23
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 24
	.uleb128 0x2
	.long	.LASF58
	.value	0x2a8
	.byte	0x22
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 32
	.uleb128 0x2
	.long	.LASF59
	.value	0x2a9
	.byte	0x22
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 40
	.uleb128 0x1
	.string	"mb"
	.value	0x2ab
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1
	.string	"nb"
	.value	0x2ac
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1
	.string	"kb"
	.value	0x2ad
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1
	.string	"_mc"
	.value	0x2af
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1
	.string	"_nc"
	.value	0x2b0
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1
	.string	"_kc"
	.value	0x2b1
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x1
	.string	"mc"
	.value	0x2b3
	.byte	0x9
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x1
	.string	"nc"
	.value	0x2b3
	.byte	0xd
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1
	.string	"kc"
	.value	0x2b3
	.byte	0x11
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x1
	.string	"i"
	.value	0x2b4
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1
	.string	"j"
	.value	0x2b4
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1
	.string	"l"
	.value	0x2b4
	.byte	0xf
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x9
	.long	.LASF60
	.value	0x2b6
	.byte	0xc
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.uleb128 0x24
	.long	.LASF63
	.byte	0x1
	.value	0x260
	.byte	0x1
	.quad	.LFB4872
	.quad	.LFE4872-.LFB4872
	.uleb128 0x1
	.byte	0x9c
	.long	0x86e
	.uleb128 0x4
	.string	"mc"
	.value	0x260
	.byte	0x1c
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x4
	.string	"nc"
	.value	0x261
	.byte	0x1c
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x4
	.string	"kc"
	.value	0x262
	.byte	0x1c
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x2
	.long	.LASF52
	.value	0x263
	.byte	0x1c
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x2
	.long	.LASF57
	.value	0x264
	.byte	0x1c
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x4
	.string	"C"
	.value	0x265
	.byte	0x1d
	.long	0x265
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x2
	.long	.LASF58
	.value	0x266
	.byte	0x1c
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x2
	.long	.LASF59
	.value	0x267
	.byte	0x1c
	.long	0x66
	.uleb128 0x3
	.byte	0x91
	.sleb128 -108
	.uleb128 0x1
	.string	"mp"
	.value	0x269
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1
	.string	"np"
	.value	0x26a
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1
	.string	"_mr"
	.value	0x26c
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x1
	.string	"_nr"
	.value	0x26d
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1
	.string	"mr"
	.value	0x26f
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1
	.string	"nr"
	.value	0x26f
	.byte	0xd
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x1
	.string	"i"
	.value	0x270
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1
	.string	"j"
	.value	0x270
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x9
	.long	.LASF61
	.value	0x272
	.byte	0x13
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x9
	.long	.LASF62
	.value	0x273
	.byte	0x13
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x16
	.long	.LASF64
	.value	0x243
	.quad	.LFB4871
	.quad	.LFE4871-.LFB4871
	.uleb128 0x1
	.byte	0x9c
	.long	0x8fa
	.uleb128 0x4
	.string	"m"
	.value	0x243
	.byte	0x11
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x4
	.string	"n"
	.value	0x244
	.byte	0x11
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.long	.LASF52
	.value	0x245
	.byte	0x11
	.long	0xca
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x4
	.string	"X"
	.value	0x246
	.byte	0x12
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x2
	.long	.LASF65
	.value	0x247
	.byte	0x11
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x2
	.long	.LASF66
	.value	0x248
	.byte	0x11
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1
	.string	"i"
	.value	0x24a
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1
	.string	"j"
	.value	0x24a
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x16
	.long	.LASF67
	.value	0x223
	.quad	.LFB4870
	.quad	.LFE4870-.LFB4870
	.uleb128 0x1
	.byte	0x9c
	.long	0x9b2
	.uleb128 0x4
	.string	"m"
	.value	0x223
	.byte	0x17
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x4
	.string	"n"
	.value	0x224
	.byte	0x17
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x2
	.long	.LASF52
	.value	0x225
	.byte	0x17
	.long	0xca
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x4
	.string	"X"
	.value	0x226
	.byte	0x18
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x2
	.long	.LASF65
	.value	0x227
	.byte	0x17
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x2
	.long	.LASF66
	.value	0x228
	.byte	0x17
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x4
	.string	"Y"
	.value	0x229
	.byte	0x18
	.long	0x265
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x2
	.long	.LASF68
	.value	0x22a
	.byte	0x17
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x2
	.long	.LASF69
	.value	0x22b
	.byte	0x17
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1
	.string	"i"
	.value	0x22d
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1
	.string	"j"
	.value	0x22d
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x12
	.long	.LASF70
	.byte	0x88
	.quad	.LFB4869
	.quad	.LFE4869-.LFB4869
	.uleb128 0x1
	.byte	0x9c
	.long	0xa72
	.uleb128 0x7
	.string	"kc"
	.byte	0x88
	.byte	0x19
	.long	0x6d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x5
	.long	.LASF52
	.byte	0x89
	.byte	0x1b
	.long	0xca
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x7
	.string	"A"
	.byte	0x89
	.byte	0x30
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x7
	.string	"B"
	.byte	0x89
	.byte	0x41
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x5
	.long	.LASF57
	.byte	0x8a
	.byte	0x1b
	.long	0xca
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x7
	.string	"C"
	.byte	0x8b
	.byte	0x1c
	.long	0x265
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x5
	.long	.LASF58
	.byte	0x8b
	.byte	0x24
	.long	0x6d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x5
	.long	.LASF59
	.byte	0x8b
	.byte	0x32
	.long	0x6d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x5
	.long	.LASF61
	.byte	0x8c
	.byte	0x22
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x5
	.long	.LASF62
	.byte	0x8c
	.byte	0x37
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x8
	.string	"kb"
	.byte	0x8e
	.byte	0xa
	.long	0x6d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x8
	.string	"kl"
	.byte	0x8f
	.byte	0xa
	.long	0x6d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x12
	.long	.LASF71
	.byte	0x69
	.quad	.LFB4868
	.quad	.LFE4868-.LFB4868
	.uleb128 0x1
	.byte	0x9c
	.long	0xb12
	.uleb128 0x7
	.string	"kc"
	.byte	0x69
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x7
	.string	"nc"
	.byte	0x69
	.byte	0x14
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x7
	.string	"B"
	.byte	0x69
	.byte	0x26
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	.LASF55
	.byte	0x69
	.byte	0x2d
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x5
	.long	.LASF56
	.byte	0x69
	.byte	0x3a
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x5
	.long	.LASF72
	.byte	0x6a
	.byte	0x10
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x8
	.string	"np"
	.byte	0x6c
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x8
	.string	"_nr"
	.byte	0x6d
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x8
	.string	"i"
	.byte	0x6f
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x8
	.string	"j"
	.byte	0x6f
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x25
	.long	.LASF73
	.byte	0x1
	.byte	0x57
	.byte	0x1
	.quad	.LFB4867
	.quad	.LFE4867-.LFB4867
	.uleb128 0x1
	.byte	0x9c
	.long	0xb8b
	.uleb128 0x7
	.string	"k"
	.byte	0x57
	.byte	0xf
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x7
	.string	"B"
	.byte	0x57
	.byte	0x20
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	.LASF55
	.byte	0x57
	.byte	0x27
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x5
	.long	.LASF56
	.byte	0x57
	.byte	0x34
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x5
	.long	.LASF72
	.byte	0x58
	.byte	0x13
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x8
	.string	"i"
	.byte	0x5a
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x8
	.string	"j"
	.byte	0x5a
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x12
	.long	.LASF74
	.byte	0x38
	.quad	.LFB4866
	.quad	.LFE4866-.LFB4866
	.uleb128 0x1
	.byte	0x9c
	.long	0xc2b
	.uleb128 0x7
	.string	"mc"
	.byte	0x38
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x7
	.string	"kc"
	.byte	0x38
	.byte	0x14
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x7
	.string	"A"
	.byte	0x38
	.byte	0x26
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	.LASF53
	.byte	0x38
	.byte	0x2d
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x5
	.long	.LASF54
	.byte	0x38
	.byte	0x3a
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x5
	.long	.LASF72
	.byte	0x39
	.byte	0x10
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x8
	.string	"mp"
	.byte	0x3b
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x8
	.string	"_mr"
	.byte	0x3c
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x8
	.string	"i"
	.byte	0x3e
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x8
	.string	"j"
	.byte	0x3e
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x26
	.long	.LASF78
	.byte	0x1
	.byte	0x26
	.byte	0x1
	.quad	.LFB4865
	.quad	.LFE4865-.LFB4865
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x7
	.string	"k"
	.byte	0x26
	.byte	0xf
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x7
	.string	"A"
	.byte	0x26
	.byte	0x20
	.long	0x260
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x5
	.long	.LASF53
	.byte	0x26
	.byte	0x27
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x5
	.long	.LASF54
	.byte	0x26
	.byte	0x34
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x5
	.long	.LASF72
	.byte	0x27
	.byte	0x13
	.long	0x265
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x8
	.string	"i"
	.byte	0x29
	.byte	0x9
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x8
	.string	"j"
	.byte	0x29
	.byte	0xc
	.long	0x66
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 15
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x88
	.uleb128 0x21
	.sleb128 16
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 13
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x87
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF26:
	.string	"calloc"
.LASF20:
	.string	"_Float16"
.LASF13:
	.string	"clock_t"
.LASF51:
	.string	"dgemm_nn"
.LASF34:
	.string	"start_naive"
.LASF54:
	.string	"incColA"
.LASF56:
	.string	"incColB"
.LASF59:
	.string	"incColC"
.LASF7:
	.string	"short int"
.LASF9:
	.string	"size_t"
.LASF27:
	.string	"malloc"
.LASF67:
	.string	"dgeaxpy"
.LASF35:
	.string	"end_naive"
.LASF76:
	.string	"__PRETTY_FUNCTION__"
.LASF62:
	.string	"nextB"
.LASF66:
	.string	"incColX"
.LASF50:
	.string	"fill_matrix"
.LASF36:
	.string	"time_naive"
.LASF10:
	.string	"__clock_t"
.LASF78:
	.string	"pack_MRxk"
.LASF45:
	.string	"matches"
.LASF37:
	.string	"start_optimized"
.LASF14:
	.string	"time_t"
.LASF52:
	.string	"alpha"
.LASF75:
	.string	"GNU C17 13.2.0 -mtune=generic -march=x86-64 -g -fasynchronous-unwind-tables"
.LASF30:
	.string	"rand"
.LASF73:
	.string	"pack_kxNR"
.LASF22:
	.string	"free"
.LASF63:
	.string	"dgemm_macro_kernel"
.LASF49:
	.string	"print_matrix"
.LASF16:
	.string	"float"
.LASF3:
	.string	"unsigned int"
.LASF15:
	.string	"long long int"
.LASF17:
	.string	"long long unsigned int"
.LASF8:
	.string	"long int"
.LASF28:
	.string	"printf"
.LASF61:
	.string	"nextA"
.LASF74:
	.string	"pack_A"
.LASF19:
	.string	"long double"
.LASF4:
	.string	"unsigned char"
.LASF6:
	.string	"signed char"
.LASF42:
	.string	"rows"
.LASF25:
	.string	"time"
.LASF5:
	.string	"short unsigned int"
.LASF12:
	.string	"char"
.LASF46:
	.string	"main"
.LASF64:
	.string	"dgescal"
.LASF60:
	.string	"_beta"
.LASF32:
	.string	"C_naive"
.LASF33:
	.string	"C_optimized"
.LASF70:
	.string	"dgemm_micro_kernel"
.LASF39:
	.string	"time_optimized"
.LASF38:
	.string	"end_optimized"
.LASF72:
	.string	"buffer"
.LASF57:
	.string	"beta"
.LASF47:
	.string	"naive_matrix_multiply"
.LASF2:
	.string	"long unsigned int"
.LASF29:
	.string	"clock"
.LASF18:
	.string	"double"
.LASF43:
	.string	"cols"
.LASF11:
	.string	"__time_t"
.LASF48:
	.string	"size"
.LASF44:
	.string	"count"
.LASF21:
	.string	"__bf16"
.LASF40:
	.string	"mat1"
.LASF41:
	.string	"mat2"
.LASF53:
	.string	"incRowA"
.LASF55:
	.string	"incRowB"
.LASF58:
	.string	"incRowC"
.LASF77:
	.string	"compare_matrices"
.LASF69:
	.string	"incColY"
.LASF24:
	.string	"__assert_fail"
.LASF71:
	.string	"pack_B"
.LASF23:
	.string	"srand"
.LASF31:
	.string	"dgemm_kernel_asm"
.LASF65:
	.string	"incRowX"
.LASF68:
	.string	"incRowY"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"dgemm_nn.c"
.LASF1:
	.string	"/home/akiel/Desktop/trunk/github/pub/openGPMP/modules/linalg"
	.ident	"GCC: (Debian 13.2.0-9) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
