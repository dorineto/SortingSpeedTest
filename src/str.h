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

#ifndef _STR_H_
#define _STR_H_

#include <stdlib.h>
#include <stdio.h>

/* Structs */

typedef struct{
  char *value;
  int size;
} str;

/* Function definition */

int initStr(str **str, int size);

/* Function implementation */

int initStr(str **strI, int size){
    if(size <= 0) return 0;

	size_t s = sizeof(str);
	
    str *aux = (str *)malloc(s);
	if(aux == NULL) return 0;
    
	*strI = aux;
	
    (*strI)->value = (char *)malloc(sizeof(char) * size);
    if((*strI)->value == NULL) return 0;

    (*strI)->size = size;
    
    return 1;
}

#endif