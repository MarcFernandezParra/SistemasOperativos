#ifndef _POKEMON_H_
	#define _POKEMON_H_
	typedef struct pokemon_info *Pokemon;
	Pokemon new_pokemon(int pokemon_id, char *name, char **types, 
                    int total, int hp, int attack, int defense, 
                    int spAttack, int spDefense, int speed, int generation, 
                    int legendary, int seen, int captured);
	int pokemon_id(Pokemon pokemon);
	char *pokemon_name(Pokemon pokemon);
	char **pokemon_types(Pokemon pokemon);
	int pokemon_total(Pokemon pokemon);
	int pokemon_hp(Pokemon pokemon);
	int pokemon_attack(Pokemon pokemon);
	int pokemon_defense(Pokemon pokemon);
	int pokemon_spAttack(Pokemon pokemon);
	int pokemon_spDefense(Pokemon pokemon);
	int pokemon_speed(Pokemon pokemon);
	int pokemon_generation(Pokemon pokemon);
	int pokemon_legendary(Pokemon pokemon);
	int pokemon_seen(Pokemon pokemon);
	int pokemon_captured(Pokemon pokemon);	
	int set_pokemon_seen_true (Pokemon pokemon);
	int set_pokemon_captured_true (Pokemon pokemon);
#endif
