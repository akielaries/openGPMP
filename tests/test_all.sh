#!/usr/bin/sh

# test all modules together with googletest. produce ONE .info coverage
# file for the whole test suite. 
g++ --coverage arith/t_arith.cpp ../modules/arithmetic/arith.cpp \
    calc/t_calc.cpp ../modules/calculus/deriv.cpp \
    number_theory/t_cipher.cpp ../modules/number_theory/cipher.cpp \
    number_theory/t_rc4.cpp ../modules/number_theory/rc4.cpp \
    -lgtest -lgtest_main -o RM_tests -fprofile-arcs -ftest-coverage -fPIC

# run compiled binary
./RM_tests

#number_theory/t_rc4.cpp ../modules/number_theory/rc4.cpp \
# generate lcov files
lcov --directory . --capture --output-file lcov.txt
# move lcov file to .coverage
mv lcov.txt ../.coverage

# cd into root directory and run gcovr from here
cd ../ && gcovr --xml-pretty >> lcov.xml && mv lcov.xml .coverage/

#rm -
#rm -f *.gc*
#rm -rf web/

