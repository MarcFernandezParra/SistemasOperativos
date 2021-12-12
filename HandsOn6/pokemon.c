#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "pokemon.h"

struct pokemon_info {
  int pokemon_id;
  char *name;
  char **types;
  int total;
  int hp;
  int attack;
  int defense;
  int spAttack;
  int spDefense;
  int speed;
  int generation;
  int legendary;
  int seen;
  int captured;
};

Pokemon new_pokemon(int pokemon_id, char *name, char **types, 
                    int total, int hp, int attack, int defense, 
                    int spAttack, int spDefense, int speed, int generation, 
                    int legendary, int seen, int captured) {
  Pokemon pokemon = malloc(sizeof(struct pokemon_info));

  pokemon->pokemon_id = pokemon_id;
  pokemon->name = name;
  pokemon->types = types;
  pokemon->total = total;
  pokemon->hp = hp;
  pokemon->attack = attack;
  pokemon->defense = defense;
  pokemon->spAttack = spAttack;
  pokemon->spDefense = spDefense;
  pokemon->speed = speed;
  pokemon->generation = generation;
  pokemon->legendary = legendary;
  pokemon->seen = seen;
  pokemon->captured = captured;

  return pokemon;
}

int pokemon_id(Pokemon pokemon) {
  return pokemon->pokemon_id;
}

char *pokemon_name(Pokemon pokemon) {
  return pokemon->name;
}

char **pokemon_types(Pokemon pokemon) {
  return pokemon->types;
}

int pokemon_total(Pokemon pokemon) {
  return pokemon->total;
}

int pokemon_hp(Pokemon pokemon) {
  return pokemon->hp;
}

int pokemon_attack(Pokemon pokemon) {
  return pokemon->attack;
}

int pokemon_defense(Pokemon pokemon) {
  return pokemon->defense;
}

int pokemon_spAttack(Pokemon pokemon) {
  return pokemon->spAttack;
}

int pokemon_spDefense(Pokemon pokemon) {
  return pokemon->spDefense;
}

int pokemon_speed(Pokemon pokemon) {
  return pokemon->speed;
}

int pokemon_generation(Pokemon pokemon) {
  return pokemon->generation;
}

int pokemon_legendary(Pokemon pokemon) {
  return pokemon->legendary;
}

int pokemon_seen(Pokemon pokemon) {
  return pokemon->seen;
}

int pokemon_captured(Pokemon pokemon) {
  return pokemon->captured;
}

int set_pokemon_seen_true (Pokemon pokemon){
  pokemon->seen = 1;
  return pokemon->seen;
}
int set_pokemon_captured_true (Pokemon pokemon){
  pokemon->captured = 1;
  return pokemon->seen;
}