BINDIR = ./bin

OPTFLAGS = -Ofast -ftrapv -flto -march=native -mtune=native
THRFLAGS = -D MAXTHREADS=$(shell getconf _NPROCESSORS_ONLN) -pthread -fopenmp
CFLAGS = -std=c99 $(OPTFLAGS) -Wno-implicit-int -Wno-incompatible-pointer-types -I../lib/ -lgmp $(shell $(PKGCONFIG) --cflags mpfr gmp) $(THRFLAGS) -fPIC
LDFLAGS = $(shell $(PKGCONFIG) --libs mpfr gmp) -L../lib/matcalc -lmatcalc -lm
COBJECTS = $(wildcard *.c)

CXXFLAGS = -std=c++14 $(shell $(PKGCONFIG) --cflags mpfr gmp) $(OPTFLAGS) -I ../lib/ $(THRFLAGS)
LDFLAGSXX = $(LDFLAGS) -lgmpxx
CXXOBJECTS = $(wildcard *.cpp)


$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

CORES = $(shell getconf _NPROCESSORS_ONLN)
all : ../lib/matcalc/libmatcalc.a; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS)) \
	$(patsubst %.cpp, %, $(CXXOBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) $(LDFLAGS) -o "$(BINDIR)/$@"

% : %.cpp
	$(CXX) "$<" $(wildcard ../lib/matcalc/*.c) $(CXXFLAGS) $(LDFLAGSXX) -o "$(BINDIR)/$@"

check :
	make
	make clean

clean :
	rm -rvf $(BINDIR)
