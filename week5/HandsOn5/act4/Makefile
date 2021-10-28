main_v2: main.o 
	gcc main.o pokemon.o pokedex.o -o main
main_v2.o: main.c
	gcc -c pokemon.c pokedex.c main.c
clean:
	/bin/rm -rf *.o main
execute:
	./main
