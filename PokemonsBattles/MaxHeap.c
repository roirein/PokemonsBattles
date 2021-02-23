/*
 * MaxHeap.c
 *
 *  Created on: Dec 14, 2019
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "MaxHeap.h"
struct Heap_t{
	char *name;
	int size;
	element* array;
	copyFunction copyElement;
	freeFunction freeElement;
	equalFunction eqfunction;
	printFunction printfunc;
	int nextindex;
};
void heapify(heap Heap, int index);
void increase(heap Heap,int i,element e);
int parent(int);


heap createHeap(int max_size,char * name,copyFunction copyfunc, freeFunction freefunc,equalFunction eqfunc,printFunction printfunc){
	if (max_size == 0){
		return NULL;
	}
	heap max_heap = (heap)malloc(sizeof(struct Heap_t));
	if (max_heap == NULL){
		printf (" No memory available .\n");
		return NULL;
	}
	max_heap->name = (char *)malloc(strlen(name)*sizeof(char)+1);
	if (max_heap->name == NULL){
		printf (" No memory available .\n");
		free(max_heap);
		return NULL;
	}
	strcpy(max_heap->name ,name);
	max_heap->array = (element*)malloc(sizeof(element)*max_size);
	if (max_heap->array == NULL){
		printf (" No memory available .\n");
		free(max_heap->name);
		free(max_heap);
		return NULL;
	}
	max_heap->copyElement = copyfunc;
	max_heap->eqfunction = eqfunc;
	max_heap->printfunc = printfunc;
	max_heap->freeElement = freefunc;
	max_heap->size = max_size;
	max_heap->nextindex = 0;
	int i;
	for (i=0; i<max_size;i++){
		max_heap->array[i]=NULL;
	}
	return max_heap;
}

status destroyHeap(heap Heap){
	if (Heap == NULL)
		return failure;
	while (Heap->nextindex != 0){
		Heap->freeElement(PopMaxHeap(Heap));
	}
	free(Heap->name);
	free(Heap->array);
	free(Heap);
	return success;
}

void heapify(heap Heap,int index){
	int left = 2*index+1;
	int right = 2*index+2;
	int largest;
	if(left <= Heap->nextindex && Heap->eqfunction(Heap->array[left],Heap->array[index]) > 0){
		largest = left;
	}
	else{
		largest = index;
	}
	if(right <= Heap->nextindex && Heap->eqfunction(Heap->array[right],Heap->array[largest]) > 0){
		   largest = right;
	}
	if (largest != index){
		element temp = Heap->array[index];
		Heap->array[index] = Heap->array[largest];
		Heap->array[largest] = temp;
		heapify(Heap,largest);
	}

}

void increase(heap hp,int i,element e){
	int parent1 = (i-1)/2;
	hp->array[i] = e;
	while(i >= 1 && hp->eqfunction(hp->array[i],hp->array[parent1]) == 1){
		element temp = hp->array[i];
		hp->array[i] = hp->array[parent1];
		hp->array[parent1] = temp;
		i = parent(i);
 		parent1 = parent1/2;
	}
}
status insertToHeap(heap Heap, element elem){
	if (Heap == NULL || elem == NULL){
		return failure;
	}
	if (Heap->nextindex == Heap->size){
		return failure;
	}
	else{
		element new = Heap->copyElement(elem);
		increase(Heap,Heap->nextindex,new);
		Heap->nextindex++;
	}
	return success;
}
int parent (int index){
	return index/2;
}
status printHeap(heap Heap){
	if (Heap == NULL){
		return failure;
	}
	int size = getHeapCurrentSize(Heap);
	element temp[size];
	printf("%s:\n",Heap->name);
	int i = 1;
	if (Heap->nextindex == 0){
		printf("No elements.\n\n");
		return success;
	}
	while (Heap->nextindex != 0){
		printf("%d. ",i);
		element temp1 = TopMaxHeap(Heap);
		Heap->printfunc(temp1);
		temp[i-1] = PopMaxHeap(Heap);
		i++;

	}
	for (i = 0;i<size;i++){
		insertToHeap(Heap,temp[i]);
		Heap->freeElement(temp[i]);
	}
	return success;


}

element PopMaxHeap(heap Heap){
	if (Heap == NULL || Heap->nextindex == 0){
		return NULL;
	}
	element temp = (element)Heap->array[0];
	Heap->array[0] = Heap->array[Heap->nextindex-1];
	Heap->nextindex--;
	heapify(Heap,0);
	return temp;
}


element TopMaxHeap(heap Heap){
	if (Heap == NULL)
		return NULL;
	if (Heap->array[0] == NULL)
		return NULL;
	return Heap->array[0];
}

char * getHeapId(heap Heap){
	if (Heap == NULL){
		return NULL;
	}
	return Heap->name;
}

int getHeapCurrentSize(heap Heap){
	return Heap->nextindex;
}

status comp1(element hp,element name){
	if (hp == NULL){
		return failure;
	}
	if (strcmp(getHeapId((heap)hp),(char*)name)== 0){
		return success;
	}
	return failure;
}

element copyHeap1(element hp){
    heap newHeap= (heap)hp;
    heap new_hp = createHeap(newHeap->size,newHeap->name, newHeap->copyElement, newHeap->freeElement,newHeap->eqfunction,newHeap->printfunc);
	if (new_hp!= NULL){
		return new_hp;
	}
	else
		return NULL;
}

int equalHeap(element elem1, element elem2){
	return strcmp(getHeapId((heap)elem1),getHeapId((heap)elem2));
}




