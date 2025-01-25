minimize: main.o
	gcc -o minimize main.o

main.o: main.c
	gcc -c main.c

clean:
	rm minimize main.o
