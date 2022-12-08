
CXX				= g++

pypath			= -I/usr/include/python3.10

API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/


swig_files		= arithmetic.i
run-swig:
	swig -c++ -python ${swig_files}

compile-ARITH:
	${CXX} -O2 -fPIC -c ${MOD_DIR}/arithmetic/arith.cpp

compile-ARITH-wrapper:
	${CXX} -O2 -fPIC -c arithmetic_wrap.cxx ${pypath}

compile-ARITH-lib:
	${CXX} -shared arith.o arithmetic_wrap.o -o _arithmetic.so

clean:
	rm -rf __pycache__
	rm -f *.o
	rm -f *.so
	rm -f *.cxx
	rm -f arithmetic.py

test:
	ls ${SRC_DIR}
	ls ${MOD_DIR}
	ls ${INC_DIR}

