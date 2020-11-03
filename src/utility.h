#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>

#include "str.h"

/* Function definition */

void toLowerStr(char *str);

void toUpperStr(char *str);

int listFiles(const char *dirName, str ***fileNames, int (*select)(struct dirent *));

str **timeFormat(struct tm *tmTime);

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

str **timeFormat(struct tm *tmTime){
	if(tmTime == NULL) return NULL;
	
	str **timeFormated = (str **)malloc(sizeof(str) * 3);
	if(timeFormat == NULL) return NULL;
	
	errno = 0;
	for(int i = 0; i < 3; i++){
		if(!initStr(&timeFormated[i], (int)sizeof(int))){
			errno = -1;
			break;
		}
	}
	
	if(errno == -1){
		free(timeFormated);
		return NULL;
	}
	
	sprintf(timeFormated[0]->value, (tmTime->tm_hour - 10 < 0? "0%d" : "%d"), tmTime->tm_hour);
	sprintf(timeFormated[1]->value, (tmTime->tm_min - 10 < 0? "0%d" : "%d"), tmTime->tm_min);
	sprintf(timeFormated[2]->value, (tmTime->tm_sec - 10 < 0? "0%d" : "%d"), tmTime->tm_sec);
	
	return timeFormated;
}

#endif