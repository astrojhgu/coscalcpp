target=lib/libjscoscalcpp.a
all:$(target)

CXX=em++
CXXFLAGS=-std=c++11 -I include/ -g -O2
LDFLAGS=-L lib/ -lcoscalcpp

jsobj/coscalc.o:src/coscalc.cpp include/coscalc.hpp
	mkdir -p jsobj && $(CXX) -c $< -o $@ $(CXXFLAGS)

lib/libjscoscalcpp.a:jsobj/coscalc.o
	mkdir -p lib && emar rv $@ $^

clean:
	rm -rf jsobj bin lib
