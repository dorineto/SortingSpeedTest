#ifndef _LOADSORTALGW_H_
#define _LOADSORTALGW_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define PATH_ALG "./alg/"

typedef void(__cdecl *sort)(int *, int);

bool loadSortAlg(void **handle, sort *func_sort, char* libFile);

void unloadSortAlg(void **handle);

bool loadSortAlg(void **handle, sort *func_sort, char* libFile){
	if(strlen(libFile) == 0 || strstr(libFile, ".dll") == NULL) return false;
	
	char path[strlen(PATH_ALG)];
	strcpy(path, PATH_ALG);
	strcat(path, libFile);
	
	HINSTANCE hHandle = LoadLibrary(TEXT(path));
	if(hHandle == NULL) return false;
	
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