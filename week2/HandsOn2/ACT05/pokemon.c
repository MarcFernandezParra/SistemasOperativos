#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pokemon.h"

typedef struct Pokemon {
  int pokemon_id;
  char *name;
  double height;
  double weight;
};

struct Pokemon new_pokemon(int id, char *name, double height, double weight){
    printf("%d\n", id);
    printf("%lf\n", weight);
    printf("%lf\n", height);
    printf("%s\n", name);

    struct Pokemon *pokemon = malloc(sizeof(struct Pokemon));
    pokemon->pokemon_id = id;
    pokemon->name = name;
    pokemon->height = height;
    pokemon->weight = weight;

    return *pokemon;
}

char *pokemon_name(struct Pokemon *pokemon) {
	 return pokemon->name;
}

double pokemon_height(struct Pokemon *pokemon) {
	 return pokemon->height;
}

double pokemon_weight(struct Pokemon *pokemon) {
	return pokemon->weight;
}

int pokemon_id(struct Pokemon *pokemon) {
    return pokemon->pokemon_id;
}
