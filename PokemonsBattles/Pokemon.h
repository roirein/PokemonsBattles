/*
 * Pokemon.h
 *
 *  Created on: Nov 25, 2019
 *      Author: ise
 */

#ifndef POKEMON_H_
#define POKEMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct bilogic_info{
	double height;
	double weight;
	int attack;
}bilogic_info;

typedef struct pokemon_type{
	char *type_name;
	int number_of_type;
	struct pokemon_type **effective_against_me;
	int me_size; // number of types in effective against me list
	struct pokemon_type **effective_against_other;
	int other_size; // number of types in effective against other list
}pokemon_type;

typedef struct pokemon{
	char *name;
	char *specie;
	bilogic_info *bio;
	pokemon_type *type;
}pokemon;
/* initialize biologic info about the pokemon */
bilogic_info* create_bio_info(double , double , int );
/* initialize the pokemon */
pokemon* Create_Pokemon(char *, char *, double ,double ,int  , pokemon_type*);
/* initialize the pokemon type */
pokemon_type* create_type(char *);
/* destroy the pokemon, free all the fields of pokemon */
void free_pokemon(element e );
/* add pokemon type to effective against me list */
status add_to_against_me(pokemon_type * , pokemon_type * );
/* add pokemon type to effective against other list */
status add_to_against_other(pokemon_type * , pokemon_type * );
/* remove pokemon type from effective against me list */
status delete_from_me(pokemon_type * , char  * );
/* remove pokemon type from effective against other list */
status delete_from_other(pokemon_type * , char * );
/* print the pokemon and the information about it */
status print_pokemon(element p );
/* print the pokemon type and the information about it */
status print_pokemon_type(pokemon_type * );
/* destroy effective against me and other lists in pokemon type */
void empty_list(pokemon_type * );
/*destroy pokemon type object */
void free_type(pokemon_type* );
/*searching type in types array */
int search_type(char* , pokemon_type ** , int );
char * getType(element p);
int getAttackFunction1(element elem1,element elem2,int* attackFirst, int* attackSecond);
element copyPokemon(element elem);
int equalPokemon(element elem1,element elem2);
#endif /* POKEMON_H_ */
