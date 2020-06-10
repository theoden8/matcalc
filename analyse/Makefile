CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -fopenmp $(pkg-config --cflags gmp mpfr)
LDFLAGS = $(shell $(PKGCONFIG) --libs gmp mpfr) -lgmp -lmpfr -pthread -lm -ftrapv
COBJECTS = $(wildcard *.c)
BINDIR = ../bin

CORES = $(shell getconf _NPROCESSORS_ONLN)
all: ../bin; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) $(LDFLAGS) -o "$(BINDIR)/$@"

clean :;
