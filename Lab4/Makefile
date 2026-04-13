CC=gcc

all: main

main: src/main.c src/tree.c
	$(CC) -o main src/main.c src/tree.c

clean:
	rm -f *.exe

tests: tests/test.c tests/test_tree_many.c src/tree.c
	$(CC) -o test tests/test.c tests/test_tree_many.c src/tree.c 