# define our project director
PROJDIR     = $(realpath $(CURDIR))

LIBXBGI		= /usr/lib/libXbgi.a

CXX			= g++ 
CXXFLAGS	= -lpthread -fopenmp ${LIBXBGI} -lX11 
CXXFLAGS2	= -lGL -lGLU -lglut -lm

CC 			= gcc

VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g

SRCDIR		= $(PROJDIR)/
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

GPU_DIR		= $(PROJDIR)/GPU
GPU_0		= $(PROJDIR)/GPU/openGL_example00.c
GPU_BIN_0	= openGL_00

openGL_00:
	${CC} ${GPU_0} ${CXXFLAGS2} -o ${GPU_BIN_0} 
	./${GPU_BIN_0}

openGL_01:


openGL_02:


openGL_03:


clean_bins:
	rm ${GPU_BIN_0}

