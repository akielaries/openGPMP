WRAP		= _gpu_mtx_add_wrapper.cpp 
SRC			= _gpu_mtx_add.c
SRC_OBJ		= _gpu_mtx_add.o

CC			= gcc
CXX			= g++

CFLAGS		= -c -fPIC -lm
CXXFLAGS	= 
CLFLAGS		= -lOpenCL

BIN 		= ACCL_MTX
BIN_2		= ACCL_ARR

compile_src_mtx:
	${CC} ${CFLAGS} ${SRC} -o ${SRC_OBJ} ${CLFLAGS}

compile_wrap_mtx:
	${CXX} ${CXXFLAGS} ${WRAP} ${SRC_OBJ} ${CLFLAGS} -o ${BIN}

WRAP_ARR 	= _gpu_arr_wrapper.cpp
SRC_ARR		= _gpu_arr_add.c
SRC_ARR_OBJ	= _gpu_arr_add.o

compile_src_arr:
	${CC} ${CFLAGS} ${SRC_ARR} -o ${SRC_ARR_OBJ} ${CLFLAGS}

compile_wrap_arr:
	${CXX} ${CXXFLAGS} ${WRAP_ARR} ${SRC_ARR_OBJ} ${CLFLAGS} -o ${BIN_2}

clean:
	rm -rf *.o
	rm ${BIN} ${BIN_2}
