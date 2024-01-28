# USE G++-10 for baremetal testing, G++-12 for Docker use
# Check if running within a Docker container
IS_DOCKER := $(shell test -f /.dockerenv && echo 1)

ifeq ($(IS_DOCKER),1)
    # If running within a Docker container, use g++-12
    CC := g++-12
else
    # If not running within a Docker container, use g++-10
    CC := g++-10
endif

CCSTD	= -std=c++20 -march=native -lpthread
CCFLGS	= -pg -g -Wall -Wextra -pedantic -Wno-unused-result -Wparentheses -Wsign-compare

NVCC 	= nvcc

PROJDIR = $(realpath $(CURDIR))
SRCDIR	= $(PROJDIR)/src
CPP		= $(shell find $(PROJDIR)/src -name '*.cpp')
MAIN	= benchmark.cpp
BIN 	= benchsys
OBJDIR  = $(PROJDIR)/obj

# check if nvcc (CUDA compiler) is available
ifeq ($(shell command -v nvcc -V 2> /dev/null),)
	HAS_NVCC 	=
	OBJ_CUDA	=

# has NVCC
else
	# set CUDA defs
	CUDA    	= $(shell find $(PROJDIR)/src -name '*.cu')
	HAS_NVCC 	= -D__HAS_NVCC__
	NVCC_FLGS	= -pg -g -Wno-deprecated-gpu-targets
	OBJ_CUDA	= $(patsubst $(SRCDIR)/%.cu,$(OBJDIR)/%.o,$(CUDA))

$(OBJDIR)/%.o: $(SRCDIR)/%.cu
	@mkdir -p $(@D)
	$(NVCC) -c ${HAS_NVCC} $(NVCC_FLGS) $< -o $@

endif
OBJ_CPP = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPP))
OBJ 	= $(OBJ_CPP) $(OBJ_CUDA)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c  $(HAS_NVCC) $(CCSTD) $(CCFLGS) $< -o $@

$(BIN): $(OBJ)
ifeq ($(HAS_NVCC), -D__HAS_NVCC__)
	$(NVCC) $(MAIN) $(HAS_NVCC) $(NVCC_FLGS) $^ -o $@
else
	$(CC) $(MAIN) $(HAS_NVCC) $(CCSTD) $(CCFLGS) $^ -o $@
endif

run_bench:
	./${BIN} -b

run_daemon:
	./${BIN} -d

gprof:
	gprof ${BIN} gmon.out > gprof.txt

callgrind:
	valgrind --tool=callgrind ./${BIN}
	#callgrind_annotate callgrind.out

flamegraph:
	sudo perf record -g ./${BIN}
	sudo perf script | sudo ../FlameGraph/stackcollapse-perf.pl | sudo ../FlameGraph/flamegraph.pl > rpi.svg

docker_img:
	sudo docker build . -t benchmarks

docker_run:
	sudo docker run --privileged -it benchmarks:latest /bin/bash

gpu_docker_img:
	sudo nvidia-docker build . -t benchmarks

gpu_docker_run:
	sudo nvidia-docker run --privileged -it benchmarks:latest /bin/bash

avail_macros:
	gcc -dM -E - </dev/null

install:
	mv ${BIN} /usr/bin

uninstall:
	rm -f /usr/bin/${BIN}

clean:
	rm -f ${BIN}
	rm -f *.txt
	rm -f *.out
	rm -f *.data*
	rm -f *perf
	rm -f *.csv
	rm -f *.o
	rm -rf obj/
