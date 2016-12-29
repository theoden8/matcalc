CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr -pthread -lm -ftrapv
ifeq ($(shell uname), Darwin)
	CC = clang-omp
endif
COBJECTS = $(wildcard *.c)
BINDIR = ../bin

all : $(patsubst %.c, %, $(COBJECTS))

% : %.c
	$(CC) "$<" $(CFLAGS) -o "$(BINDIR)/$@"
