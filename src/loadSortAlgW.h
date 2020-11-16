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

#ifndef _LOADSORTALGW_H_
#define _LOADSORTALGW_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

typedef void(__cdecl *sort)(int *, int);

bool loadSortAlg(void **handle, sort *func_sort, char* libFile);

void unloadSortAlg(void **handle);

bool loadSortAlg(void **handle, sort *func_sort, char* libFile){
	if(strlen(libFile) == 0 || strstr(libFile, ".dll") == NULL) return false;
	
	char *path = (char *)malloc(sizeof(char) * (strlen(libFile) + 7));
	strcpy(path, "./alg/");
	strcat(path, libFile);
	
	HINSTANCE hHandle = LoadLibrary(TEXT(path));
	if(hHandle == NULL) return false;
	
	free(path);

	*func_sort = (sort)GetProcAddress(hHandle, "sort");
	if(*func_sort == NULL){
		FreeLibrary(hHandle);
		return false;
	}
	
	*handle = (void *)&hHandle;
	return true;
}

void unloadSortAlg(void **handle){
	if(*handle == NULL) return;
	
	FreeLibrary((*(HINSTANCE *)handle));
}

#endif
