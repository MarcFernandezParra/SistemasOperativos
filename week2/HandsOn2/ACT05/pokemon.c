#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pokemon.c"

struct Pokemon {
  int pokemon_id;
  char *name;
  double height;
  double weight;
};

struct Pokemon new_pokemon(int pokemon_id, char *name, double height, double weight){
	struct Pokemon new_poke;
	new_poke.pokemon_id = pokemon_id;
	new_poke.name = (char *)malloc((strlen(name)+1)*sizeof(char));
	new_poke.height = height;
	new_poke.weight = weight;
	return new_poke;
}
char *pokemon_name(struct Pokemon pokemon){
	return pokemon.name;
}
double pokemon_height(struct Pokemon pokemon){
	return pokemon.height;
}
double pokemon_weight(struct Pokemon pokemon){
	return pokemon.weight;
}
