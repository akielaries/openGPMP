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

openGL_circle:
	${CC} ${GPU_0} ${CXXFLAGS2} -o ${GPU_BIN_0} 
	./${GPU_BIN_0}


GPU_01		= $(PROJDIR)/GPU/openGL_tri.cpp
GPU_BIN_01	= openGL_tri

openGL_tri:
	${CXX} ${GPU_01} ${CXXFLAGS} ${CXXFLAGS2} -o ${GPU_BIN_01} 
	./${GPU_BIN_01}


GPU_02		= $(PROJDIR)/GPU/openGL_torus.cpp
GPU_BIN_02	= openGL_torus

openGL_torus:
	${CXX} ${GPU_02} ${CXXFLAGS} ${CXXFLAGS2} -o ${GPU_BIN_02} 
	./${GPU_BIN_02}


GPU_03		= $(PROJDIR)/GPU/openGL_torus_animated.cpp
GPU_BIN_03	= openGL_torus_animated

openGL_torus_animated:
	${CXX} ${GPU_03} ${CXXFLAGS} ${CXXFLAGS2} -o ${GPU_BIN_03} 
	./${GPU_BIN_03}

clean_bins:
	rm -f ${GPU_BIN_0}
	rm -f ${GPU_BIN_01}
	rm -f ${GPU_BIN_02}
	rm -f ${GPU_BIN_03}

