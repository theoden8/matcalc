OPTFLAGS = -Ofast -flto -ftrapv -m64 -march=native -mtune=native
CFLAGS = $(OPTFLAGS) -std=c99 -Wno-implicit-int -Wno-incompatible-pointer-types -ftrapv -D MAXTHREADS=$(shell getconf _NPROCESSORS_ONLN) $(shell $(PKGCONFIG) --cflags mpfr gmp) -fPIC
# CFLAGS += -DNPRINT
OBJECTS = $(wildcard *.c)
LDFLAGS = $(shell $(PKGCONFIG) --libs mpfr) -lgmp -lmpfr -pthread $(shell $(PKGCONFIG) --libs --cflags --silence-errors libbsd) -lm
COBJECTS = $(patsubst %.c, %.o, $(OBJECTS))

LIBNAME = libmatcalc

CORES = $(shell getconf _NPROCESSORS_ONLN)
all :; @$(MAKE) _all -j$(CORES)
_all : $(LIBNAME).a $(LIBNAME).so

$(LIBNAME).a : $(COBJECTS)
	ar rcs "$@" $(COBJECTS)

$(LIBNAME).so : $(COBJECTS)
	$(CC) -o "$@" $(COBJECTS) $(CFLAGS) $(LDFLAGS) -shared

%.o : %.c
	$(CC) -c $(CFLAGS) -o "$@" "$<"

clean :
	rm -vf *.o *.a *.so
