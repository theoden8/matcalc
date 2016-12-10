CFLAGS = -O3 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr
OBJECTS = $(wildcard *.c)
BINDIR = ../bin

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

all : $(patsubst %.c, %, $(OBJECTS))

% : %.c
	$(CC) $(CFLAGS) -o "$(BINDIR)/$@" "$<"
