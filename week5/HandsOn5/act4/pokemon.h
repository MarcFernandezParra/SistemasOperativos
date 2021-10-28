#ifndef _POKEMON_H_
	#define _POKEMON_H_
	typedef struct pokemon_info *Pokemon;
	Pokemon new_pokemon(int pokemon_id, char *name, char **type, 
                    int total, int hp, int attack, int defense, 
                    int spAttack, int spDefense, int speed, int generation, 
                    int legendary, int seen, int captured);
	int pokemon_id(Pokemon pokemon);
	char *pokemon_name(Pokemon pokemon);
#endif
