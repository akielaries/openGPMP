JL_SHARE = $(shell julia -e 'print(joinpath(Sys.BINDIR, Base.DATAROOTDIR, "julia"))')
CXXFLAGS += $(subst -std=gnu99,,$(shell $(JL_SHARE)/julia-config.jl --cflags))
#CXXFLAGS += -DVERBOSE_IMPORT #To enable the verbose mode of the libray loading
#CXXFLAGS += -Wall -O0 -g     #To compile with debugger infomation
LDFLAGS  += $(shell $(JL_SHARE)/julia-config.jl --ldflags)
LDLIBS   += $(shell $(JL_SHARE)/julia-config.jl --ldlibs)

arith = ../../modules/arithmetic/arith.cpp
deriv = ../../modules/calculus/deriv.cpp
nt = ../../modules/nt/primes.cpp

CXXWRAP_CPPFLAGS=-I $(shell julia -e 'using CxxWrap; print(CxxWrap.prefix_path() * "/include")') -std=c++20

INCL_ARITH 	= -I'../../include/arithmetic'
INCL_CALC 	= -I'../../include/calculus'
INCL_LA 	= -I'../../include/linalg'
INCL_NT 	= -I'../../include/nt'

CXXFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable -fmax-errors=3

CPPFLAGS += -MMD

LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

CC_FILES = jlopenMTPK.cxx $(arith) $(deriv) 

.PHONY: all clean run_demo

.PRECIOUS: $(CC_FILES)

PRODUCTS = jlopenMTPK.so jlopenMTPK.cxx jlopenMTPK.h openMTPK.jl

all: $(PRODUCTS)

clean:
	-$(RM) jlopenMTPK-report.txt *.o *.d *.cxx *.h

jl%.cxx: %.wit
	wrapit --force $<

%.o: %.cxx
	$(COMPILE.cc) $(CXXWRAP_CPPFLAGS) $(INCL_ARITH) $(INCL_CALC) $(INCL_LA) -o $@ $<


jl%.so: jl%.o arith.o deriv.o primes.o
	$(LINK.o) -o $@ --shared -fPIC $^ $(ROOT_LIBS) 

arith.o: $(arith)
	$(COMPILE.cc) $(CXXWRAP_CPPFLAGS) $(INCL_ARITH) -o $@ $<

deriv.o: $(deriv)
	$(COMPILE.cc) $(CXXWRAP_CPPFLAGS) $(INCL_CALC) -o $@ $<

primes.o: $(nt)
	$(COMPILE.cc) $(CXXWRAP_CPPFLAGS) $(INCL_NT) -o $@ $<

echo_%:
	@echo $*=$($*)

run_demo: all
	. ./path.sh && julia arithmetic_ex.jl

-include $(addsuffix .d, $(basename $(CC_FILES)))
