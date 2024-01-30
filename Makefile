# ********** WARNING ********** 
# THIS MAKEFILE IS NOT A PART OF THE OFFICIAL INSTALLATION PROCESS ONLY DEVEL


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
	cd pygpmp && rm -rf */*.cpp */*.so
	rm -rf build/ dist/ pygpmp.egg-info/ 
	find . -name "__pycache__" -type d -exec rm -r "{}" \;
	rm -rf __pycache__

openGPMP-docs:
	doxygen
	cd docs/analysis && \
		cppcheck --xml --xml-version=2 --enable=all --suppress=missingIncludeSystem \
		../../include/ ../../modules/ 2>analysis.xml && \
		cppcheck-htmlreport --source-dir=docs/analysis --title=openGPMP --file=analysis.xml --report-dir=.
	cp -r docs/analysis docs/doxygen/html

docs-analysis:
	cd docs/analysis && \
		cppcheck --xml --xml-version=2 --enable=all --suppress=missingIncludeSystem \
		../../include/ ../../modules/ 2>analysis.xml && \
		cppcheck-htmlreport --source-dir=docs/analysis --title=openGPMP --file=analysis.xml --report-dir=.
	cp -r docs/analysis docs/doxygen/html

docs-testcov:
	cd .coverage && ./genhtml


clean-docs:
	rm -rf docs/doxygen docs/analysis/*.html
