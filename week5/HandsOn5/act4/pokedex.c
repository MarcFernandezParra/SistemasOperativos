#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "pokemon.h"
#include "pokedex.h"

Pokemon pokedex[151];

void readcsv() {

  FILE* f = fopen("./pokemon.csv", "r");

  if(!f){
    perror("El fitxer no s'obre");
  }

  char *name;
  char *types[2];
  int id, total, hp, attack, defense, spAttack, spDefense, speed, generation, legendary;
  char buf[151];
  int i = 0;

  while (fgets(buf, 151, f) != NULL) {

    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
      buf[strlen (buf) - 1] = '\0';
    }
  
    id = atoi(strtok(buf, ","));
    name = strdup(strtok(NULL, ","));
    types[0] = strdup(strtok(NULL, ","));
    types[1] = strdup(strtok(NULL, ","));
    total = atoi(strtok(NULL, ","));
    hp = atoi(strtok(NULL, ","));
    attack = atoi(strtok(NULL, ","));
    defense = atoi(strtok(NULL, ","));
    spAttack = atoi(strtok(NULL, ","));
    spDefense = atoi(strtok(NULL, ","));
    speed = atoi(strtok(NULL, ","));
    generation = atoi(strtok(NULL, ","));
    legendary = atoi(strtok(NULL, ","));

    pokedex[i] = new_pokemon(id, name, types, total, hp, attack, defense, 
                             spAttack, spDefense, speed, generation, 
                             legendary, 0, 0);                       

    i++;

  }

  fclose(f);

}

int show_pokemon(int position) {
  char s[200];

  sprintf(s, "\n=========================\n");
  write(1, s, strlen(s));

  sprintf(s, "== ID: %d\n", pokemon_id(pokedex[position]));
  write(1, s, strlen(s));

  sprintf(s, "== Name: %s\n", pokemon_name(pokedex[position]));
  write(1, s, strlen(s));

  sprintf(s, "== Types: %s and %s\n", pokemon_types(pokedex[position])[0], pokemon_types(pokedex[position])[1]);
  write(1, s, strlen(s));

  sprintf(s, "=========================\n\n");
  write(1, s, strlen(s));
  
  /*
  printf("== Total: %d\n", pokemon_total(pokedex[position]));
  printf("== HP: %d\n", pokemon_hp(pokedex[position]));
  printf("== Attack: %d\n", pokemon_attack(pokedex[position]));
  printf("== Defense: %d\n", pokemon_defense(pokedex[position]));
  printf("== Special Attack: %d\n", pokemon_spAttack(pokedex[position]));
  printf("== Special Defense: %d\n", pokemon_spDefense(pokedex[position]));
  printf("== Speed: %d\n", pokemon_speed(pokedex[position]));
  printf("== Generation: %d\n", pokemon_generation(pokedex[position]));
  printf("== Legendary: %d\n", (pokemon_generation(pokedex[position]) == 1 ? "Yes" : "No"));
  printf("== Seen: %d\n", (pokemon_seen(pokedex[position]) == 1 ? "Yes" : "No"));
  printf("== Captured: %d\n", (pokemon_captured(pokedex[position]) == 1 ? "Yes" : "No"));
  printf("=============================\n");
  */
  
  return EXIT_SUCCESS;
}

int init_pokedex() {
  readcsv();

  return EXIT_SUCCESS;
}