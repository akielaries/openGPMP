# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= g++
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g

SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR ARITHMETIC
AR			= $(SRCDIR)/basics/RM_arith.cpp
ARDRV		= $(PROJDIR)/drivers/d_arith.cpp
ARBIN		= arith
# FILES FOR CALCULUS OPERATIONS
CALC		= $(SRCDIR)/calculus/RM_deriv.cpp
CALCDRV		= $(PROJDIR)/drivers/calc/d_deriv.cpp
CALCBIN		= calc
# FILES FOR REGRESSION
LR			= $(SRCDIR)/regression/RM_linreg.cpp
LRDRV		= $(PROJDIR)/drivers/d_reg.cpp
LRBIN		= lin_reg
# FILES FOR BASIC LINEAR ALGEBRA OPERATIONS
BLA			= $(SRCDIR)/LINALG/RM_lao.cpp
BLADRV		= $(PROJDIR)/drivers/d_lao.cpp
BLABIN		= la_ops

# FILES FOR NUMBER THEORY OPERATIONS AND ENCRYPTION 
CIPH		= $(SRCDIR)/number_theory/RM_cipher.cpp
CIPHDRV	= $(PROJDIR)/drivers/number_theory/d_cipher.cpp
CIPHBIN	= cipher

RC2			= $(SRCDIR)/number_theory/RM_rc2.cpp
RC2DRV		= $(PROJDIR)/drivers/number_theory/d_rc2.cpp
RC2BIN		= rc2

RC4			= $(SRCDIR)/number_theory/RM_rc4.cpp
RC4DRV		= $(PROJDIR)/drivers/number_theory/d_rc4.cpp
RC4BIN		= rc4

RC5			= $(SRCDIR)/number_theory/RM_rc5.cpp
RC5DRV		= $(PROJDIR)/drivers/number_theory/d_rc5.cpp
RC5BIN		= rc5

LIBDIR		= $(PROJDIR)/include


arith:
	${CC} ${ARDRV} -o ${ARBIN}
	./${ARBIN}

calculus:
	${CC} ${CALC} ${CALCDRV} -o ${CALCBIN}
	./${CALCBIN}

lin-reg:
	${CC} ${LR} ${LRDRV} -o ${LRBIN}
	./${LRBIN}

la-ops:
	${CC} ${BLA} ${BLADRV} -o ${BLABIN}
	./${BLABIN}

num-theory: 
	# RIVEST CIPHER ALGORITHMS, RC2, RC4, RC5, RC6
	${CC} ${RC4} ${RC4DRV} -o ${RC4BIN}
	./${RC4BIN}

	${CC} ${RC5} ${RC5DRV} -o ${RC5BIN}
	./${RC5BIN}

	${CC} ${CIPH} ${CIPHDRV} -o ${CIPHBIN}
	./${CIPHBIN}

clean-mods:
	rm -f ${ARBIN}
	rm -f ${CALCBIN}
	rm -f ${LRBIN}
	rm -f ${BLABIN}
	rm -f ${RC4BIN}
	rm -f ${CIPHBIN}

# testing created modules
# test arith
TSARDRV		= $(PROJDIR)/tests/t_arith.cpp
TSARBIN		= t_arith

test-arith:
	${CC} ${TSARDRV} -o ${TSARBIN}
	./${TSARBIN}

clean-tests:
	rm -f ${}

