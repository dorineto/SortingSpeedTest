#ifndef _CONFIGTEST_H_
#define _CONFIGTEST_H_

#include <stdlib.h>
#include "str.h"

#define elem str
#include "list.h"

/* Structs and Macros*/

typedef struct{
	int quantTent;
	list *algSort;
	list *arqLoad;
} configTest;

/* Function definition */

bool initConfigTest(configTest **ct);

/* Function implementation */

bool initConfigTest(configTest **ct){
	*ct = (configTest *)malloc(sizeof(configTest));
	if(*ct == NULL) return false;
	
	(*ct)->algSort = (list *)malloc(sizeof(list));
	if(!initList((*ct)->algSort, 3, 3)) return false;
	
	(*ct)->arqLoad = (list *)malloc(sizeof(list));
	if(!initList((*ct)->arqLoad, 3, 3)) return false;
	
	return true;
}

#endif