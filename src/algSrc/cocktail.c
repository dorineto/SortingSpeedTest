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

#include <stdlib.h>
#include "linux_sort.h"

void cocktail(int *arr, int size);

void swap(int *a, int *b);

void sort(int *arr, int size){
	cocktail(arr, size);
}

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void cocktail(int *arr, int size){
    int init = 0; 
    int fin = size; 
    int swaped = 0;
    
    do{
        for(int i = init; i < fin - 1; i++){
            if(arr[i] > arr[i + 1]){
                swap(&arr[i], &arr[i + 1]);
                swaped = 1;
            }
        }
        
        if(!swaped)
            break;
        
        fin--;
        
        swaped = 0;
        for(int i = fin - 1; i > init; i--){
            if(arr[i] < arr[i - 1]){
                swap(&arr[i], &arr[i - 1]);
                swaped = 1;
            }
        }
        
        init++;
    }while(swaped);
}