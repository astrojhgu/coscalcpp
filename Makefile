target=lib/libcoscalcpp.a bin/test
all:$(target)

CXX=clang++
CXXFLAGS=-std=c++11 -I include/ -g -fPIC -O2
LDFLAGS=-L lib/ -lcoscalcpp

obj/coscalc.o:src/coscalc.cpp include/coscalc.hpp
	mkdir -p obj && $(CXX) -c $< -o $@ $(CXXFLAGS)

lib/libcoscalcpp.a:obj/coscalc.o
	mkdir -p lib && ar rv $@ $^

bin/test: test/test.cpp lib/libcoscalcpp.a
	mkdir -p bin && $(CXX) -o $@ $< $(CXXFLAGS) $(LDFLAGS) 

clean:
	rm -rf obj bin lib
