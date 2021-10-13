#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pokemon.h"

struct pokemon_info {
  int pokemon_id;
  char *name;
  double height;
  double weight;
};

Pokemon new_pokemon(int pokemon_id, char *name, double height, double weight) {
  Pokemon pokemon = malloc(sizeof(struct pokemon_info));
  pokemon->pokemon_id = pokemon_id;
  pokemon->name = name;
  pokemon->height = height;
  pokemon->weight = weight;

  return pokemon;
}

char *pokemon_name(Pokemon pokemon) {
  return pokemon->name;
}

double pokemon_height(Pokemon pokemon) {
  return pokemon->height;
}

double pokemon_weight(Pokemon pokemon) {
	return pokemon->weight;
}

int pokemon_id(Pokemon pokemon) {
  return pokemon->pokemon_id;
}
