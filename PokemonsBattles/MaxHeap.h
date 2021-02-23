/*
 * MaxHeap.h
 *
 *  Created on: Dec 14, 2019
 *      Author: ise
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "Defs.h"
typedef struct Heap_t* heap;
heap createHeap(int max_size,char * name,copyFunction copyfunc, freeFunction freefunc,equalFunction eqfunc,printFunction printfunc);
status destroyHeap(heap Heap);
status insertToHeap(heap Heap, element elem);
status printHeap(heap Heap);
element PopMaxHeap(heap Heap);
element TopMaxHeap(heap Heap);
char * getHeapId(heap Heap);
int getHeapCurrentSize(heap Heap);
status comp1(element hp, element name);
element copyHeap1(element hp);
int equalHeap(element elem1, element elem2);

#endif /* MAXHEAP_H_ */
