CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr -pthread -lm -ftrapv
ifeq ($(shell uname), Darwin)
	CC = clang-omp
endif
COBJECTS = $(wildcard *.c)
BINDIR = ../bin
CXXFLAGS = -std=c++1y -lgmpxx -lgmp -flto -O2
CXXOBJECTS = $(wildcard *.cpp)
CXXHEADERS = $(wildcard *.hpp)

NVCC = nvcc
NVOBJECTS = $(wildcard *.cu)
NVFLAGS = -lm -O2

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

all : \
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
	$(CXX) "$<" $(CXXFLAGS)

check :
	make
	make clean

clean :
	rm -vf *.gch
	rm -rvf $(BINDIR)
