# This is the Makefile used to run the modules with their respective driver
# methods as well as corresponding unit tests done with Google's gtest. This
# Makefile is only important in testing and developing within this repository
# there are seperate files available for demonstrating how to create a Makefile
# for your own projects which are much more simple.


# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC			= gcc
CXX 		= g++
VERBOSE 	= TRUE

CXX_DBG 	= -Wall -Wextra -g
# CXX_THREAD	= -lpthread  
LIBXBGI		= /usr/lib/libXbgi.a
CXX_VIZ		=  -lX11 -lGL -lGLU -lglut -lm


SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR ARITHMETIC
AR			= $(SRCDIR)/arithmetic/arith.cpp
ARDRV		= $(PROJDIR)/drivers/d_arith.cpp
ARBIN		= arith

arith:
	${CXX} ${CXX_DBG} ${ARDRV} -o ${ARBIN}
	./${ARBIN}


# FILES FOR CALCULUS OPERATIONS
CALC		= $(SRCDIR)/calculus/deriv.cpp
CALCDRV		= $(PROJDIR)/drivers/calc/d_deriv.cpp
CALCBIN		= calc

calculus:
	${CXX} ${CXX_DBG} ${CALC} ${CALCDRV} -o ${CALCBIN}
	./${CALCBIN}


# FILES FOR REGRESSION
LR			= $(SRCDIR)/ML_DL/linreg.cpp
LRDRV		= $(PROJDIR)/drivers/ML_DL/d_reg.cpp
LRBIN		= lin_reg

lin-reg:
	${CXX} ${CXX_DBG} ${LR} ${LRDRV} -o ${LRBIN}
	./${LRBIN}


# FILES FOR BASIC LINEAR ALGEBRA OPERATIONS
BLA			= $(SRCDIR)/linalg/lao.cpp
BLADRV		= $(PROJDIR)/drivers/linalg/d_lao.cpp
BLABIN		= la_ops

lin-alg:
	${CXX} ${CXX_DBG} ${BLA} ${BLADRV} -o ${BLABIN}
	./${BLABIN}


# FILES FOR NUMBER THEORY OPERATIONS AND ENCRYPTION 
PRIMES		= $(SRCDIR)/number_theory/primes.cpp
PRIMESDRV	= $(PROJDIR)/drivers/number_theory/d_primes.cpp
PRIMESBIN	= primes

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

num-theory: 
	# PRIMES
	${CXX} ${CXX_DBG} ${AR} ${PRIMES} ${PRIMESDRV} -o ${PRIMESBIN}
	./${PRIMESBIN}
	# BASIC STREAM CIPHERS
	#${CXX} ${CXX_DBG} ${CIPH} ${CIPHDRV} -o ${CIPHBIN}
	#./${CIPHBIN}
	# RIVEST CIPHER ALGORITHMS, RC2, RC4, RC5, RC6
	#${CXX} ${CXX_DBG} ${RC4} ${RC4DRV} -o ${RC4BIN}
	#./${RC4BIN}

	#${CXX} ${RC5} ${RC5DRV} -o ${RC5BIN}
	#./${RC5BIN}


TORUS			= $(SRCDIR)/complex/torus.cpp
TORUS_ANIM		= $(SRCDIR)/complex/torus_animated.cpp
TORUSDRV		= $(PROJDIR)/drivers/complex/d_torus.cpp
TORUSBIN		= torus
TORUS_ANIM_BIN	= torus_anim

complex:
	# run regular 3D torus
	${CXX} ${TORUS} ${TORUSDRV} ${CXX_VIZ} -o ${TORUSBIN}
	./${TORUSBIN}
	# run animated torus
	${CXX} ${TORUS_ANIM} ${TORUSDRV} ${CXX_VIZ} - o ${TORUS_ANIM_BIN}
	./${TORUS_ANIM_BIN}


clean-mods:
	rm -f ${ARBIN}
	rm -f ${CALCBIN}
	rm -f ${LRBIN}
	rm -f ${BLABIN}
	rm -f ${PRIMESBIN}
	rm -f ${RC4BIN}
	rm -f ${CIPHBIN}

	#rm -f ${TORUSBIN}
	#rm -f ${TORUS_ANIM_BIN}
	#rm -f Mandelbrot

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
	${CXX} ${TMEM} ${GTFLAGS} -o ${TMEMBIN}
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

