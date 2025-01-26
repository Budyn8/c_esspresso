minimize: main.o
	gcc -o minimize main.o

main.o: main.c
	gcc -c main.c

test: test.o
	gcc -o test test.o
	rm test.o

test.o: test.c
	gcc -c test.c

clean:
	rm minimize main.o
