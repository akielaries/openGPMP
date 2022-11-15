# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= g++
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g

SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR REGRESSION
LR			= $(SRCDIR)/regression/linreg.cpp
LRDRV		= $(PROJDIR)/drivers/d_reg.cpp
LRBIN		= lin_reg
# FILES FOR BASIC LINEAR ALGEBRA OPERATIONS
BLA			= $(SRCDIR)/LINALG/la_ops.cpp
BLADRV		= $(PROJDIR)/drivers/d_lao.cpp
BLABIN		= la_ops

LIBDIR		= $(PROJDIR)/include


lin-reg:
	${CC} ${LR} ${LRDRV} -o ${LRBIN}
	./${LRBIN}

la-ops:
	${CC} ${BLA} ${BLADRV} -o ${BLABIN}
	./${BLABIN}

clean:
	rm -f ${LRBIN}

