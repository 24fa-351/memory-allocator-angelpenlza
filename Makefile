all: mem all-tests clean

one: mem one-test clean

mem: tests.c mem.c
	gcc tests.c mem.c -o mem

all-tests:
	./mem

one-test: 
	./mem -t 1

clean:
	rm mem