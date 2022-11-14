# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= g++
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g

SRCDIR		= $(PROJDIR)/modules
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')

# FILES FOR REGRESSION
LR			= $(SRCDIR)/regression/linreg.cpp
LRDRV		= $(PROJDIR)/examples/reg_driver.cpp
LRBIN		= lin_reg

LIBDIR		= $(PROJDIR)/include


lin-reg:
	${CC} ${LR} ${LRDRV} -o ${LRBIN}
	./${LRBIN}


clean:
	rm -f ${LRBIN}

