ifeq ($(shell uname), Darwin)
CC = clang-omp
endif
CFLAGS = -O2 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -ftrapv
OBJECTS = $(wildcard *.c)

STATICLIB = libmatcalc

$(shell rm -f *.o)

CORES = $(shell getconf _NPROCESSORS_ONLN)
all :; @$(MAKE) _all -j$(CORES)
_all : $(STATICLIB).a

$(STATICLIB).a : $(patsubst %.c, %.o, $(OBJECTS))
	ar rcs "$@" $(patsubst %.c, %.o, $(OBJECTS))

%.o : %.c
	$(CC) -c $(CFLAGS) $(shell ./detect_libs.pl "$<") -o "$@" "$<"

clean :
	rm -vf *.o
	rm -vf *.a
