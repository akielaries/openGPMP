
CXX				= g++
CXX_DBG     	= -Wall -Wextra -g

pypath			= -I/usr/include/python3.10

API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/


swig_files		= RM_pkg.i
run-swig:
	swig -c++ -python ${swig_files}


primes 			= $(MOD_DIR)/number_theory/primes.cpp
arith			= $(MOD_DIR)/arithmetic/arith.cpp
compile:
	${CXX} ${CXX_DBG} -O2 -fPIC -c ${arith} ${primes}

compile-wrapper:
	${CXX} ${CXX_DBG} -O2 -fPIC -c RM_pkg_wrap.cxx ${pypath}


compile-lib:
	${CXX} ${CXX_DBG} -shared arith.o primes.o RM_pkg_wrap.o -o _RM_pkg.so


clean:
	rm -rf __pycache__
	rm -f *.o
	rm -f *.cxx

test:
	ls ${SRC_DIR}
	ls ${MOD_DIR}
	ls ${INC_DIR}

