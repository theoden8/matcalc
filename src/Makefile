BINDIR = ../bin

OPTFLAGS = -Ofast -ftrapv -flto -march=native -mtune=native
THRFLAGS = -D MAXTHREADS=$(shell getconf _NPROCESSORS_ONLN) -pthread -fopenmp
CFLAGS = -std=c99 $(OPTFLAGS) -Wno-implicit-int -Wno-incompatible-pointer-types -I../lib/ $(shell $(PKGCONFIG) --cflags mpfr gmp) $(THRFLAGS)
LDFLAGS = -L../lib/matcalc -lmatcalc $(shell $(PKGCONFIG) --libs gmp mpfr) -lmpfr -lgmp -lm
COBJECTS = $(wildcard *.c)

CXXFLAGS = -std=c++14 $(shell pkg-config --cflags gmp mpfr) $(OPTFLAGS) -I ../lib/ $(LDFLAGS) $(THRFLAGS)
LDXXFLAGS = $(LDFLAGS) -lgmpxx
CXXOBJECTS = $(wildcard *.cpp)

# NVCC = nvcc
# NVOBJECTS = $(wildcard *.cu)
# NVFLAGS = -lm -O2

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

CORES = $(shell getconf _NPROCESSORS_ONLN)
all : ../lib/matcalc/libmatcalc.a; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS)) \
	$(patsubst %.cu, %, $(NVOBJECTS)) \
	$(patsubst %.cpp, %, $(CXXOBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) $(LDFLAGS) -o "$(BINDIR)/$@"

# % : %.cu
# 	$(NVCC) "$<" $(NVFLAGS) -o "$(BINDIR)/$@"

% : %.cpp
	$(CXX) "$<" $(CXXFLAGS) $(LDXXFLAGS) -o "$(BINDIR)/$@"

check :
	make
	make clean

clean :
	rm -rvf $(BINDIR)
