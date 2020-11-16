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

#ifndef _TESTER_H_
#define _TESTER_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#ifdef __WIN32
	#include "loadSortAlgW.h"
#else
	#include "loadSortAlgL.h"
#endif

/* Function definition */

char *makeSpeedTest(int *arrSort, int arrSize, int quantRep, char *libName, double **results);

/* Function implementation */

char *makeSpeedTest(int *arrSort, int arrSize, int quantRep, char *libName, double **results){
	if(arrSort == NULL || quantRep <= 0 || libName == NULL || strlen(libName) == 0)
		return "Parametro(s) invalido(s)!";
	
	
	void *handle = NULL;
	sort sortAlg = NULL;
	
	if(!loadSortAlg(&handle, &sortAlg, libName))
		return "Nao foi possivel carregar a biblioteca!";
	
	*results = (double *)malloc(sizeof(double) * (quantRep + 1));
	if(*results == NULL){
		unloadSortAlg(&handle);
		return "Falha na alocacao de memoria!";
	}
	
	int *sortedArr = (int *)malloc(sizeof(int) * arrSize);
	if(sortedArr == NULL){
		unloadSortAlg(&handle);
		return "Falha na alocacao de memoria!";
	}
	
	for(int iter = 0; iter < quantRep; iter++){
		for(int i = 0; i < arrSize; i++)
			sortedArr[i] = arrSort[i];
		
		time_t start = time(NULL);
		
		(sortAlg)(sortedArr, arrSize);
		
		(*results)[iter] = difftime(time(NULL), start);  
	}
	
	free(sortedArr);
	
	double sum = 0;
	for(int i = 0; i < quantRep; i++)	
		sum += (*results)[i];

	(*results)[quantRep] = sum / quantRep;
	
	unloadSortAlg(handle);
	return "";
}

#endif