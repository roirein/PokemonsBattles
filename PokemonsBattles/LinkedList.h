/*
 * LinkedList.h
 *
 *  Created on: Dec 10, 2019
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include "Defs.h"
typedef struct LinkedList_t* LinkedList;

LinkedList createLinkedList(copyFunction copyfunc, freeFunction freefunc,equalFunction eqfunc,printFunction printfunc, searchFunction sfunc);
status destroyList(LinkedList list);
status appendNode(LinkedList list, element elem);
status deleteNode(LinkedList list, element elem);
status displayList(LinkedList list);
element searchByKeyInList(LinkedList list, element elem);

#endif /* LINKEDLIST_H_ */
