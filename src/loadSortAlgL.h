#ifndef _LOADSORTALGL_H_
#define _LOADSORTALGL_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>


#define PATH_ALG "./bin/alg/"

typedef void(*sort)(int *, int);

bool loadSortAlg(void **handle, sort *func_sort, const char* libName);

void unloadSortAlg(void **handle);

bool loadSortAlg(void **handle, sort *func_sort, const char* libFile){
	if(strlen(libFile) == 0 || strstr(libFile, ".so") == NULL) return false;
	
	char path[strlen(PATH_ALG)];
	strcpy(path, PATH_ALG);
	strcat(path, libFile);
	
	*handle = dlopen(path, RTLD_LAZY);
	if(*handle == NULL) return false;
	
	dlerror();
	*func_sort = (sort)dlsym(*handle, "sort");
	
	char *error = dlerror();
	if(error != NULL){
		dlclose(handle);
		return false;
	}
	
	return true;
}

void unloadSortAlg(void **handle){
	if(*handle == NULL) return;
	
	dlclose(handle);
}

#endif