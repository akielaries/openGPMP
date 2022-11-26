#!/usr/bin/sh

# TESTS ON MODULES WILL BE DONE INDIVIDUALLY FOR STATUS ON UNIT TESTING FOR
# EACH MODULE + TOGETHER AS A WHOLE TO GENERATE THE CODE COVERAGE REPORT

# testing calculus operations using shell scripts. each module with respective
# test scripts will be ran from the root directories Makefile

# run the test + generate coverage files
g++ t_arith.cpp -lgtest -o t_arith -fprofile-arcs -ftest-coverage

./t_arith

# more coverage files
gcov t_arith.cpp
lcov --capture --directory . --output-file arith_cov.info

# generate HTML page
# genhtml arith_cov.info --output-directory web

# open HTML
# open web/index.html

# move .info file to .coverage/
mv arith_cov.info ../../.coverage
# remove binaries and generated files needed for coverage report
rm -f t_arith
rm -f *.gc*

#rm -rf web/

