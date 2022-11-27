#!/usr/bin/sh

# test all modules together with googletest. produce ONE .info coverage
# file for the whole test suite. 
g++ --coverage arith/t_arith.cpp ../modules/basics/arith.cpp \
    calc/t_calc.cpp ../modules/calculus/deriv.cpp \
    -lgtest -lgtest_main -o RM_tests -fprofile-arcs -ftest-coverage

# generate lcov files
lcov --directory . --capture --output-file lcov.info

# move lcov file to .coverage
mv lcov.info ../.coverage

#rm -
#rm -f *.gc*
#rm -rf web/

