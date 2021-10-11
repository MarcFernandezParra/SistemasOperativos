#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "pokedex.h"

struct pokemon {
  int pokemon_id; 
  char *name;
  double height;
  double weight;
};
struct pokemon pokedex[151];

void readcsv(){  
  
  FILE* f = fopen("./pokemon.csv", "r");

  if(!f){
    perror("El fitxer no s'obre");
  }

  char *info;
  char buf[151];
  int i = 0;

  while (fgets(buf, 151, f) != NULL) {

    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n')) {
      buf[strlen (buf) - 1] = '\0';
    }
  
    info = strtok(buf, ",");
    pokedex[i].pokemon_id = atoi(info);
    info = strtok(NULL, ",");
    pokedex[i].name = strdup(info);
    info = strtok(NULL, ",");
    pokedex[i].weight = atof(info);
    info = strtok(NULL, "\n");
    pokedex[i].height = atof(info);

    i++;

  }

  fclose(f);

}



int add_pokemon(char *line) 
{ 
  struct pokemon readPoke;
  
  FILE* f = fopen("./pokemon.csv", "a");

  char tmpName[200];
  int pokemon_id;
  double height, weight;
  sscanf(line, "%d %s %lf %lf", &pokemon_id, tmpName, &height, &weight);
  readPoke = new_pokemon(pokemon_id, tempName, height, weight);
  
  
  fprintf(f, "%d,%s,%lf,%lf\n", readPoke.pokemon_id, readPoke.name, readPoke.height, readPoke.weight);
  
  fclose(f);

  return EXIT_SUCCESS;
}

int show_pokemon(int position) {
  printf("=====================\n");
  printf("== id: %d\n", pokedex[position].pokemon_id);
  printf("== name: %s\n", pokedex[position].name);
  printf("== weight: %lf\n", pokedex[position].weight);
  printf("== height: %lf\n", pokedex[position].height);
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

