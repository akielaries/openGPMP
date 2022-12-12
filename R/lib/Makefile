
ARITH	= ../../modules/arithmetic/arith.cpp
PRIMES	= ../../modules/number_theory/primes.cpp
CIPHER	= ../../modules/number_theory/cipher.cpp
RC4		= ../../modules/number_theory/rc4.cpp

r-swig:
	swig -c++ -r -o RM_pkg_wrap.cpp RM_pkg.i
	R CMD SHLIB -o RM_pkg.so ${ARITH} ${PRIMES} ${CIPHER} ${RC4}


clean:
	rm -rf *.cmo
	rm -rf *.cmi
	rm -rf example
clean-all:
	rm -rf *.o
	rm -rf *.so
	rm -rf *.R *.cpp

