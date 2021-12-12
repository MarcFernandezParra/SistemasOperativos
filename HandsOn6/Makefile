main: main.o 
	gcc main.o pokemon.o pokedex.o -o main
main.o: main.c
	gcc -c pokemon.c pokedex.c main.c
clean:
	/bin/rm -rf *.o main
execute:
	./main
