#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>

#include "str.h"

/* Function definition */

void toLowerStr(char *str);

void toUpperStr(char *str);

int listFiles(const char *dirName, str ***fileNames, int (*select)(struct dirent *));

str **charArrToStrArr(char *arrChar[], int size){
	if(arrChar == NULL || size <= 0) return NULL;
	
	str **strArr = (str **)malloc(sizeof(str) * size);
	if(strArr == NULL) return NULL;
	
	for(int i = 0; i < size; i++){
		if(!initStr(&strArr[i], strlen(arrChar[i]))) return NULL;
		strcpy(strArr[i]->value, arrChar[i]);
	}
	
	return strArr;
}

/* Function implementation */

void toLowerStr(char *str){
	for(int i = 0; i < strlen(str); i++)
		str[i] = (char)tolower(str[i]);
}

void toUpperStr(char *str){
	for(int i = 0; i < strlen(str); i++)
		str[i] = (char)toupper(str[i]);
}

int listFiles(const char *dirName, str ***fileNames, int (*select)(struct dirent *)){
	if(strlen(dirName) == 0) return -1;
	
	DIR *dir = opendir(dirName);
	if(dir == NULL)
		return -1;
	
	*fileNames = (str **)malloc(sizeof(str) * 5);
	int fileNameTotal = 5;
	int size = 0;
	
	struct dirent *arq;
	do{
		errno = 0;
		if((arq = readdir(dir)) != NULL){
			if(select != NULL && !(select)(arq))
				continue;
			
			size++;
			
			if(size > fileNameTotal ){
				fileNameTotal += 5;
				realloc(*fileNames, sizeof(str) * fileNameTotal);
				
				if(*fileNames == NULL) return -1;
			}
			
			initStr(&((*fileNames)[size - 1]), strlen(arq->d_name));
			strcpy((*fileNames)[size - 1]->value, arq->d_name);
		}
	}while(arq != NULL);
	
	if(arq == NULL && errno != 0){
		free(*fileNames);
		return -1;
	}
	
	if(size == 0)
		free(*fileNames);
	else{
		realloc(*fileNames, sizeof(str) * size);
		if(*fileNames == NULL)
			return -1;
	}
	
	closedir(dir);
	
	return size;
}

#endif