
CXX				= g++
CXX_DBG     	= -Wall -Wextra -g

pypath			= -I/usr/include/python3.10

API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/


swig_files		= openMTPK.i
run-swig:
	swig -c++ -python ${swig_files}


primes 			= $(MOD_DIR)/number_theory/primes.cpp
arith			= $(MOD_DIR)/arithmetic/arith.cpp
cipher			= $(MOD_DIR)/number_theory/cipher.cpp
rc4				= $(MOD_DIR)/number_theory/rc4.cpp
compile:
	${CXX} ${CXX_DBG} -O2 -fPIC -c ${arith} ${primes} ${cipher} ${rc4}

compile-wrapper:
	${CXX} ${CXX_DBG} -O2 -fPIC -c openMTPK_wrap.cxx ${pypath}

PKG		= _openMTPK.so
compile-lib:
	${CXX} ${CXX_DBG} -shared arith.o primes.o cipher.o rc4.o openMTPK_wrap.o -o ${PKG}
	mv ${PKG} openMTPK.py examples/

clean:
	rm -rf */__pycache__
	rm -f *.o
	rm -f *.cxx

test:
	ls ${SRC_DIR}
	ls ${MOD_DIR}
	ls ${INC_DIR}

