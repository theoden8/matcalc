BINDIR = ./bin

LDFLAGS = -L../lib/matcalc -lmatcalc -lm
OPTFLAGS = -Ofast -ftrapv -flto -march=native -mtune=native
THRFLAGS = -D MAXTHREADS=$(shell getconf _NPROCESSORS_ONLN) -pthreads -fopenmp
CFLAGS = $(OPTFLAGS) -Wno-implicit-int -Wno-incompatible-pointer-types -I../lib/ -lgmp -lmpfr $(LDFLAGS) $(THRFLAGS)
COBJECTS = $(wildcard *.c)

CXXFLAGS = -std=c++14 -lgmpxx -lgmp $(OPTFLAGS) -I ../lib/ $(LDFLAGS) $(THRFLAGS)
CXXOBJECTS = $(wildcard *.cpp)


$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

CORES = $(shell getconf _NPROCESSORS_ONLN)
all : ../lib/matcalc/libmatcalc.a; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS)) \
	$(patsubst %.cpp, %, $(CXXOBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"

% : %.cpp
	$(CXX) "$<" $(wildcard ../lib/matcalc/*.c) $(CXXFLAGS) -o "$(BINDIR)/$@"

check :
	make
	make clean

clean :
	rm -rvf $(BINDIR)
