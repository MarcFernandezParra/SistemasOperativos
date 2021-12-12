#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pokemon.h"
#include "pokedex.h"

#define LOGNAME_SIZE 30
#define LOGNAME_FORMAT "./pokedex_%Y%m%d_%H%M%S"
Pokemon pokedex[151];

void create_csv(){
  FILE *f;
  static char name[LOGNAME_SIZE];
  time_t now = time(0);
  strftime(name, sizeof(name), LOGNAME_FORMAT, localtime(&now));

  f = fopen(name, "ab");

  for(int i = 0; i<151;i++){
    fprintf(f,"%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", pokemon_id(pokedex[i]), pokemon_name(pokedex[i]), 
    pokemon_types(pokedex[i])[0],
    pokemon_types(pokedex[i])[1],pokemon_hp(pokedex[i]), pokemon_attack(pokedex[i]), pokemon_defense(pokedex[i]),
    pokemon_spAttack(pokedex[i]), pokemon_spDefense(pokedex[i]), pokemon_speed(pokedex[i]), pokemon_generation(pokedex[i]),
    pokemon_legendary(pokedex[i]), pokemon_seen(pokedex[i]), pokemon_captured(pokedex[i])); 
  }

  fclose(f);
}

void readcsv() {

  FILE* f = fopen("./pokemon.csv", "r");

  if(!f){
    perror("El fitxer no s'obre");
  }

  char *name;
  char **types;
  int id, total, hp, attack, defense, spAttack, spDefense, speed, generation, legendary;
  char buf[151];
  int i;

  while (fgets(buf, 151, f) != NULL) {

    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
      buf[strlen (buf) - 1] = '\0';
    }

    types = (char **)malloc(2 * sizeof(char*));
  
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

Pokemon get_pokemon(int position){
  return pokedex[position];
}

int show_pokemon(int position) {
  char s[200];

  printf("\n=========================\n");
  printf("== ID: %d\n", pokemon_id(pokedex[position]));
  printf("== Name: %s\n", pokemon_name(pokedex[position]));
  printf("== Types: %s and %s\n", pokemon_types(pokedex[position])[0], pokemon_types(pokedex[position])[1]);
  printf("== Total: %d\n", pokemon_total(pokedex[position]));
  printf("== HP: %d\n", pokemon_hp(pokedex[position]));
  printf("== Attack: %d\n", pokemon_attack(pokedex[position]));
  printf("== Defense: %d\n", pokemon_defense(pokedex[position]));
  printf("== Special Attack: %d\n", pokemon_spAttack(pokedex[position]));
  printf("== Special Defense: %d\n", pokemon_spDefense(pokedex[position]));
  printf("== Speed: %d\n", pokemon_speed(pokedex[position]));
  printf("== Generation: %d\n", pokemon_generation(pokedex[position]));
  printf("== Legendary: %s\n", (pokemon_legendary(pokedex[position]) == 1 ? "Yes" : "No"));
  printf("== Seen: %s\n", (pokemon_seen(pokedex[position]) == 0 ? "No" : "Yes"));
  printf("== Captured: %s\n", (pokemon_captured(pokedex[position]) == 0 ? "No" : "Yes"));
  printf("=============================\n");
  
  return EXIT_SUCCESS;
}

int init_pokedex() {
  readcsv();

  return EXIT_SUCCESS;
}