#include <stdlib.h>
#include "linux_sort.h"

void CountingSort(int *arr, int size, int p) {
		int count[10];
		int *output = malloc(sizeof(int)*size);
		int i;
		for (i = 0; i < 10; i++) 
			count[i] = 0;
		//counting sort at p decimal place
		for (i = 0; i < size; i++)
			count[(arr[i] % (p*10)) / p]++;
		//prefix sum
		for (i = 1; i < 10; i++)
			count[i] += count[i-1];
		//placing on output
		for (i = size-1; i >= 0; i--) {
			int index = --count[(arr[i] % (p*10)) / p];
			output[index] = arr[i];
		}
		//copy output to array
		for (i = 0; i < size; i++) {
			arr[i] = output[i];
		}
		free(output);
}

void RadixSort(int *arr, int size) {
	int i;
	//biggest element
	int max = 0;
	for (i = 0; i < size; i++)
		if (arr[i] > max) 
			max = arr[i];
	//radix sort
	int p;
	for (p = 1; max / p > 0; p *= 10) {
		CountingSort(arr, size, p);
	}
	return;
}

void sort(int *arr, int size){
	RadixSort(arr, size);
}
