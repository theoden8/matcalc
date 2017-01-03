CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr -pthread -lm -ftrapv
ifeq ($(shell uname), Darwin)
	CC = clang-omp
endif
COBJECTS = $(wildcard *.c)
BINDIR = ../bin

CORES ?= $(shell sysctl -n hw.ncpu || echo 1)
all:; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.c, %, $(COBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"
