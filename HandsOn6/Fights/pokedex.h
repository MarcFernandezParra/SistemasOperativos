#ifndef _POKEDEX_H_
    #define _POKEDEX_H_
	typedef struct pokemon_info *Pokemon;
	int show_pokemon(int position);
    int init_pokedex();
    Pokemon get_pokemon(int position);
    void create_csv();
#endif // _POKEDEX_H_