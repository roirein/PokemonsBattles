/*
 * Pokemon.c
 *
 *  Created on: Nov 25, 2019
 *      Author: ise
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Defs.h"

bilogic_info* create_bio_info(double height, double weight, int attack){
	bilogic_info *Pbio;
	Pbio = (bilogic_info*)malloc(sizeof(bilogic_info));
	if (Pbio == NULL)
		return NULL;
	Pbio->attack = attack;
	Pbio->height = height;
	Pbio->weight = weight;
	return (bilogic_info *) Pbio;
}

pokemon* Create_Pokemon(char *Pname, char *Pspeice, double Pheight,double Pweight,int attack , pokemon_type *Ptype_name){
	if (Pname == NULL || Pspeice == NULL || Ptype_name == NULL)
		return NULL;
	pokemon *Ppokemon;

	Ppokemon = (pokemon*)malloc(sizeof(pokemon));
	if (Ppokemon == NULL)
		return NULL;
	Ppokemon->name = (char*)malloc(strlen(Pname)*sizeof(char)+1);
	if (Ppokemon->name == NULL)
		return NULL;

	strcpy(Ppokemon->name,Pname);

	Ppokemon->specie = (char*)malloc(strlen(Pspeice)*sizeof(char)+1);

	if (Ppokemon->specie == NULL)
		return NULL;

	strcpy(Ppokemon->specie,Pspeice);
	Ppokemon->type = Ptype_name;
	Ppokemon->type->number_of_type++;
	Ppokemon->bio =create_bio_info(Pheight,Pweight,attack);

return (pokemon*)Ppokemon;
}

pokemon_type* create_type(char *type){
	pokemon_type *ptype;

	ptype = (pokemon_type*)malloc(sizeof(pokemon_type));
	if (ptype == NULL)
		return NULL;
	ptype->type_name= (char*)malloc(strlen(type)*sizeof(char)+1);
	if (ptype-> type_name == NULL)
		return NULL;

	strcpy(ptype->type_name,type);
	ptype->number_of_type = 0;

	ptype->effective_against_me = NULL;
	ptype->me_size = 0;
	ptype->effective_against_other = NULL;
	ptype->other_size = 0;


	return (pokemon_type *) ptype;
}

void free_bilogic_info(bilogic_info* info){
	free(info);
}


void free_pokemon(element e){
	pokemon *ppokemon = (pokemon*)e;
	ppokemon->type->number_of_type--;
	free_bilogic_info(ppokemon->bio);
	ppokemon->bio = NULL;
	free(ppokemon->specie);
	ppokemon->specie=NULL;
	free(ppokemon->name);
	free(ppokemon->specie);
	ppokemon->type = NULL;
	free(ppokemon);
	ppokemon = NULL;
}


status add_to_against_me(pokemon_type * type_A, pokemon_type * type_B){
	if (type_A == NULL || type_B == NULL){
		 return failure;
	}
     if (type_A -> me_size == 0){
    	 type_A->effective_against_me =(pokemon_type**) malloc(sizeof(pokemon_type*));
    	 if (type_A->effective_against_me == NULL){
    		 return failure;
    	 }
    	 type_A->effective_against_me[0] = type_B;
     }
     else{
         if (search_type(type_B->type_name,type_A->effective_against_me,type_A->me_size) != -1){//type didn't exist in the list
        	 return failure;
         }
    	 type_A->effective_against_me = (pokemon_type**)realloc(type_A->effective_against_me,sizeof(pokemon_type*)*(type_A->me_size+1));
    	 if (type_A->effective_against_me == NULL){
    		 return failure;
    	 }
    	 type_A->effective_against_me[type_A->me_size]= type_B;
     }
     type_A->me_size++;
     return success;
}
status add_to_against_other(pokemon_type * type_A, pokemon_type * type_B){
	if (type_A == NULL || type_B == NULL){
		 return failure;
	}
    if (type_A -> effective_against_other == NULL){
    	 type_A->effective_against_other =(pokemon_type**) malloc(sizeof(pokemon_type*));
    	 if (type_A->effective_against_other == NULL){
    		 return failure;
    	 }
   	     type_A->effective_against_other[0] = type_B;

    }
    else{
     if (search_type(type_B->type_name,type_A->effective_against_other,type_A->other_size) != -1){//type didn't exist in the list
    	 return failure;
     }
   	 type_A->effective_against_other = (pokemon_type**)realloc(type_A->effective_against_other,sizeof(pokemon_type*)*(type_A->other_size+1));
	 if (type_A->effective_against_other == NULL){
		 return failure;
	 }
   	 type_A->effective_against_other[type_A->other_size] = &(*type_B);

    }
    type_A->other_size++;
    return success;
}

status delete_from_me(pokemon_type * type_A, char* type_B){
	if (type_A == NULL || type_B == NULL){
		 return failure;
	}
	int i;
	int point;
	bool flag = false;
	for (i = 0; i < type_A->me_size;i++){
		if (strcmp(type_A->effective_against_me[i]->type_name, type_B) == 0){
			flag = true;
			point = i;
			break;
		}
	}

	if (!flag)
		return failure;
	for (point = i;point < type_A->me_size-1;point++){
		type_A->effective_against_me[point] = type_A->effective_against_me[point+1];
	}
	type_A->effective_against_me[type_A->me_size-1] = NULL;
	type_A->effective_against_me = (pokemon_type**)realloc(type_A->effective_against_me,sizeof(pokemon_type*)*(type_A->me_size-1));
	if (type_A->effective_against_me == NULL && type_A->me_size != 1){
		 return failure;
	 }
    type_A->me_size--;
	return success;
}

status delete_from_other(pokemon_type * type_A, char * type_B){
	if (type_A == NULL || type_B == NULL){
		 return failure;
	}
	int i,point;
	bool flag = false;
	for (i = 0; i < type_A->other_size;i++){
		if (strcmp(type_A->effective_against_other[i]->type_name, type_B) == 0){
			flag = 1;
			point = i;
			break;
		}
	}
	if (!flag)
		return failure;
	for (point = i;point < type_A->other_size-1;point++){
		type_A->effective_against_other[point] = type_A->effective_against_other[point+1];
	}
	type_A->effective_against_other[type_A->other_size-1] = NULL;
	type_A->effective_against_other = (pokemon_type**)realloc(type_A->effective_against_other,sizeof(pokemon_type*)*(type_A->other_size-1));
	if (type_A->effective_against_other == NULL && type_A->other_size != 1){
		 return failure;
	 }
	type_A->other_size--;
    return success;
}

status print_pokemon(element e){
	pokemon *p_pokemon = (pokemon*)e;
	printf("%s%s\n",p_pokemon->name," :");
	printf("%s, %s Type.\n",p_pokemon->specie, p_pokemon->type->type_name);
	printf("Height: %.2f m    ",p_pokemon->bio->height);
	printf("Weight: %.2f kg    ",p_pokemon->bio->weight);
	printf("Attack: %d\n\n",p_pokemon->bio->attack);
	return success;
}

status print_pokemon_type(pokemon_type * type){
	if (type == NULL)
		return failure;
	printf("Type %s -- %d pokemons\n",type->type_name,type->number_of_type);
	if (type->me_size > 0){
	   printf("\tThese types are super-effective against ");
	   printf("%s:",type->type_name);
	   int i;
	   for (i = 0; i<type->me_size-1;i++){
		   printf("%s",type->effective_against_me[i]->type_name);
		   printf(" ,");
	   }
	   printf("%s\n",type->effective_against_me[type->me_size-1]->type_name);
	}
	if (type->other_size > 0){
		printf("\t%s ",type->type_name);
	    printf("moves are super-effective against:");
		int i;
		for (i = 0; i<type->other_size-1;i++){
		    printf("%s",type->effective_against_other[i]->type_name);
		    printf(" ,");
		  }
	    printf("%s\n",type->effective_against_other[type->other_size-1]->type_name);
		}
	printf("\n");
	return success;

}

void empty_list(pokemon_type * type){
	while(type->me_size > 0){
		delete_from_me(type, type->effective_against_me[type->me_size-1]->type_name);

	}
	while(type->other_size > 0){
		delete_from_other(type, type->effective_against_other[type->other_size - 1]->type_name);
	}
}

void free_type(pokemon_type * type){
	free(type->type_name);
	free(type);
}


int search_type(char* type, pokemon_type ** types, int size){
	if (types == NULL){
		return -1;
	}
	int j = -1;
	int i;
	for (i = 0;i<size;i++){
		if (strcmp(type, types[i]->type_name) == 0){
			j = i;
			break;
		}
	}
	return j;

}


char * getType(element p){
	pokemon *p1 = (pokemon*)p;
	return p1->type->type_name;
}


element copyPokemon(element elem){
	pokemon *p = (pokemon*)elem;
	pokemon * newPokemon = Create_Pokemon(p->name,p->specie,p->bio->height,p->bio->weight,p->bio->attack,p->type);
	if (newPokemon != NULL){
		return newPokemon;
	}
	else
		return NULL;
}

int equalPokemon(element elem1,element elem2){
    pokemon * p1 = (pokemon*)elem1;
    pokemon * p2 = (pokemon*)elem2;
	if (p1 == NULL && p2 == NULL){
		return -2;
	}
	if (p1 != NULL && p2 == NULL){
		return 1;
	}
	if (p1 == NULL && p2 != NULL){
		return -1;
	}
	if (p1->bio->attack > p2->bio->attack){
		return 1;
	}
	else if (p1->bio->attack == p2->bio->attack){
		return 0;
	}
	else
		return -1;

}


int getAttackFunction1(element elem1,element elem2,int* attackFirst, int* attackSecond){
	pokemon* poke1 = (pokemon*)elem1;
	pokemon* poke2 = (pokemon*)elem2;
	*attackFirst = poke1->bio->attack;
	*attackSecond = poke2->bio->attack;
	pokemon_type** effective1 = poke1->type->effective_against_me;
	pokemon_type** effective2 = poke1->type->effective_against_other;
	pokemon_type** effective3 = poke2->type->effective_against_me;
	pokemon_type** effective4 = poke2->type->effective_against_other;
	int number2 = poke1->type->other_size;
	int number1 = poke1->type->me_size;
	int number3 = poke2->type->me_size;
	int number4 = poke2->type->other_size;
	char * name_type1 =getType(poke1);
	char * name_type2 =getType(poke2);
	int tmp = search_type(name_type2,effective1,number1);//search elem2 in effective against me of elem1
	int tmp1 = search_type(name_type1,effective4,number4);//search elem1 in effective against other of elem2
	if(tmp!=-1 || tmp1 != -1 ){
		*attackFirst -= 10;
	}
	int tmp2 = search_type(name_type1,effective3,number3);//search elem1 in effective against other of elem2
	int tmp3 = search_type(name_type2,effective2,number2);
	if(tmp2!=-1 || tmp3 != -1){
		*attackSecond -= 10;
	}
	return *attackFirst-*attackSecond;
}




