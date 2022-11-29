# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= g++ -lpthread -fopenmp
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g

SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR ARITHMETIC
AR			= $(SRCDIR)/basics/arith.cpp
ARDRV		= $(PROJDIR)/drivers/d_arith.cpp
ARBIN		= arith
# FILES FOR CALCULUS OPERATIONS
CALC		= $(SRCDIR)/calculus/deriv.cpp
CALCDRV		= $(PROJDIR)/drivers/calc/d_deriv.cpp
CALCBIN		= calc
# FILES FOR REGRESSION
LR			= $(SRCDIR)/ML_DL/linreg.cpp
LRDRV		= $(PROJDIR)/drivers/d_reg.cpp
LRBIN		= lin_reg
# FILES FOR BASIC LINEAR ALGEBRA OPERATIONS
BLA			= $(SRCDIR)/LINALG/lao.cpp
BLADRV		= $(PROJDIR)/drivers/d_lao.cpp
BLABIN		= la_ops

# FILES FOR NUMBER THEORY OPERATIONS AND ENCRYPTION 
CIPH		= $(SRCDIR)/number_theory/cipher.cpp
CIPHDRV		= $(PROJDIR)/drivers/number_theory/d_cipher.cpp
CIPHBIN		= cipher

RC2			= $(SRCDIR)/number_theory/rc2.cpp
RC2DRV		= $(PROJDIR)/drivers/number_theory/d_rc2.cpp
RC2BIN		= rc2

RC4			= $(SRCDIR)/number_theory/rc4.cpp
RC4DRV		= $(PROJDIR)/drivers/number_theory/d_rc4.cpp
RC4BIN		= rc4

RC5			= $(SRCDIR)/number_theory/rc5.cpp
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
	# BASIC STREAM CIPHERS
	#${CC} ${CIPH} ${CIPHDRV} -o ${CIPHBIN}
	#./${CIPHBIN}
	# RIVEST CIPHER ALGORITHMS, RC2, RC4, RC5, RC6
	${CC} ${RC4} ${RC4DRV} -o ${RC4BIN}
	./${RC4BIN}

	#${CC} ${RC5} ${RC5DRV} -o ${RC5BIN}
	#./${RC5BIN}

complex:
	${CC} modules/complex/Mandelbrot.cpp /usr/lib/libXbgi.a -lX11 -lm -std=c++0x -o Mandelbrot
	./Mandelbrot

clean-mods:
	rm -f ${ARBIN}
	rm -f ${CALCBIN}
	rm -f ${LRBIN}
	rm -f ${BLABIN}
	rm -f ${RC4BIN}
	rm -f ${CIPHBIN}
	rm -f Mandelbrot

# testing created modules
# using gtest
GTFLAGS		= -pthread -lgtest 

GCOV		= gcov
LCOV		= lcov
GCOVFLAGS	= -fprofile-arcs -ftest-coverage
LCOVFLAGS1	= --capture --directory 
LCOVFLAGS2	= --output-file

COVDIR		= $(PROJDIR)/.coverage
COVREPORT	= lcov.info
STORE_COV	= $(addprefix $(COVDIR), $(COVREPORT))

# clean these coverage files
GCDALEFTOVERS	= $(shell find $(PROJDIR) -name '*.gcda')
GCNOLEFTOVERS	= $(shell find $(PROJDIR) -name '*.gcno')
GCOVLEFTOVERS	= $(shell find $(PROJDIR) -name '*.gcov')

GENREPORT	= genhtml
GENFLAGS	= --output-directory

VG			= valgrind
VGFLAGS		= --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck

TMEM		= $(PROJDIR)/tests/misc/t_memleak.cpp
TMEMBIN		= t_memleak

# test arith
TSARDIR		= $(PROJDIR)/tests/arith
TSARDRV		= $(PROJDIR)/tests/arith/t_arith.cpp
TSARBIN		= t_arith


# testing memory
test-gtest: 
	${CC} ${TMEM} ${GTFLAGS} -o ${TMEMBIN}
	./${TMEMBIN}

# test memory leaks of generated module binaries
test-leaks: 
	${VG} ${VGFLAGS} ./${TMEMBIN}

run-tests:
	cd tests/ && sh -x test_all.sh

clean-tests:
	cd tests/ && rm -f *.gc* web/ RM_tests
	rm -f ${TMEMBIN}
	rm -f ${TSARBIN}
	rm -f ${TCALCBIN}

