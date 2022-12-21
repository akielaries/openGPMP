
run-swig:
	swig -c++ -fortran openMTPK.i

compile:
	g++ -c openMTPK_wrap.cxx

#ARITH   = ../../modules/arithmetic/arith.cpp
PRIMES  = ../../modules/number_theory/primes.cpp
CIPHER  = ../../modules/number_theory/cipher.cpp
RC4     = ../../modules/number_theory/rc4.cpp


link:
	g++ -c ${PRIMES} ${CIPHER} ${RC4} 

verify:
	gfortran -c openMTPK.f90 

clean-all:
	rm -f *.o *.cxx *.f90
	rm -f *.mod


