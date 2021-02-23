/*
 * MainSecond.c
 *
 *  Created on: Dec 20, 2019
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Defs.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "BattleByCategory.h"

void free_arr(int ,pokemon_type** );
void free_arr(int size,pokemon_type** types){
	int i,j;
	for (j = 0;j < size; j++){
		empty_list(types[j]);
	}
	for(i=0;i<size;i++){
		free_type(types[i]);
	}
	free(types);

}

int main(int argc, char * argv[]) {


	FILE *in_fp;
	char buffer[300];//buffer for the line length and the user input
	int numberOfTypes,CapacityInType;
	sscanf(argv[1],"%d",&numberOfTypes);
	sscanf(argv[2],"%d",&CapacityInType);
	pokemon_type ** types;
	types = (pokemon_type**)malloc(sizeof(pokemon_type*) * numberOfTypes);
	if (types == NULL){
		printf (" No memory available .\n");
		free(types);
		return 0;

	}
    in_fp = fopen(argv[3],"r");
    if (in_fp == NULL){
    	return 0;
    }
    char *line = fgets(buffer, 300, in_fp);//first line of the file
    	while(!strstr(line,"Types")){
    		line = fgets(buffer, 300, in_fp);
    	}
	line = fgets(buffer, 300, in_fp);
	line[strlen(line)-2] = 0;
	char * temp = (char*)malloc(sizeof(char)*strlen(line)+1);
	if(temp == NULL){
		printf (" No memory available .\n");
		return 0;
	}
    strcpy(temp,line);
	char * delimeter = ",";
	char *splited = strtok(line,delimeter);
	int k = 0;
	if (numberOfTypes != 0){
	    while (k < numberOfTypes){
	         pokemon_type * type = create_type(splited);
	         types[k] = type;
		     splited = strtok(NULL,delimeter);
		     k++;
	    }
	Battle battle = createBattleByCategory(CapacityInType,numberOfTypes,temp,(equalFunction)equalPokemon,copyPokemon,(freeFunction)free_pokemon,getType,getAttackFunction1,(printFunction)print_pokemon);
    free(temp);
    line = fgets(buffer, 300, in_fp);
    while (buffer[0] == '\t'){
        char* deli = " ";
        line++;
        char* temp1 = (char*)malloc(strlen(line)*sizeof(char)+1);
        if(temp1 == NULL){
        	printf (" No memory available .\n");
        	destroyBattleByCategory(battle);
        	free(types);
        	free(temp1);
        	return 0;
        }
        strcpy(temp1,line);
        char * split = strtok(temp1,deli);
        int ind = search_type(split,types,numberOfTypes);
        line += strlen(temp1)+1;
        char* temp2 = (char*)malloc(strlen(line)*sizeof(char)+1);
        if(temp2== NULL){
        	printf (" No memory available .\n");
        	destroyBattleByCategory(battle);
        	free(types);
        	free(temp1);
        	free(temp2);
        	return 0;
        }
        strcpy(temp2,line);
        char *opt1 = "effective-against-me";
        char *opt2 = "effective-against-other";
        char* deli1 = ":";
        char * split1 = strtok(temp2,deli1);
  	    line += strlen(split1)+1;
  	    char* delimeter1 = ",";
  	    char *splited1 = strtok(line,delimeter1);
        if (strcmp(split1,opt1) == 0){
     	    while(splited1[strlen(splited1) - 1] != '\n'){
     		     int ind1 = search_type(splited1,types,numberOfTypes);
     		     add_to_against_me(types[ind],types[ind1]);
     		     splited1 = strtok(NULL,delimeter1);
     	    }
     	   splited1[strlen(splited1) - 2] = 0;
  		   int ind2 = search_type(splited1,types,numberOfTypes);
     	   add_to_against_me(types[ind],types[ind2]);
          }

        if (strcmp(split1,opt2) == 0){
     	    while(splited1[strlen(splited1) - 1] != '\n'){
     		     int ind1 = search_type(splited1,types,numberOfTypes);
     		     add_to_against_other(types[ind],types[ind1]);
     		     splited1 = strtok(NULL,delimeter1);
     	}
     	    splited1[strlen(splited1) - 2] = 0;
  		    int ind2 = search_type(splited1,types,numberOfTypes);
        	add_to_against_other(types[ind],types[ind2]);

     }
          free(temp1);
          free(temp2);
          line = fgets(buffer, 300, in_fp);


    }
    line = fgets(buffer, 300, in_fp);
    while(line != NULL){
    	int number;
    	char* dell = ",";
    	char * name;
    	char * specie;
    	double height;
    	double weigth;
    	int attack;
    	char * type;
    	char * spl = strtok(line,dell);
    	for (number = 1; number < 7; number++){
    		switch(number){
    		case 1:
    			name = (char * )malloc(strlen(spl)*sizeof(char)+1);
    			if (name == NULL){
    				printf (" No memory available .\n");
    		        destroyBattleByCategory(battle);
    		        free(types);
    		        free(name);
    		        return 0;
    			}
    			strcpy(name,spl);
    			break;
    		case 2:
    		    spl = strtok(NULL,dell);
    			specie = (char *)malloc((strlen(spl)*sizeof(char)+1));
    			if (specie == NULL){
    				printf (" No memory available .\n");
    				destroyBattleByCategory(battle);
    				free(types);
    				free(name);
    				free(specie);
    				return 0;
			}
    			strcpy(specie,spl);
    			break;
    		case 3:
    			spl = strtok(NULL,dell);
    			height = (double)atof(spl);
    			break;
    		case 4:
    			spl = strtok(NULL,dell);
    			weigth = (double)atof(spl);
    			break;
    		case 5:
    			spl = strtok(NULL,dell);
    			attack = atoi(spl);
    			break;
    		case 6:
    			spl = strtok(NULL,dell);
    			spl[strlen(spl) - 2] = 0;
    			type = (char * )malloc(sizeof(strlen(spl))+1);
    			if (type == NULL){
    				printf (" No memory available .\n");
        			destroyBattleByCategory(battle);
        			free(types);
        			free(name);
        			free(specie);
        			return 0;
    			}
    			strcpy(type,spl);
    			break;
    		}
    	}

    	int l = search_type(type, types,numberOfTypes);
    	pokemon * new_pokemon = Create_Pokemon(name,specie,height,weigth,attack,types[l]);
    	insertObject(battle,(element)new_pokemon);
 		if (new_pokemon == NULL){
 			printf("No memory available.");
 			destroyBattleByCategory(battle);
 			return 0;
 		}
    	free(name);
    	free(specie);
    	free(type);
    	free_pokemon((element)new_pokemon);
    	line = fgets(buffer, 300, in_fp);

    }
	fclose(in_fp);
	int ch = 0,x;
	char input[300];
	char type2[300];
	char name[300];
	char specie[300];
	float height;
	float weight;
	int attack;
	pokemon * new_poke1;
	while (ch != 9){
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove stronger Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");
		scanf("%s",input);
		ch = atoi(input);
		switch(ch){
		case 1:
			displayObjectsByCategories(battle);
			break;

		case 2:
			for(x = 0; x < numberOfTypes; x++){
				print_pokemon_type(types[x]);
			}
			break;

		case 3:
			printf("Please enter Pokemon type name:\n");
			scanf("%s", type2);
			int exist = search_type(type2,types,numberOfTypes);
			if (exist== -1){
				printf("Type name doesn't exist.\n");
				break;
			}
			if (getNumberOfObjectsInCategory(battle,type2) == CapacityInType){
				printf("Type at full capacity.\n");
				break;
			}
			printf("Please enter Pokemon name:\n");
			scanf("%s", name);
			printf("Please enter Pokemon species:\n");
			scanf("%s",specie);
			printf("Please enter Pokemon height:\n");
			scanf("%f", &height);
			printf("Please enter Pokemon weight:\n");
			scanf("%f", &weight);
			printf("Please enter Pokemon attack:\n");
			scanf("%d", &attack);
			pokemon * new_poke = Create_Pokemon(name,specie,height,weight,attack,types[exist]);
			element e = (element)new_poke;
			status s = insertObject(battle,e);
			if(s == success){
				printf("The Pokemon was successfully added.\n");
				print_pokemon(e);
			}
			free_pokemon((element)new_poke);
			break;

		case 4:
			printf("Please enter type name:\n");
			scanf("%s", type2);
			int exist1 = search_type(type2,types,numberOfTypes);
			if (exist1 == -1){
				printf("Type name doesn't exist.\n");
				break;
			}
			element temp = removeMaxByCategory(battle,type2);
			if (temp == NULL){
				printf("There is no Pokemon to remove.\n");
				break;
			}
			printf("the strongest Pokemon was removed:\n");
			print_pokemon(temp);
			free_pokemon(temp);
			break;



		case 5:
			printf("Please enter Pokemon type name:\n");
			scanf("%s", type2);
			int exist2 = search_type(type2,types,numberOfTypes);
			if (exist2 == -1){
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter Pokemon name:\n");
			scanf("%s", name);
			printf("Please enter Pokemon species:\n");
			scanf("%s",specie);
			printf("Please enter Pokemon height:\n");
			scanf("%f", &height);
			printf("Please enter Pokemon weight:\n");
			scanf("%f", &weight);
			printf("Please enter Pokemon attack:\n");
			scanf("%d", &attack);
			new_poke1 = Create_Pokemon(name,specie,height,weight,attack,types[exist2]);//problematic line
			element e1 = (element)new_poke1;
			printf("you choose to fight with:\n");
			print_pokemon(e1);
			element e2 = fight(battle,e1);
			if (e2 == NULL){
				printf("There are no Pokemons to fight against you.\n");
			}
			free_pokemon(e1);
			break;

		case 6:
			destroyBattleByCategory(battle);
			free_arr(numberOfTypes,types);
			printf("All the memory cleaned and the program is safely closed.\n");
			ch = 9;
			break;

		default:
			printf("Please choose a valid number.\n");


		}
	}
	}
}


