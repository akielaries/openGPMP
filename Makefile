# ********** WARNING ********** 
# THIS MAKEFILE IS NOT A PART OF THE OFFICIAL INSTALLATION PROCESS SEE BELOW :
#
# This is the Makefile used to run the modules with their respective driver
# methods as well as corresponding unit tests done with Google's gtest. This
# Makefile is only important in testing and developing within this repository
# there are seperate files available for demonstrating how to create a Makefile
# for your own projects which are much more simple.



# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC			= gcc
CXX 		= g++ -std=c++20
VERBOSE 	= TRUE

CXX_DBG 	= -Wno-unused-result -Wsign-compare -DNDEBUG -g -O3 -Wall -Wextra
# CXX_THREAD	= -lpthread  
LIBXBGI		= /usr/lib/libXbgi.a
CXX_VIZ		=  -lX11 -lGL -lGLU -lglut -lm

OPM			= -lopenGPMP


SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR ARITHMETIC
AR			= $(SRCDIR)/arithmetic/arith.cpp
ARDRV		= $(PROJDIR)/samples/cpp/arithmetic.cpp
ARBIN		= arith

arith:
	${CXX} ${CXX_DBG} ${ARDRV} ${OPM} -o ${ARBIN}
	./${ARBIN}


# FILES FOR CALCULUS OPERATIONS
CALC		= $(SRCDIR)/calculus/deriv.cpp
CALCDRV		= $(PROJDIR)/samples/cpp/deriv.cpp
CALCBIN		= calc

calculus:
	${CXX} ${CXX_DBG} ${CALCDRV} ${OPM} -o ${CALCBIN}
	./${CALCBIN}


# FILES FOR THE MACHINE LEARNING MODULE
LR			= $(SRCDIR)/ml/linreg.cpp
LRDRV		= $(PROJDIR)/samples/cpp/reg.cpp
LRBIN		= lin_reg
MLP			= $(SRCDIR)/ml/mlp_network.cpp
MLPDRV		= $(PROJDIR)/samples/cpp/mlp.cpp
MLPBIN		= MLP

ml_dl:
	${CXX} ${CXX_DBG} ${LRDRV} ${OPM} -o ${LRBIN}
	./${LRBIN}
mlp:
	${CXX} ${CXX_DBG} ${MLP} ${MLPDRV} -o ${MLPBIN}
	./${MLPBIN}

# FILES FOR BASIC LINEAR ALGEBRA OPERATIONS
LINALG		= $(SRCDIR)/linalg/lao.cpp
LINALGDRV	= $(PROJDIR)/samples/cpp/linalg_ops.cpp
LINALGBIN	= linalg_ops

lin-alg:
	${CXX} ${CXX_DBG} ${LINALGDRV} ${OPM} -o ${LINALGBIN}
	./${LINALGBIN}


# FILES FOR NUMBER THEORY OPERATIONS AND ENCRYPTION 
PRIMES		= $(SRCDIR)/nt/prime_test.cpp
PRIMESDRV	= $(PROJDIR)/samples/cpp/prime_test.cpp
PRIMESBIN	= primes

CIPH		= $(SRCDIR)/nt/cipher.cpp
CIPHDRV		= $(PROJDIR)/samples/cpp/cipher.cpp
CIPHBIN		= cipher

RC2			= $(SRCDIR)/nt/rc2.cpp
RC2DRV		= $(PROJDIR)/samples/cpp/rc2.cpp
RC2BIN		= rc2

RC4			= $(SRCDIR)/nt/rc4.cpp
RC4DRV		= $(PROJDIR)/samples/cpp/rc4.cpp
RC4BIN		= rc4

RC5			= $(SRCDIR)/nt/rc5.cpp
RC5DRV		= $(PROJDIR)/samples/cpp/rc5.cpp
RC5BIN		= rc5

num-theory: 
	# PRIMES
	${CXX} ${CXX_DBG} ${PRIMESDRV} ${OPM} -o ${PRIMESBIN}
	./${PRIMESBIN}
	# BASIC STREAM CIPHERS
	${CXX} ${CXX_DBG} ${CIPHDRV} ${OPM} -o ${CIPHBIN}
	./${CIPHBIN}
	# RIVEST CIPHER ALGORITHMS, RC2, RC4, RC5, RC6
	${CXX} ${CXX_DBG} ${RC4DRV} ${OPM} -o ${RC4BIN}
	./${RC4BIN}

	#${CXX} ${RC5} ${RC5DRV} -o ${RC5BIN}
	#./${RC5BIN}


TORUS			= $(SRCDIR)/complex/torus.cpp
TORUS_ANIM		= $(SRCDIR)/complex/torus_animated.cpp
TORUSDRV		= $(PROJDIR)/samples/cpp/torus.cpp
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
	rm -f ${LINALGBIN}
	rm -f ${PRIMESBIN}
	rm -f ${RC4BIN}
	rm -f ${CIPHBIN}
	rm -f ${MLPBIN}

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
	gcovr

clean-tests:
	cd tests/ && rm -f *.gc* web/ openGPMP_tests
	rm -f ${TMEMBIN}
	rm -f ${TSARBIN}
	rm -f ${TCALCBIN}

clean-misc:
	cd pygpmp && rm -rf */*.cpp
	rm -rf build/ dist/ pygpmp.egg-info/ 
	find . -name "__pycache__" -type d -exec rm -r "{}" \;
	rm -rf __pycache__

openGPMP-docs:
	doxygen

