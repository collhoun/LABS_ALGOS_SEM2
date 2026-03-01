
test.o: test.c
	gcc -c test.c

trees.o: trees.c
	gcc -c trees.c

run.o: run.c
	gcc -c run.c

all: test.o trees.o run.o
	gcc -o main test.o trees.o run.o

clean:
	rm -f *.o main