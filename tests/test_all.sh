#!/usr/bin/sh
# Utility script to test running openGPMP unit tests and generate coverage 
# files in openGPMP/.coverage

# test all modules together with googletest. produce ONE .info coverage
# file for the whole test suite. 
g++ -std=c++2a -march=native -Wno-unused-result -Wparentheses -Wsign-compare -DNDEBUG -g -O3 \
    -Wall --coverage \
    arith/t_arith.cpp ../modules/arithmetic/arith.cpp \
    calc/t_calc.cpp ../modules/calculus/differential.cpp \
    linalg/t_matrix.cpp ../modules/linalg/mtx.cpp
    nt/t_cipher.cpp ../modules/nt/cipher.cpp \
    nt/t_rc4.cpp ../modules/nt/rc4.cpp \
    nt/t_primes.cpp ../modules/nt/prime_test.cpp  ../modules/nt/prime_gen.cpp \
    nt/t_factorization.cpp ../modules/nt/factorization.cpp \
    nt/t_logarithms.cpp ../modules/nt/logarithms.cpp \
    core/t_threadpool.cpp \
    -lgtest -lgtest_main -o openGPMP_tests -fprofile-arcs -ftest-coverage -fPIC

# run compiled binary
./openGPMP_tests

#number_theory/t_rc4.cpp ../modules/number_theory/rc4.cpp \
# generate lcov files
lcov --directory . --capture --output-file lcov.info
# move lcov file to .coverage
mv lcov.info ../.coverage

# cd into root directory and run gcovr from here
cd ../ && gcovr --xml-pretty >> lcov.xml && mv lcov.xml .coverage/

