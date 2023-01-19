JL_SHARE = $(shell julia -e 'print(joinpath(Sys.BINDIR, Base.DATAROOTDIR, "julia"))')
CXXFLAGS += $(subst -std=gnu99,,$(shell $(JL_SHARE)/julia-config.jl --cflags))
#CXXFLAGS += -DVERBOSE_IMPORT #To enable the verbose mode of the libray loading
#CXXFLAGS += -Wall -O0 -g     #To compile with debugger infomation
LDFLAGS  += $(shell $(JL_SHARE)/julia-config.jl --ldflags)
LDLIBS   += $(shell $(JL_SHARE)/julia-config.jl --ldlibs)

arith = ../../modules/arithmetic/arith.cpp

CXXWRAP_CPPFLAGS=-I $(shell julia -e 'using CxxWrap; print(CxxWrap.prefix_path() * "/include")') -std=c++17

CXXFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable -fmax-errors=3

CPPFLAGS += -MMD

LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

CC_FILES = jlArithmetic.cxx 

.PHONY: all clean run_demo

.PRECIOUS: $(CC_FILES)

PRODUCTS = jlArithmetic.so jlArithmetic.cxx jlArithmetic.h Arithmetic.jl

all: $(PRODUCTS)

clean:
	-$(RM) $(PRODUCTS) jlArithmetic.d jlArithmetic.o jlArithmetic-report.txt

jl%.cxx: %.wit
	wrapit --force $<

%.o: %.cxx
	$(COMPILE.cc) $(CXXWRAP_CPPFLAGS) -o $@ $<


jl%.so: jl%.o
	$(LINK.o) -o $@ --shared -fPIC $< $(ROOT_LIBS)

echo_%:
	@echo $*=$($*)

run_demo: all
	. ./path.sh && julia arithmetic_ex.jl

-include $(addsuffix .d, $(basename $(CC_FILES)))
