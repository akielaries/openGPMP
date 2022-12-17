
ARITH	= ../../modules/arithmetic/arith.cpp
PRIMES	= ../../modules/number_theory/primes.cpp
CIPHER	= ../../modules/number_theory/cipher.cpp
RC4		= ../../modules/number_theory/rc4.cpp

r-swig:
	swig -c++ -r -o openMTPK_wrap.cpp openMTPK.i
	R CMD SHLIB -o openMTPK.so openMTPK_wrap.cpp ${ARITH} ${PRIMES} ${CIPHER} ${RC4}


clean:
	rm -rf *.cmo
	rm -rf *.cmi
	rm -rf example

clean-all:
	rm -rf *.o
	rm -rf *.so
	rm -rf *.R *.cpp

