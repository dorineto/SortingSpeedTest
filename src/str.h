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
	
    *strI = (str *)malloc(sizeof(str));
	if(*strI == NULL) return 0;
	
    (*strI)->value = (char *)malloc(sizeof(char) * size);
    if((*strI)->value == NULL) return 0;

    (*strI)->size = size;
    
    return 1;
}

#endif