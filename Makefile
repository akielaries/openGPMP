# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= g++
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g

SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR REGRESSION
LR			= $(SRCDIR)/regression/linreg.cpp
LRDRV		= $(PROJDIR)/drivers/reg_driver.cpp
LRBIN		= lin_reg
# FILES FOR BASIC LINEAR ALGEBRA OPERATIONS
BLA			= $(SRCDIR)/LA/la_ops.cpp
BLADRV		= $(PROJDIR)/drivers/la_ops_driver.cpp
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

