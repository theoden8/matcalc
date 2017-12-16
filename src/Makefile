BINDIR = ../bin

LDFLAGS = -L../lib/matcalc -lmatcalc
OPTFLAGS = -Ofast -ftrapv -flto -march=native -mtune=native
CFLAGS = $(OPTFLAGS) -fopenmp -Wno-implicit-int -Wno-incompatible-pointer-types -I../lib/ -lgmp -lmpfr -pthread -lm $(LDFLAGS) -D MAXTHREADS=$(shell getconf _NPROCESSORS_ONLN)
COBJECTS = $(wildcard *.c)

CXXFLAGS = -std=c++1y -lgmpxx -lgmp -flto -O2
CXXOBJECTS = $(wildcard *.cpp)

NVCC = nvcc
NVOBJECTS = $(wildcard *.cu)
NVFLAGS = -lm -O2

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

CORES = $(shell getconf _NPROCESSORS_ONLN)
all : ../lib/matcalc/libmatcalc.a; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS)) \
	$(patsubst %.cu, %, $(NVOBJECTS)) \
	$(patsubst %.cpp, %, $(CXXOBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"

% : %.cu
	$(NVCC) "$<" $(NVFLAGS) -o "$(BINDIR)/$@"

% : %.cpp
	$(CXX) "$<" $(CXXFLAGS) -o "$(BINDIR)/$@"

check :
	make
	make clean

clean :
	rm -rvf $(BINDIR)
