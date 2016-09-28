CFLAGS = -O3 -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp
OBJECTS = $(wildcard *.c)
BINDIR = ./bin

$(shell rm -rvf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

all : $(patsubst %.c, %, $(OBJECTS))

% : %.c
	$(CC) $(CFLAGS) -o "$(BINDIR)/$@" "$<"
