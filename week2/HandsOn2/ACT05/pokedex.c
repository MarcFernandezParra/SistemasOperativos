#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "pokedex.h"
#include "pokemon.h"

Pokemon pokedex[151];

void readcsv(){  

  FILE* f = fopen("./pokemon.csv", "r");

  if(!f){
    perror("El fitxer no s'obre");
  }

  char* name;
  int id;
  double height, weight;

  char buf[151];
  int i = 0;

  while (fgets(buf, 151, f) != NULL) {

    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
      buf[strlen (buf) - 1] = '\0';
    }
  
    id = atoi(strtok(buf, ","));
    name = strdup(strtok(NULL, ","));
    weight = atof(strtok(NULL, ","));
    height = atof(strtok(NULL, ","));

    printf("%d\n", id);
    printf("%lf\n", weight);
    printf("%lf\n", height);
    printf("%s\n", name);

    pokedex[i] = new_pokemon(id, name, height, weight);

    i++;

  }

  fclose(f);

}



int add_pokemon(char *line) 
{ 
  Pokemon readPoke;
  
  FILE* f = fopen("./pokemon.csv", "a");

  char tmpName[200];
  int pokemon_id;
  double height, weight;
  sscanf(line, "%d %s %lf %lf", &pokemon_id, tmpName, &height, &weight);
  readPoke = new_pokemon(pokemon_id, tmpName, height, weight);
  
  fprintf(f, "%d,%s,%lf,%lf\n", 1, pokemon_name(readPoke), pokemon_height(readPoke), pokemon_weight(readPoke));
  
  fclose(f);

  return EXIT_SUCCESS;
}

int show_pokemon(int position) {
  printf("=====================\n");
  printf("== id: %d\n", pokemon_id(pokedex[position]));
  printf("== name: %s\n", pokemon_name(pokedex[position]));
  printf("== weight: %lf\n", pokemon_weight(pokedex[position]));
  printf("== height: %lf\n", pokemon_height(pokedex[position]));
  printf("=====================\n");
  return EXIT_SUCCESS;
}

int remove_pokemon() {
  //printf("[remove_pokemon]: @NOT IMPLEMENTED \n");
  return EXIT_SUCCESS;
}


int init_pokedex() {
  readcsv();
  return EXIT_SUCCESS;
}

