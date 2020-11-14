#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>

#include "str.h"

/* Function definition */

void toLowerStr(char *str);

void toUpperStr(char *str);

#ifdef _WIN32
	#include <windows.h>
	
	int listFiles(const char *dirName, char ***fileNames, int (*select)(CHAR [MAX_PATH]));
#else
	#include <dirent.h>

	int listFiles(const char *dirName, char ***fileNames, int (*select)(struct dirent *));
#endif

char **timeFormat(struct tm *tmTime);

int indexOf(const char *searchStr, const char *cmpStr);

char *subString(const char* string, int start, int end);

void setupDirs();

/* Function implementation */

void toLowerStr(char *str){
	for(int i = 0; i < strlen(str); i++)
		str[i] = (char)tolower(str[i]);
}

void toUpperStr(char *str){
	for(int i = 0; i < strlen(str); i++)
		str[i] = (char)toupper(str[i]);
}

#ifdef _WIN32
int listFiles(const char *dirName, char ***fileNames, int (*select)(CHAR [MAX_PATH])){
	if(strlen(dirName) == 0) return -1;
	
	WIN32_FIND_DATA fd;
	HANDLE hFiles = INVALID_HANDLE_VALUE;
	
	*fileNames = NULL;
	
	int fileNameTotal = 5;
	int size = 0;
	char **fileN = (char **)malloc(sizeof(char *) * fileNameTotal);
	if(fileN == NULL)
		return -1;
	
	for(int i = 0; i < fileNameTotal; i++){
		fileN[i] = (char *)malloc(sizeof(char) * 50);
		if(fileN[i] == NULL) return -1;
	}
	
	char path[strlen(dirName) + 2];
	strcpy(path, dirName);
	strcat(path, "*\0");
	
	hFiles = FindFirstFile(TEXT(path), &fd);
	if(hFiles == INVALID_HANDLE_VALUE){
		free(fileN);
		return -1;
	}
	
	do{
		if(select != NULL && !(select)(fd.cFileName))
			continue;
		
		size++;
		if(size > fileNameTotal){
			fileNameTotal += 5;
			fileN = (char **)realloc(fileN, sizeof(char *) * fileNameTotal);
			if(fileN == NULL) return -1;
			
			for(int i = size - 1; i < fileNameTotal; i++){
				fileN[i] = (char *)malloc(sizeof(char) * 50);
				if(fileN[i] == NULL) return -1;
			}
		}
		
		strcpy(fileN[size - 1], fd.cFileName);
	}while(FindNextFile(hFiles, &fd));
	
	if(GetLastError() != ERROR_NO_MORE_FILES){
		free(fileN);
		return -1;
	}
	
	if(size == 0){
		free(fileN);
	}else{
		fileN = (char **)realloc(fileN, sizeof(char *) * size);
		if(fileN == NULL) return -1;
	}
	
	FindClose(hFiles);
	
	*fileNames = fileN;
	
	return size;
}
#else
int listFiles(const char *dirName, char ***fileNames, int (*select)(struct dirent *)){
	if(strlen(dirName) == 0) return -1;
	
	DIR *dir = opendir(dirName);
	if(dir == NULL)
		return -1;
	
	*fileNames = NULL;
	
	int fileNameTotal = 5;
	int size = 0;
	
	char **fileN = (char **)malloc(sizeof(char *) * fileNameTotal);
	if(fileN == NULL)
		return -1;
	
	for(int i = 0; i < fileNameTotal; i++){
		fileN[i] = (char *)malloc(sizeof(char *) * 50);
		if(fileN[i] == NULL){
			free(fileN);
			return -1;
		}
	}
	
	struct dirent *arq;
	do{
		errno = 0;
		if((arq = readdir(dir)) != NULL){
			if(select != NULL && !(select)(arq))
				continue;
			
			size++;
			
			if(size > fileNameTotal ){
				fileNameTotal += 5;
				fileN = (char **)realloc(fileN, sizeof(char *) * fileNameTotal);
				if(fileN == NULL) return -1;

				for(int i = size - 1; i < fileNameTotal; i++){
					fileN[i] = (char *)malloc(sizeof(char) * 50);
					if(fileN[i] == NULL){
						free(fileN);
						return -1;
					}
				}
			}			
			
			strcpy(fileN[size - 1], arq->d_name);
		}
	}while(arq != NULL);
	
	if(arq == NULL && errno != 0){
		free(fileN);
		return -1;
	}
	
	if(size == 0)
		free(fileN);
	else{
		fileN = (char **)realloc(fileN, sizeof(char *) * size);
		if(fileN == NULL)
			return -1;
	}
	
	closedir(dir);
	
	*fileNames = fileN;
	
	return size;
}	
#endif

char **timeFormat(struct tm *tmTime){
	if(tmTime == NULL) return NULL;
	
	char **timeFormated = (char **)malloc(sizeof(char*) * 3);
	if(timeFormated == NULL) return NULL;
	
	for(int i = 0; i < 3; i++){
		timeFormated[i] = (char *)malloc(sizeof(char) * 3);
		if(timeFormated[i] == NULL){
			free(timeFormated);
			return NULL;
		}
	}
	
	char timePattern[10];
	strcpy(timePattern, "\0");
	
	int times[3]; 
	times[0] = tmTime->tm_hour;
	times[1] = tmTime->tm_min; 
	times[2] = tmTime->tm_sec;
	
	for(int i = 0; i < 3; i++){
		sprintf(timePattern, (times[i] - 10 < 0? "0%d" : "%d"), times[i]);
		strcpy(timeFormated[i], timePattern);
	}
	
	return timeFormated;
}

char **timeFormatWSec(time_t tim){
	char **timeFormated = (char **)malloc(sizeof(char *) * 3);
	if(timeFormated == NULL) return NULL;

	for(int i = 0; i < 3; i++){
		timeFormated[i] = (char *)malloc(sizeof(char) * 11);
		if(timeFormated[i] == NULL) return NULL;
	}

	int aux;
	time_t restTim = tim;

	if(restTim / 3600 != 0){
		aux = restTim / 3600;
		restTim -= aux * 3600;
		sprintf(timeFormated[0], aux - 10 > 0? "%d" : "0%d", aux);		
	}
	else{
		strcpy(timeFormated[0], "00");
	}


	if(restTim / 60 != 0){
		aux = restTim / 60;
		restTim -= aux * 60;
		sprintf(timeFormated[1], aux - 10 > 0? "%d" : "0%d", aux);
	}
	else{
		strcpy(timeFormated[1], "00");
	}

	sprintf(timeFormated[2], restTim - 10 > 0? "%d" : "0%d", (int)restTim);

	return timeFormated;
}


char *subString(const char* string, int start, int end){
	if(string == NULL || start < 0 || start > strlen(string)
	|| end <= start || end > strlen(string)) return "";

	char Str[strlen(string) + 1];
	strcpy(Str, string);

	char *subStr = (char *)malloc(sizeof(char) * (end - start + 1));
	for(int i = start, k = 0; i < end; i++, k++)
		subStr[k] = Str[i];
	
	subStr[end - start] = '\0';
	return subStr;
}

int indexOf(const char *searchStr, const char *cmpStr){
	if(searchStr == NULL || strlen(searchStr) == 0 
	|| cmpStr == NULL || strlen(cmpStr) == 0 ) return -1;
	
	char scStr[strlen(searchStr) + 1];
	strcpy(scStr, searchStr);
	
	char cpStr[strlen(cmpStr) + 1];
	strcpy(cpStr, cmpStr);
	
	int index = -1;
	bool matched;
	
	for(int i = 0; i < strlen(scStr); i++){
		if(i + strlen(cpStr) - 1 > strlen(scStr) - 1)
			break;
		
		matched = true;
		for(int j = 0; j < strlen(cpStr); j++){
			if(scStr[i + j] != cpStr[j]){
				matched = false;
				break;
			}
		}
		
		if(matched){
			index = i;
			break;
		}
	}
	
	return index;
}


void setupDirs(){
	#ifdef _WIN32
		_mkdir("./alg/");
		_mkdir("./cargas");
	#else
		mkdir("./alg/", S_IRWXU | S_IRWXG | S_IRWXO);
		mkdir("./cargas/", S_IRWXU | S_IRWXG | S_IRWXO);
	#endif
}

#endif
