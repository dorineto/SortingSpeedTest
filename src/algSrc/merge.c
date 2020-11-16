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

void split(int *arr, int init, int fin, int *arrSorted);

void merge(int *arr, int init, int mid, int fin, int *arrSorted);

void sort(int *arr, int size)
{
	if(arr == NULL || size < -1){
		free(arr);
		arr = NULL;
		return;
	}
	
	int *auxArr = (int *)malloc(sizeof(int) * size);
	if(auxArr == NULL){
		free(arr);
		arr = NULL;
		return;
	}
	
	split(arr, 0, size, auxArr);
	free(auxArr);
}

void split(int *arr, int init, int fin, int *arrSorted){
    if(fin - init <= 1)
        return;
        
    int mid = (init + fin) / 2;
    
    split(arrSorted, init,  mid, arr);
    split(arrSorted, mid, fin, arr);
	   
    merge(arr, init, mid, fin, arrSorted);
}

void merge(int *arr, int init, int mid, int fin, int *arrSorted){
	int i = init, j = mid;

	for(int k = init; k < fin; k++){
		if(i < mid && (j >= fin || arr[i] < arr[j])){
		   arrSorted[k] = arr[i++];
		}
		else{
		   arrSorted[k] = arr[j++];
		}
	}
}
