HXXFLAGS = -std=c++14 -ftemplate-depth=4096
CXXHEADERS = $(wildcard *.hpp)

CORES = $(shell getconf _NPROCESSORS_ONLN)
all :; @$(MAKE) _all -j$(CORES)
_all : \
	$(patsubst %.hpp, %.hpp.gch, $(CXXHEADERS))

%.hpp.gch : %.hpp
	$(CXX) "$<" $(HXXFLAGS)
	rm -vf "$@"

clean :
	rm -vf *.gch
