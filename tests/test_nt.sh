#!/usr/bin/sh

# test all modules together with googletest. produce ONE .info coverage
# file for the whole test suite. 
g++ --coverage \
    number_theory/t_rc4.cpp ../modules/number_theory/rc4.cpp \
    -lgtest -lgtest_main -o RM_tests -fprofile-arcs -ftest-coverage

# run compiled binary
./RM_tests

#number_theory/t_rc4.cpp ../modules/number_theory/rc4.cpp \
# generate lcov files
lcov --directory . --capture --output-file lcov.info

# move lcov file to .coverage
mv lcov.info ../.coverage


#rm -
#rm -f *.gc*
#rm -rf web/

