build:
	g++ trie.cpp -o prog --std=c++20

run: build
	./prog && rm ./prog

mem: build
	valgrind --leak-check=full -v ./prog && rm ./prog