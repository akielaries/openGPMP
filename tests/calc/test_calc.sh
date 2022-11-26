#!/usr/bin/sh

# TESTS ON MODULES WILL BE DONE INDIVIDUALLY FOR STATUS ON UNIT TESTING FOR
# EACH MODULE + TOGETHER AS A WHOLE TO GENERATE THE CODE COVERAGE REPORT

# testing calculus operations using shell scripts. each module with respective
# test scripts will be ran from the root directories Makefile

# run the test + generate coverage files
g++ t_calc.cpp ../../modules/calculus/deriv.cpp -lgtest -o t_calc -fprofile-arcs -ftest-coverage

./t_calc

# more coverage files
gcov t_calc.cpp
lcov --capture --directory . --output-file calc_cov.info

# generate HTML page
genhtml calc_cov.info --output-directory web

# open HTML
open web/index.html

# move .info file to .coverage/
mv calc_cov.info ../../.coverage

# remove binaries and generated files needed for coverage report
rm -f t_calc
rm -f *.gc*

#rm -rf web/

