/*
 * BattleByCategory.c
 *
 *  Created on: Dec 20, 2019
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "MaxHeap.h"
#include "Defs.h"
#include "Pokemon.h"
#include "BattleByCategory.h"
#include <string.h>

struct battle_s{
	int num_of_categories;
	int category_max_size;//maximum objects in one category
	LinkedList list;
	copyFunction copyElement;
	freeFunction freeElement;
	equalFunction eqfunction;
	printFunction printfunc;
	getCategoryFunction categoryFunction;
	getAttackFunction attackfunction;
	char ** categories;
};

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){
	if(capacity == 0 || numberOfCategories == 0 || copyElement == NULL || freeElement == NULL || equalElement == NULL || printElement == NULL || getCategory == NULL || getAttack ==NULL){
		return NULL;
	}
	Battle PBattle  = (Battle) malloc (sizeof(struct battle_s));
	if (PBattle == NULL){
		printf (" No memory available .\n");
				return NULL;
	}
	LinkedList link= createLinkedList(copyHeap1, (freeHeapFunction)destroyHeap,equalHeap,(printHeapFunction)printHeap,comp1);
	PBattle->list = link;
	PBattle->attackfunction = getAttack;
	PBattle->categoryFunction = getCategory;
	PBattle->category_max_size = capacity;
	PBattle->num_of_categories = numberOfCategories;
	PBattle->copyElement = copyElement;
	PBattle->eqfunction = equalElement;
	PBattle->freeElement = freeElement;
	PBattle->printfunc = printElement;
	char delim[]=",";
	char temp[strlen(categories)];
	strcpy(temp,categories);
	PBattle->categories = (char**)malloc(sizeof(char*)*numberOfCategories);
	if(PBattle == NULL){
		destroyList(PBattle->list);
		free(PBattle);
	}
	char * ptr = strtok(temp,delim);
	int i = 0;
	while(ptr != NULL){
		heap Pheap= createHeap(capacity,ptr,copyElement, freeElement, equalElement, printElement);
		appendNode(PBattle->list,Pheap);
		destroyHeap(Pheap);
		PBattle->categories[i] = (char*)malloc(sizeof(char)*strlen(ptr)+1);
		if(PBattle->categories[i] == NULL){
			destroyList(PBattle->list);
			free(PBattle);
		}
		strcpy(PBattle->categories[i],ptr);
		ptr = strtok(NULL,delim);
		i++;
	}
	return PBattle;

}


status destroyBattleByCategory(Battle b){
	if (b ==NULL)
		return failure;
	status s = destroyList(b->list);
	if (s == failure)
		return failure;
	int i;
	for (i = 0; i < b->num_of_categories;i++){
		free(b->categories[i]);
	}
	free(b->categories);
	free(b);
	return success;

}

status insertObject(Battle b, element elem){
	if (b == NULL || elem == NULL){
		return failure;
	}
	char * category = b->categoryFunction(elem);
	element cat = (element)category;
	heap temp = searchByKeyInList(b->list, cat);
	if (temp == NULL){
		return failure;
	}
	if (getHeapCurrentSize(temp) == b->category_max_size)
		return failure;
	insertToHeap(temp,elem);
	return success;
}

void displayObjectsByCategories(Battle b){
	if (b == NULL){
		return;
	}
	displayList(b->list);

}

element removeMaxByCategory(Battle b,char* category){
	if (b == NULL){
		return NULL;
	}
	element cat = (element)category;
	heap temp = searchByKeyInList(b->list, cat);
	if (temp == NULL){
		return NULL;
	}
	if (getHeapCurrentSize(temp) == 0){
		return NULL;
	}
	return PopMaxHeap(temp);


}

int getNumberOfObjectsInCategory(Battle b,char* category){
	if (b == NULL){
		return 0;
	}
	element cat = (element)category;
	heap temp = searchByKeyInList(b->list, cat);
	if (temp == NULL){
		return 0;
	}
	return getHeapCurrentSize(temp);
}

element fight(Battle b,element elem){
	int i = 1;
	int attack1 = 0;
	int attack2 = 0;
	element temp = (element)b->categories[0];
	element hp_tmp = searchByKeyInList(b->list,temp);
	while (getHeapCurrentSize(hp_tmp) == 0 && i < b->num_of_categories){
		element temp = (element)b->categories[i];
		hp_tmp = searchByKeyInList(b->list,temp);
		i++;
	}
	int j;
	if (getHeapCurrentSize(hp_tmp) == 0){
	    return NULL;
	}
	element TmpMax = TopMaxHeap(hp_tmp);
	int temp_dif = b->attackfunction(elem,TopMaxHeap(hp_tmp),&attack1,&attack2);
	int a1 = attack1;
	int a2 = attack2;
	for(j=i;j<b->num_of_categories;j++){
		element temp1 = (element)b->categories[j];
		heap hp_tmp1 = searchByKeyInList(b->list,temp1);
		if (getHeapCurrentSize(hp_tmp1) == 0){
			continue;
		}
		int r = b->attackfunction(elem,TopMaxHeap(hp_tmp1),&attack1,&attack2);
		if (r < temp_dif){
			temp_dif = r;
			TmpMax = TopMaxHeap(hp_tmp1);
			a1 = attack1;
			a2 = attack2;
		}
	}
	
	element winner;
	if (temp_dif > 0){
		winner = elem;
	}
	else{
		winner = TmpMax;
	}
	printf("The final battle between:\n");
	b->printfunc(elem);
	printf("In this battle his attack is :%d\n\n",a1);
	printf("against ");
	b->printfunc(TmpMax);
	printf("In this battle his attack is :%d\n\n",a2);
	if (temp_dif == 0){
		printf("IT IS A DRAW.\n");
		return TmpMax;
	}
	printf("THE WINNER IS:\n");
	b->printfunc(winner);
        TmpMax = NULL;
	return winner;
}


