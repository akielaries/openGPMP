# UNIT TESTS
CXX 		= g++
CXXFLAGS 	= -std=c++2a -march=native -Wno-unused-result -Wparentheses \
			  -Wsign-compare -DNDEBUG -g -Wall --coverage -fprofile-arcs \
			  -ftest-coverage -fPIC
LIBS 		= -lgtest -lgtest_main

SRCDIR 		= ../modules

ARITH		= $(SRCDIR)/arithmetic
CALC		= $(SRCDIR)/calculus
CMPLX		= $(SRCDIR)/complex
CORE		= $(SRCDIR)/core
LINALG		= $(SRCDIR)/linalg
NT			= $(SRCDIR)/nt
ML			= $(SRCDIR)/ml

T_ARITH		= arith
T_CALC		= calc
T_CMPLX		= complex
T_CORE		= core
T_LINALG	= linalg
T_ML		= ml
T_NT		= nt

SRCS		= $(ARITH)/arith.cpp $(T_ARITH)/t_arith.cpp \
			  $(CALC)/differential.cpp $(T_CALC)/t_calc.cpp \
			  $(LINALG)/mtx.cpp $(T_LINALG)/t_matrix.cpp \
			  $(NT)/cipher.cpp $(T_NT)/t_cipher.cpp \
			  $(NT)/rc4.cpp $(T_NT)/t_rc4.cpp \
			  $(NT)/prime_test.cpp $(NT)/prime_gen.cpp $(T_NT)/t_primes.cpp \
			  $(NT)/factorization.cpp $(T_NT)/t_factorization.cpp \
			  $(NT)/logarithms.cpp $(T_NT)/t_logarithms.cpp \
			  $(NT)/random.cpp $(T_NT)/t_random.cpp \
			  $(T_CORE)/t_threadpool.cpp

BIN = openGPMP_tests

all: $(BIN)

$(BIN): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LIBS) -o $(BIN)

run: $(BIN)
	./$(BIN)

coverage: run
	lcov --directory . --capture --output-file lcov.info
	mv lcov.info ../.coverage
	cd ../ && gcovr --xml-pretty >> lcov.xml && mv lcov.xml .coverage/

U01_FLAGS	= -Iinclude -Llib -ltestu01 -lprobdist -lmylib -lm
U01_FILES	= nt/testu01_nt.cpp
U01_BIN		= openGPMP_U01

TestU01:
	$(CXX) -g $(U01_FILES) $(NT)/random.cpp -o $(U01_BIN) $(U01_FLAGS)

clean:
	rm -f $(BIN) $(U01_BIN) *.gc* *.info *.o


