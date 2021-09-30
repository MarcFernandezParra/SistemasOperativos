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
      
      if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
        buf[strlen (buf) - 1] = '\0';

        info = strtok(buf, ",");
        
        pokedex[i].pokemon_id = atoi(info);
        pokedex[i].name = strtok(buf, ",");
        info = strtok(buf, ",");
        pokedex[i].weight = atof(info);
        info = strtok(buf, "\n");
        pokedex[i].height = atof(info);
        i++;
    }
    
  fclose(f);
}



int add_pokemon(char *line) 
{ 
  struct pokemon readPoke;
  
  FILE* my_file = fopen("pokemon.csv", "w");
  sscanf(line, "%d %s %lf %lf", readPoke.pokemon_id, readPoke.name, 
                readPoke.height, readPoke.weight);
  fprintf(my_file, "%d, %s, %lf, %lf", readPoke.pokemon_id, readPoke.name, 
                readPoke.height, readPoke.weight);
  fclose(my_file);

  return EXIT_SUCCESS;
}

int show_pokemon(int position) {
  //printf("[show_pokemon]: @NOT IMPLEMENTED \n");
  return EXIT_SUCCESS;
}

int remove_pokemon() {
  //printf("[remove_pokemon]: @NOT IMPLEMENTED \n");
  return EXIT_SUCCESS;
}


int init_pokedex() {
  readcsv();
  printf("%s", pokedex[0].name);
  return EXIT_SUCCESS;
}

