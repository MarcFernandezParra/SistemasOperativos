#ifndef _POKEDEX_H_
    #define _POKEDEX_H_
    typedef struct pokemon_info *Pokemon;
    int add_pokemon(char *line);
    int remove_pokemon();
    int show_pokemon(int position);
    int init_pokedex();
#endif // _POKEDEX_H_