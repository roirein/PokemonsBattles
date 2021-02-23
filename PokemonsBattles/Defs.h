/*
 * Defs.h
 *
 *  Created on: Dec 1, 2019
 *      Author: ise
 */

#ifndef DEFS_H_
#define DEFS_H_
typedef enum e_bool{false,true} bool;
typedef enum e_status{success,failure} status;
typedef void* element;
typedef element (*copyFunction)(element);
typedef status (*freeFunction)(element);
typedef status (*printFunction)(element);
typedef int (*equalFunction)(element,element);
typedef status (*searchFunction)(element,element);
typedef char* (*getCategoryFunction)(element);
typedef int (*getAttackFunction)(element firstElem,element secondElem, int* attackFirst, int* attackSecond);
typedef status (*comp)(element hp,element name);
typedef element (*copyHeapFunction)(element);
typedef status (*printHeapFunction)(element);
typedef status (*freeHeapFunction)(element);
typedef int (*equalHeapFunction)(element elem1, element elem2);
typedef void (*swapFunction)(element elem1, element elem2);

#endif /* DEFS_H_ */
