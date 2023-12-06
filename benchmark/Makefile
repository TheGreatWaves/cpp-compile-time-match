build:
	g++ nanobench.cpp benchmark.cpp -o prog --std=c++20 -O3

run: build
	./prog && rm ./prog

mem: build
	valgrind --leak-check=full -v ./prog && rm ./prog