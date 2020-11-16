/*
ANDRÉ GONÇALVES DE BRITO - RA: N487EF4
ALEX KATANOSAKA FREITAS - RA: N478DJ0
BEATRIZ SILVA DE SOUSA - RA: N4758H8
BRUNO VICTORINO - RA: D986EB5
DORIVAL PROPHETA ALVES NETO - RA: D93HDG1
EDGAR HIROSHI - RA: N4572J2
JULIO HIDEKI MOREIRA MATSUASHI - RA: NHO9EHO
JOÃO NICOLAS ARAUJO DE SOUZA - RA: F0133E4
VITOR SILVA PELLEGRINO - RA: F001HFO
WILLIAN FUKASE - RA: F0838E9
*/

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