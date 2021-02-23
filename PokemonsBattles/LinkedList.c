/*
 * LinkedList.c
 *
 *  Created on: Dec 10, 2019
 *      Author: ise
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Defs.h"

/*********Struts*********/
typedef struct Node_t{
	struct Node_t * next;
	element Data;
}Node;

struct LinkedList_t{
	Node* head;
	Node* tail;
	int size;
	copyFunction copyElement;
	freeFunction freeElement;
	equalFunction eqfunction;
	printFunction printfunc;
	searchFunction searchfunction;
};


Node * createNode(element elem);
void DestroyNode(Node *);

// create of node
Node * createNode(element elem){
	Node * node =NULL;
	node = (Node *)malloc(sizeof(Node));
	if (node == NULL){
		printf (" No memory available .\n");
		return NULL;
	}
	node->Data = elem;
	node->next = NULL;
	return node;
}

//free of node
void DestroyNode(Node * node){
	free(node);
	node = NULL;
	return;
}

LinkedList createLinkedList(copyFunction copyfunc, freeFunction freefunc,equalFunction eqfunc,printFunction pfunc, searchFunction sfunc){
	if (copyfunc == NULL || freefunc == NULL || eqfunc == NULL || pfunc == NULL || sfunc == NULL){
		return NULL;
	}
	LinkedList list  = (LinkedList) malloc (sizeof(struct LinkedList_t));
	if (list == NULL){
		printf (" No memory available .\n");
		return NULL;
	}
	list->head = NULL;
	list->size = 0;
	list->copyElement = copyfunc;
	list->freeElement = freefunc;
	list->eqfunction = eqfunc;
	list->printfunc = pfunc;
	list->searchfunction = sfunc;
	return list;
}

status destroyList(LinkedList list){
	if (list == NULL){
		return failure;
	}
	Node * temp1 = list->head;
	Node * temp2=NULL;
	while (temp1!= NULL){
		temp2 = temp1->next;
		deleteNode(list,temp1->Data);
		temp1 = temp2;
	}
	list->head = NULL;
	list->tail =NULL;
	free(list);
	list = NULL;
	return success;
}
//append node to the array
status appendNode(LinkedList list, element elem){
	if (list == NULL || elem == NULL){
		return failure;
	}
	element newelm = list->copyElement(elem);
	if(newelm == NULL)
		return failure;
	Node * NewNode = createNode(newelm);
	if (list->size == 0){
		list->head = NewNode;
		list->tail = NewNode;
	}
	else{
		list->tail->next = NewNode;
		list->tail = NewNode;
	}
	list->size++;
	return success;
}
//delete node from the list
status deleteNode(LinkedList list, element elem){
	if (elem == NULL || list == NULL || list->size==0){
		return failure;
	}
	Node * temp = list->head;
	Node * prev = NULL;

	if(list->eqfunction(temp->Data,elem) == 0){
		list->freeElement(temp->Data);
		temp->Data =NULL;
		list->head = temp->next;
		temp->next=NULL;
		DestroyNode(temp);
		list->size-=1;
		return success;
	}
	while(temp != NULL && list->eqfunction(temp->Data,elem) != 0){
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
		return failure;

	list->freeElement(temp->Data);
	temp->Data=NULL;
	prev->next = temp->next;
	temp->next =NULL;
	DestroyNode(temp);
	list->size--;
	return success;
}

status displayList(LinkedList list){
	if (list == NULL){
		return failure;
	}
	Node * temp = list->head;
	while(temp!= NULL){
		list->printfunc(temp->Data);
		temp = temp->next;
	}
	return success;
}

element searchByKeyInList(LinkedList list, element elem){
	if( list ==NULL || elem==NULL)
		return NULL;
	Node * temp =list->head;
	int i;
	for(i=0;i<list->size;i++){
			if(list->searchfunction(temp->Data,elem) == success)
				return temp->Data;
			temp=temp->next;
	}
	return NULL;
}

