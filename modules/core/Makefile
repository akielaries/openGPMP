WRAP		= accl_mtx_wrapper.cpp
SRC			= accl_mtx.c
SRC_OBJ		= accl_mtx.o

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

WRAP_ARR 	= accl_arr_wrapper.cpp
SRC_ARR		= accl_arr.c
SRC_ARR_OBJ	= accl_arr.o

compile_src_arr:
	${CC} ${CFLAGS} ${SRC_ARR} -o ${SRC_ARR_OBJ} ${CLFLAGS}

compile_wrap_arr:
	${CXX} ${CXXFLAGS} ${WRAP_ARR} ${SRC_ARR_OBJ} ${CLFLAGS} -o ${BIN_2}

clean:
	rm -rf *.o
	rm ${BIN} ${BIN_2}
