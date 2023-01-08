# Makefile for wrapping openMTPK for Python with Swig.
# Working for both OSX and LINUX

# DETECT OPERATING SYSTEM
OS			:= $(shell uname)

check-os:
	echo ${OS} DETECTED

CXX			= g++
CXX_DBG     = -Wall -Wextra -g
STD			= --std=c++17

pypathLINUX	= -I/usr/include/python3.10
pypathOSX	= -I/usr/local/Cellar/python@3.9/3.9.6/Frameworks/Python.framework/Headers

API_DIR		= $(realpath $(CURDIR))
SRC_DIR		= $(API_DIR)/../../
MOD_DIR		= $(SRC_DIR)/modules/
INC_DIR		= $(SRC_DIR)/include/


##############################################################################
# RUN SWIG
##############################################################################
swig_files	= openmtpk.i
run-swig:
	swig -c++ -python ${swig_files}

##############################################################################
# COMPILE openMTPK SOURCES
##############################################################################
primes 		= $(MOD_DIR)/number_theory/primes.cpp
arith		= $(MOD_DIR)/arithmetic/arith.cpp
calc		= $(MOD_DIR)/calculus/deriv.cpp
linalg		= $(MOD_DIR)/linalg/lao.cpp
linreg		= $(MOD_DIR)/ml/linreg.cpp
cipher		= $(MOD_DIR)/number_theory/cipher.cpp
rc4			= $(MOD_DIR)/number_theory/rc4.cpp
compile:
	${CXX} ${STD} ${CXX_DBG} -O2 -fPIC -c ${arith} ${calc} ${primes} ${linalg} ${linreg} ${cipher} ${rc4}

##############################################################################
# COMPILE WRAPPED SOURCE FILE 
##############################################################################
compile-wrapper:
# LINUX
ifeq ($(OS), Linux)
	${CXX} ${STD} ${CXX_DBG} -O2 -fPIC -c openmtpk_wrap.cxx ${pypathLINUX}
endif

# MACOSX
ifeq ($(OS), Darwin)
	${CXX} ${STD} ${CXX_DBG} -O2 -fPIC -c openmtpk_wrap.cxx ${pypathOSX}
endif

##############################################################################
# COMPILE SOURCE OBJECTS 
##############################################################################
pkgLINUX	= _openmtpk.so
pkgOSX		= _openmtpk.so

src_objs	= arith.o deriv.o lao.o linreg.o primes.o cipher.o rc4.o openmtpk_wrap.o
compile-lib:
# LINUX
ifeq ($(OS), Linux)
	${CXX} ${STD} ${CXX_DBG} -shared ${src_objs} -o ${pkgLINUX}
endif

# MACOSX
ifeq ($(OS), Darwin)
	 ${CXX} ${STD} ${CXX_DBG} -shared ${src_objs} -o ${pkgOSX}
endif


clean:
	rm -rf */__pycache__
	rm -f *.o
	rm -f *.so
	rm -f *.cxx
	rm -f openmtpk.py

