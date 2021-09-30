#ifndef _POKEDEX_H_
    #define _POKEDEX_H_
    int add_pokemon(char *line);
    int remove_pokemon();
    int show_pokemon(int position);
    int init_pokedex();
    typedef struct pokemon *Pokemon;    
    Pokemon new_pokemon(int pokemon_id, char *name, double height,double weight);
    int pokemon_id(Pokemon pokemon);
    char *pokemon_name(Pokemon pokemon);
    double pokemon_height(Pokemon pokemon);
    double pokemon_weight(Pokemon pokemon);
#endif // _POKEDEX_H_