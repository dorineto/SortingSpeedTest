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

#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stdbool.h>

/* Structs */

#if !defined(elem)
	#define elem int
#endif

typedef struct{
	int size;
	int currentIndex;
	int grow;
	elem **values; 
} list;

/* Functions definition */
bool initList(list *l, int initalSize, int grow); 

bool isEmpty(list *l);

bool isFull(list *l); 

bool expandList(list *l); 

bool push(list *l, elem *item);

bool pushIndex(list *l, elem *item, int index); 

elem *pop(list *l);

elem *popIndex(list *l, int index); 

bool clearList(list *l);

/* Functions implementation */
bool initList(list *l, int initialSize, int grow){
	if(l == NULL || initialSize <= 0 || grow < 0) return false;
	
	l->size = initialSize;
	l->currentIndex = -1;
	l->grow = grow;
	l->values = (elem **)malloc(sizeof(elem) * l->size);
	
	if(l->values == NULL)
		return false;
	
	return true;
}

bool isFull(list *l){
	return l->currentIndex == l->size - 1;
}

bool isEmpty(list *l){
	return l->currentIndex == -1;
}

bool expandList(list *l){
	l->size += l->grow;
	l->values = (elem **)realloc(l->values, sizeof(elem) * l->size);
	
	return l->values != NULL; 
}

bool push(list *l, elem *item){
	if(l == NULL) return false;
	
	if(isFull(l) && (!expandList(l)))
		return false;
	
	l->values[++l->currentIndex] = item;
	return true;
}

bool pushIndex(list *l, elem *item, int index){
	if(l == NULL || index < 0 || index > l->currentIndex) return false;
	
	if(isFull(l) && (!expandList(l)))
		return false;
	
	for(int i = l->currentIndex; i >= index; i--){
		l->values[i+1] = l->values[i];
	}
	
	l->currentIndex++;
	l->values[index] = item;
	return true;
}

elem *pop(list *l){
	if(l == NULL || isEmpty(l)) return NULL;
	
	elem *ret = l->values[0];
	
	for(int i = 0; i < l->currentIndex; i++)
		l->values[i] = l->values[i + 1];
	
	l->currentIndex--;
	return ret;
}

elem *popIndex(list *l, int index){
	if(l == NULL || isEmpty(l) ||(index < 0 && index > l->currentIndex)) return NULL;
	
	elem *ret = l->values[index];
	
	if(index != l->currentIndex){
		for(int i = index; i < l->currentIndex; i++)
			l->values[i] = l->values[i + 1];
	}
	
	--l->currentIndex;
	return ret;
}

bool clearList(list *l){
	if(l == NULL || isEmpty(l)) return false;
	
	l->currentIndex = -1;
	return true;
}
#endif