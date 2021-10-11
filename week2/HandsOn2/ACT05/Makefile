main_v2: main_v2.o 
	gcc main_v2.o pokemon.o pokedex.o -o main_v2
main_v2.o: main_v2.c
	gcc -c pokemon.c pokedex.c main_v2.c
clean:
	/bin/rm -rf *.o main_v2
execute:
	./main_v2
