BINDIR = ../bin

ifeq ($(shell uname), Darwin)
CC = clang-omp
endif

CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr -pthread -lm -ftrapv
COBJECTS = $(wildcard *.c)

CXXFLAGS = -std=c++1y -lgmpxx -lgmp -flto -O2
CXXOBJECTS = $(wildcard *.cpp)

HPPFLAGS = -std=c++1y
CXXHEADERS = $(wildcard *.hpp)

NVCC = nvcc
NVOBJECTS = $(wildcard *.cu)
NVFLAGS = -lm -O2

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

CORES = $(shell getconf _NPROCESSORS_ONLN)
all :; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS)) \
	$(patsubst %.cu, %, $(NVOBJECTS)) \
	$(patsubst %.cpp, %, $(CXXOBJECTS)) \
	$(patsubst %.hpp, %.hpp.gch, $(CXXHEADERS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"

% : %.cu
	$(NVCC) "$<" $(NVFLAGS) -o "$(BINDIR)/$@"

% : %.cpp
	$(CXX) "$<" $(CXXFLAGS) -o "$(BINDIR)/$@"

%.hpp.gch : %.hpp
	$(CXX) "$<" $(HPPFLAGS)

check :
	make
	make clean

clean :
	rm -vf *.gch
	rm -rvf $(BINDIR)
