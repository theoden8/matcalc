CFLAGS = -O3 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr
COBJECTS = $(wildcard *.c)
BINDIR = ../bin
CXXFLAGS = -std=c++11
CXXHEADERS = $(wildcard *.hpp)

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

all : $(patsubst %.c, %, $(COBJECTS)) $(patsubst %.hpp, %.hpp.gch, $(CXXHEADERS))

% : %.c
	$(CC) $(CFLAGS) -o "$(BINDIR)/$@" "$<"

%.hpp.gch : %.hpp
	$(CXX) $(CXXFLAGS) "$<"
