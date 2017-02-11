ifeq ($(shell uname), Darwin)
	CC = clang-omp
endif
CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr -pthread -lm -ftrapv
COBJECTS = $(wildcard *.c)
BINDIR = ../bin

CORES = $(shell getconf _NPROCESSORS_ONLN)
all: ../bin; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"

clean :;
