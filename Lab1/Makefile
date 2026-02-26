
test.o: test.c
	gcc -c test.c

trees.o: trees.c
	gcc -c trees.c

all: test.o trees.o
	gcc -o main test.o trees.o

clean:
	rm -f *.o main