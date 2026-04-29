CC=gcc
CXX=g++
CFLAGS=-Wall -g
CXXFLAGS=-Wall -g -std=c++14

all: main

main: src/main.c src/edge_array.c src/graph.c
	$(CC) $(CFLAGS) -o main src/main.c src/edge_array.c src/graph.c

test:
	rm -rf build
	mkdir -p build
	cd build && cmake -G "MinGW Makefiles" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ..
	cd build && mingw32-make my_tests
	cd build && ./my_tests

benchmark: src/simple_benchmark.cpp src/edge_array.c src/graph.c
	$(CXX) $(CXXFLAGS) -o benchmark src/simple_benchmark.cpp src/edge_array.c src/graph.c
	./benchmark

bench: benchmark

clean:
	rm -f main benchmark
	rm -rf build