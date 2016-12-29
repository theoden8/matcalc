CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr -pthread -lm -ftrapv
ifeq ($(shell uname), Darwin)
	CC = clang-omp
endif
COBJECTS = $(wildcard *.c)
BINDIR = ../bin
CXXFLAGS = -std=c++1y
CXXHEADERS = $(wildcard *.hpp)
CXXOBJECTS = $(wildcard *.cpp)

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

all : $(patsubst %.c, %, $(COBJECTS)) $(patsubst %.cpp, %, $(CXXOBJECTS)) $(patsubst %.hpp, %.hpp.gch, $(CXXHEADERS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"

% : %.cpp
	$(CXX) "$<" $(CXXFLAGS) -lgmpxx -lgmp -o "$(BINDIR)/$@"

%.hpp.gch : %.hpp
	$(CXX) "$<" $(CXXFLAGS)

check :
	make
	make clean

clean :
	rm -vf *.gch
	rm -rvf $(BINDIR)
