
CXX				= g++

pypath			= -I/usr/include/python3.10

API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/


swig_files		= number_theory.i
run-swig:
	swig -c++ -python ${swig_files}

compile-NM:
	${CXX} -O2 -fPIC -c ${MOD_DIR}/number_theory/primes.cpp

compile-NM-wrapper:
	${CXX} -O2 -fPIC -c number_theory_wrap.cxx ${pypath}

compile-NM-lib:
	${CXX} -shared primes.o number_theory_wrap.o -o _number_theory.so

clean:
	rm -rf __pycache__
	rm -f *.o
	rm -f *.so
	rm -f *.cxx
	rm -f number_theory.py

test:
	ls ${SRC_DIR}
	ls ${MOD_DIR}
	ls ${INC_DIR}

