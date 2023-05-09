	.file	"dis_add.cpp"
	.text
.Ltext0:
	.file 0 "/home/akiel/Desktop/Trunk/github/public-repos/OSS/openMTPK/experiment/CPU" "dis_add.cpp"
	.p2align 4
	.globl	_Z3addii
	.type	_Z3addii, @function
_Z3addii:
.LVL0:
.LFB0:
	.file 1 "dis_add.cpp"
	.loc 1 1 23 view -0
	.cfi_startproc
	.loc 1 2 5 view .LVU1
	.loc 1 2 16 is_stmt 0 view .LVU2
	leal	(%rdi,%rsi), %eax
	.loc 1 3 1 view .LVU3
	ret
	.cfi_endproc
.LFE0:
	.size	_Z3addii, .-_Z3addii
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x6d
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0x2
	.long	.LASF2
	.byte	0x21
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x3
	.string	"add"
	.byte	0x1
	.byte	0x1
	.byte	0x5
	.long	.LASF3
	.long	0x69
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x69
	.uleb128 0x1
	.string	"a"
	.byte	0xd
	.long	0x69
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.string	"b"
	.byte	0x14
	.long	0x69
	.uleb128 0x1
	.byte	0x54
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
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
	.uleb128 0x3
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x4
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
.LASF2:
	.string	"GNU C++17 12.2.0 -mtune=generic -march=x86-64 -g -O2 -fasynchronous-unwind-tables"
.LASF3:
	.string	"_Z3addii"
	.section	.debug_line_str,"MS",@progbits,1
.LASF0:
	.string	"dis_add.cpp"
.LASF1:
	.string	"/home/akiel/Desktop/Trunk/github/public-repos/OSS/openMTPK/experiment/CPU"
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
