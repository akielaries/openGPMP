.globl func

.type func @function

func:
    .cfi_startproc
    movl $7 %eax
    ret
    .cfi_endproc

