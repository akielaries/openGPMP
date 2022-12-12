
CXX				= g++
CXX_DBG     	= -Wall -Wextra -g

pypath			= -I/usr/include/python3.10

API_DIR			= $(realpath $(CURDIR))
SRC_DIR			= $(API_DIR)/../
MOD_DIR			= $(SRC_DIR)/modules/
INC_DIR			= $(SRC_DIR)/include/

swig_files		= RM_pkg.i
run-swig:
	swig -c++ -ocaml -co swigp4.ml
	swig -c++ -ocaml ${swig_files}
	for file in swig.mli swig.ml swigp4.ml ; do swig -ocaml -co $$file ; done
	swig -ocaml -co swig.mli ; swig -ocaml -co swig.ml
	ocamlc -c swig.mli ; ocamlc -c swig.ml
	ocamlc -I `camlp4 -where` -pp 'camlp4o pa_extend.cmo q_MLast.cmo' -c swigp4.ml
	cp RM_pkg_wrap.cxx RM_pkg_wrap.c
	ocamlc -c -ccopt -xc++ RM_pkg_wrap.c
	ocamlc -c RM_pkg.mli
	ocamlc -c RM_pkg.ml

primes 			= $(MOD_DIR)/number_theory/primes.cpp
arith			= $(MOD_DIR)/arithmetic/arith.cpp
cipher			= $(MOD_DIR)/number_theory/cipher.cpp
rc4				= $(MOD_DIR)/number_theory/rc4.cpp
compile:
	${CXX} ${CXX_DBG} -O2 -fPIC -c ${arith} ${primes} ${cipher} ${rc4}

compile-wrapper:
	${CXX} ${CXX_DBG} -O2 -fPIC -c RM_pkg_wrap.cxx ${pypath}

PKG		= _RM_pkg.so
compile-lib:
	${CXX} ${CXX_DBG} -shared arith.o primes.o cipher.o rc4.o RM_pkg_wrap.o -o ${PKG}
	mv ${PKG} RM_pkg.py examples/

clean:
	rm -f *.o
	rm -f *.cmo
	rm -f *.cmi

test:
	ls ${SRC_DIR}
	ls ${MOD_DIR}
	ls ${INC_DIR}

