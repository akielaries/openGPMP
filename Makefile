# ********** WARNING ********** 
# THIS MAKEFILE IS NOT A PART OF THE OFFICIAL INSTALLATION PROCESS ONLY DEVEL


# define our project director
PROJDIR     = $(realpath $(CURDIR))

SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

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

clean-misc:
	cd pygpmp && rm -rf */*.cpp */*.so
	rm -rf build/ dist/ pygpmp.egg-info/ 
	find . -name "__pycache__" -type d -exec rm -r "{}" \;
	rm -rf __pycache__

openGPMP-docs:
	mkdir -p docs/doxygen/html/analysis
	mkdir -p docs/doxygen/html/testing
	doxygen
	cd docs/doxygen/html/analysis && \
		cppcheck --xml --xml-version=2 --enable=all --suppress=missingIncludeSystem \
		../../../../include/ ../../../../modules/ 2>analysis.xml && \
		cppcheck-htmlreport --source-dir=. --title=openGPMP --file=analysis.xml --report-dir=.
	genhtml .coverage/lcov.info --legend --output-directory docs/doxygen/html/testing
	#cp -r docs/analysis docs/doxygen/html

docs-analysis:
	mkdir -p docs/doxygen/html/analysis
	#mkdir -p docs/doxygen/html/testing
	cd docs/doxygen/html/analysis && \
        cppcheck --xml --xml-version=2 --enable=all --suppress=missingIncludeSystem \
        ../../../../include/ ../../../../modules/ 2>analysis.xml && \
        cppcheck-htmlreport --source-dir=. --title=openGPMP --file=analysis.xml --report-dir=.
	#genhtml .coverage/lcov.info --legend --output-directory docs/doxygen/html/testing
	#cp -r docs/analysis docs/doxygen/html

docs-testing:
	mkdir -p docs/doxygen/html/testing
	genhtml .coverage/lcov.info --legend --output-directory docs/doxygen/html/testing

clean-docs:
	rm -rf docs/doxygen
