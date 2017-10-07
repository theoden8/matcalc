OPTFLAGS = -Ofast -flto -ftrapv -m64 -march=native
CFLAGS = $(OPTFLAGS) -Wno-implicit-int -Wno-incompatible-pointer-types -ftrapv -D MAXTHREADS=$(shell getconf _NPROCESSORS_ONLN)
# CFLAGS += -DNPRINT
OBJECTS = $(wildcard *.c)
LDFLAGS = -lmpfr -lgmp -pthread -lm
COBJECTS = $(patsubst %.c, %.o, $(OBJECTS))

LIBNAME = libmatcalc

$(shell rm -f *.o)

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
