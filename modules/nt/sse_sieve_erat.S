	.file	"seive_erat.cpp"
	.text
	.section	.rodata._ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_.str1.1,"aMS",@progbits,1
.LC0:
	.string	"vector::_M_realloc_insert"
	.section	.text._ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_,"axG",@progbits,_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_
	.type	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_, @function
_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_:
.LFB1335:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movabsq	$2305843009213693951, %rcx
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	8(%rdi), %r12
	movq	(%rdi), %r13
	movq	%r12, %rax
	subq	%r13, %rax
	sarq	$2, %rax
	cmpq	%rcx, %rax
	je	.L25
	movq	%rsi, %r15
	movq	%rdi, %rbp
	movq	%rsi, %r14
	subq	%r13, %r15
	cmpq	%r12, %r13
	je	.L26
	leaq	(%rax,%rax), %rcx
	cmpq	%rax, %rcx
	jb	.L16
	testq	%rcx, %rcx
	jne	.L27
	xorl	%ebx, %ebx
	xorl	%edi, %edi
.L7:
	movl	(%rdx), %eax
	leaq	4(%rdi,%r15), %rcx
	subq	%r14, %r12
	vmovq	%rdi, %xmm1
	movl	%eax, (%rdi,%r15)
	leaq	(%rcx,%r12), %rax
	vpinsrq	$1, %rax, %xmm1, %xmm0
	vmovdqa	%xmm0, (%rsp)
	testq	%r15, %r15
	jg	.L28
	testq	%r12, %r12
	jle	.L11
	movq	%r12, %rdx
	movq	%r14, %rsi
	movq	%rcx, %rdi
	call	memcpy@PLT
.L11:
	testq	%r13, %r13
	jne	.L10
.L13:
	movq	%rbx, 16(%rbp)
	vmovdqa	(%rsp), %xmm2
	vmovdqu	%xmm2, 0(%rbp)
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L16:
	.cfi_restore_state
	movabsq	$9223372036854775804, %rbx
.L6:
	movq	%rbx, %rdi
	movq	%rdx, (%rsp)
	call	_Znwm@PLT
	movq	(%rsp), %rdx
	movq	%rax, %rdi
	addq	%rax, %rbx
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L28:
	movq	%r15, %rdx
	movq	%r13, %rsi
	movq	%rcx, 24(%rsp)
	call	memmove@PLT
	testq	%r12, %r12
	jg	.L29
.L10:
	movq	16(%rbp), %rsi
	movq	%r13, %rdi
	subq	%r13, %rsi
	call	_ZdlPvm@PLT
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L26:
	addq	$1, %rax
	jc	.L16
	movabsq	$2305843009213693951, %rcx
	cmpq	%rcx, %rax
	movq	%rcx, %rbx
	cmovbe	%rax, %rbx
	salq	$2, %rbx
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L29:
	movq	24(%rsp), %rdi
	movq	%r14, %rsi
	movq	%r12, %rdx
	call	memcpy@PLT
	movq	16(%rbp), %rsi
	movq	%r13, %rdi
	subq	%r13, %rsi
	call	_ZdlPvm@PLT
	jmp	.L13
.L27:
	movabsq	$2305843009213693951, %rax
	cmpq	%rax, %rcx
	cmova	%rax, %rcx
	leaq	0(,%rcx,4), %rbx
	jmp	.L6
.L25:
	leaq	.LC0(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE1335:
	.size	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_, .-_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_
	.section	.text._ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv,"axG",@progbits,_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv
	.type	_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv, @function
_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv:
.LFB1355:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L35
	movq	32(%rbx), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	movq	$0, (%rbx)
	movl	$0, 8(%rbx)
	movq	$0, 16(%rbx)
	movl	$0, 24(%rbx)
	movq	$0, 32(%rbx)
.L35:
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1355:
	.size	_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv, .-_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4
	.globl	_Z19sieveOfEratosthenesi
	.type	_Z19sieveOfEratosthenesi, @function
_Z19sieveOfEratosthenesi:
.LFB1253:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1253
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	leal	1(%rsi), %r12d
	movslq	%r12d, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$64, %rsp
	.cfi_def_cfa_offset 112
	movq	$0, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	testq	%r12, %r12
	jne	.L38
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, 16(%rdi)
	vmovdqu	%xmm0, (%rdi)
	andq	$-4, 0
.L37:
	addq	$64, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L38:
	.cfi_restore_state
	leaq	63(%r12), %r13
	movl	%esi, %ebx
	shrq	$6, %r13
	salq	$3, %r13
	movq	%r13, %rdi
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	movq	%rax, %rdi
	leaq	(%rax,%r13), %rax
	testq	%r12, %r12
	movl	$0, 24(%rsp)
	movq	%rax, 48(%rsp)
	leaq	63(%r12), %rax
	cmovns	%r12, %rax
	movq	%rdi, 16(%rsp)
	sarq	$6, %rax
	leaq	(%rdi,%rax,8), %rdx
	movq	%r12, %rax
	sarq	$63, %rax
	shrq	$58, %rax
	addq	%rax, %r12
	andl	$63, %r12d
	subq	%rax, %r12
	js	.L75
.L40:
	movq	%rdx, 32(%rsp)
	movl	$-1, %esi
	movq	%r13, %rdx
	movl	%r12d, 40(%rsp)
	call	memset@PLT
	vpxor	%xmm0, %xmm0, %xmm0
	movq	$0, 16(%rbp)
	movl	$3, %esi
	movq	%rax, %rdi
	movq	(%rax), %rax
	vmovdqu	%xmm0, 0(%rbp)
	movl	$4, %edx
	movl	$1, %r9d
	andq	$-4, %rax
	movq	%rax, (%rdi)
	cmpl	$3, %ebx
	jg	.L41
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L47:
	movl	%esi, %edx
	imull	%esi, %edx
	cmpl	%ebx, %edx
	jg	.L77
.L45:
	movq	%rsi, %rax
	incq	%rsi
	sarq	$6, %rax
	movq	(%rdi,%rax,8), %rax
.L41:
	leal	-1(%rsi), %r8d
	shlx	%r8, %r9, %rcx
	testq	%rax, %rcx
	je	.L47
	cmpl	%edx, %ebx
	jl	.L47
	.p2align 4,,10
	.p2align 3
.L50:
	movslq	%edx, %rax
	testq	%rax, %rax
	leaq	63(%rax), %rcx
	movq	%rax, %r10
	cmovns	%rax, %rcx
	sarq	$63, %r10
	shrq	$58, %r10
	addq	%r10, %rax
	sarq	$6, %rcx
	andl	$63, %eax
	leaq	(%rdi,%rcx,8), %rcx
	subq	%r10, %rax
	js	.L78
	shlx	%rax, %r9, %rax
	addl	%r8d, %edx
	notq	%rax
	andq	%rax, (%rcx)
	cmpl	%edx, %ebx
	jge	.L50
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L78:
	addq	$64, %rax
	addl	%r8d, %edx
	shlx	%rax, %r9, %rax
	notq	%rax
	andq	%rax, -8(%rcx)
	cmpl	%edx, %ebx
	jge	.L50
	movl	%esi, %edx
	imull	%esi, %edx
	cmpl	%ebx, %edx
	jle	.L45
	.p2align 4,,10
	.p2align 3
.L77:
	movl	$2, 12(%rsp)
.L51:
	movl	$2, %r12d
	movl	$1, %r14d
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L54:
	incl	%r13d
	incq	%r12
	movl	%r13d, 12(%rsp)
	cmpl	%r12d, %ebx
	jl	.L79
.L57:
	movq	%r12, %rdx
	shlx	%r12, %r14, %rax
	movl	%r12d, %r13d
	sarq	$6, %rdx
	andq	(%rdi,%rdx,8), %rax
	je	.L54
	movq	8(%rbp), %rsi
	cmpq	16(%rbp), %rsi
	je	.L55
	movl	%r12d, (%rsi)
	incl	%r13d
	addq	$4, %rsi
	incq	%r12
	movq	%rsi, 8(%rbp)
	movl	%r13d, 12(%rsp)
	cmpl	%r12d, %ebx
	jge	.L57
.L79:
	testq	%rdi, %rdi
	je	.L37
.L52:
	movq	48(%rsp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	addq	$64, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L55:
	.cfi_restore_state
	leaq	12(%rsp), %rdx
	movq	%rbp, %rdi
.LEHB1:
	call	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_
.LEHE1:
	movq	16(%rsp), %rdi
	jmp	.L54
.L75:
	addq	$64, %r12
	subq	$8, %rdx
	jmp	.L40
.L76:
	movl	$2, 12(%rsp)
	cmpl	$1, %ebx
	jg	.L51
	jmp	.L52
.L61:
	movq	%rax, %rbx
	jmp	.L58
.L62:
	movq	%rax, %rbx
	jmp	.L43
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1253:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1253-.LLSDACSB1253
.LLSDACSB1253:
	.uleb128 .LEHB0-.LFB1253
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L62-.LFB1253
	.uleb128 0
	.uleb128 .LEHB1-.LFB1253
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L61-.LFB1253
	.uleb128 0
.LLSDACSE1253:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC1253
	.type	_Z19sieveOfEratosthenesi.cold, @function
_Z19sieveOfEratosthenesi.cold:
.LFSB1253:
.L58:
	.cfi_def_cfa_offset 112
	.cfi_offset 3, -48
	.cfi_offset 6, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	.cfi_offset 14, -16
	movq	0(%rbp), %rdi
	movq	16(%rbp), %rsi
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	jne	.L80
	vzeroupper
.L59:
	leaq	16(%rsp), %rdi
	call	_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv
	movq	%rbx, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.L43:
	leaq	16(%rsp), %rdi
	vzeroupper
	call	_ZNSt13_Bvector_baseISaIbEE13_M_deallocateEv
	movq	%rbx, %rdi
	call	_Unwind_Resume@PLT
.LEHE2:
.L80:
	vzeroupper
	call	_ZdlPvm@PLT
	jmp	.L59
	.cfi_endproc
.LFE1253:
	.section	.gcc_except_table
.LLSDAC1253:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC1253-.LLSDACSBC1253
.LLSDACSBC1253:
	.uleb128 .LEHB2-.LCOLDB1
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSEC1253:
	.section	.text.unlikely
	.text
	.size	_Z19sieveOfEratosthenesi, .-_Z19sieveOfEratosthenesi
	.section	.text.unlikely
	.size	_Z19sieveOfEratosthenesi.cold, .-_Z19sieveOfEratosthenesi.cold
.LCOLDE1:
	.text
.LHOTE1:
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (Debian 13.2.0-13) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
