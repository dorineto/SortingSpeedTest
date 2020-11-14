#ifndef _LOADSORTALGL_H_
#define _LOADSORTALGL_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dlfcn.h>

typedef void(*sort)(int *, int);

bool loadSortAlg(void **handle, sort *func_sort, char* libFile);

void unloadSortAlg(void **handle);

bool loadSortAlg(void **handle, sort *func_sort, char* libFile){
	if(strlen(libFile) == 0 || strstr(libFile, ".so") == NULL) return false;
	
	char *path = (char *)malloc(sizeof(char) * (strlen(libFile) + 7));
	strcpy(path, "./alg/");
	strcat(path, libFile);	
	
	*handle = dlopen(path, RTLD_LAZY);
	if(*handle == NULL) return false;
	
	free(path);

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
