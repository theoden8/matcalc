CFLAGS = -O3 -flto -Wno-implicit-int -Wno-incompatible-pointer-types -lgmp -lmpfr
COBJECTS = $(wildcard *.c)
BINDIR = ../bin
CXXFLAGS = -std=c++1y
CXXHEADERS = $(wildcard *.hpp)
CXXOBJECTS = $(wildcard *.cpp)

$(shell rm -rf "$(BINDIR)")
$(shell mkdir -p "$(BINDIR)")

all : $(patsubst %.c, %, $(COBJECTS)) $(patsubst %.hpp, %.hpp.gch, $(CXXHEADERS)) $(patsubst %.cpp, %, $(CXXOBJECTS))

% : %.c
	$(CC) $(CFLAGS) -o "$(BINDIR)/$@" "$<"

% : %.cpp
	$(CXX) $(CXXFLAGS) -lgmpxx -lgmp -o "$(BINDIR)/$@" "$<"

%.hpp.gch : %.hpp
	$(CXX) $(CXXFLAGS) "$<"

clean :
	rm -vf *.gch
	rm -rvf $(BINDIR)
