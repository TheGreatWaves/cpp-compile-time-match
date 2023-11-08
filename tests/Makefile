build:
	g++ basic_trie_test.cpp -o prog --std=c++20 -O3

run: build
	./prog && rm ./prog

mem: build
	valgrind --leak-check=full -v ./prog && rm ./prog