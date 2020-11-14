#ifndef _LOADCONTROLLER_H_
#define _LOADCONTROLLER_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

#include "utility.h"
#include "str.h"

/* Structs and Macros */

#define PATH_CARGAS "./cargas/"

/* Function definition */

char *createLoad(int size, char *fileName, const char complexity);

int readLoad(char *fileName, int **arr);

int quantElements(size_t sizeElem, char *path);

char *genLoadFileName(int size, const char complexity);

/* Function implementation */

char *createLoad(int size, char *fileName, const char complexity){ 
	if(size <= 0 || fileName == NULL || strlen(fileName) == 0 
	|| (complexity != 'b' && complexity != 'r' && complexity != 'w'))
		return "Parametro invalido!";
	
	char *path = (char *)malloc(sizeof(char) * (strlen(fileName) + 10));
	strcpy(path, "./cargas/");
	strcat(path, fileName);
	
	errno = 0;
	FILE *file = fopen(path, "wb+");
	if(file == NULL)
		return "Nao foi possivel abrir o arquivo";
	
	free(path);

	errno = 0;
	
	int writeNumber;
	for(int i = 0; i < size; i++){
		switch(complexity){
			case 'b': writeNumber = i; break; //Melhor caso sendo os numeros ja ordenados (crescente)
			case 'r': writeNumber = rand() % size; break; //Caso regular sendo os números aleatorios 
			default:  writeNumber = size - (i + 1);  /*Pior caso sendo os números estando na ordem inversa 
													   da ordenação (decrescente)*/
		}
		
		if(fwrite(&writeNumber, sizeof(int), 1, file) != 1)
			break;
	}
	
	fclose(file);
	
	if(errno != 0)
		return "Nao foi possivel preencher o arquivo";
	
	return "";
}

int readLoad(char *fileName, int **arr){
	if(fileName == NULL || strlen(fileName) == 0 || strstr(fileName, ".cg") == NULL) return -1;
	
	char *path = (char *)malloc(sizeof(char) * (strlen(fileName) + 10));
	strcpy(path, "./cargas/");
	strcat(path, fileName);

	int size = quantElements(sizeof(int), path);
	if(size <= 0){
		free(path);
		return size;
	}
	
	*arr = (int *)malloc(sizeof(int) * size);
	if(*arr == NULL){
		free(path);
		return -1;
	}
	
	int *readNum = (int *)malloc(sizeof(int));
	if(readNum == NULL){
		free(path);
		free(*arr);
		return -1;
	}
	
	FILE *file = fopen(path, "rb");
	if(file == NULL){
		free(path);
		free(*arr);
		free(readNum);
		return -1;
	}
	
	free(path);

	rewind(file);
	errno = 0;
	
	int i = 0;
	while(fread(readNum, sizeof(int), 1, file) == 1 && errno == 0){
		(*arr)[i] = *readNum;
		i++;
	}
	
	fclose(file);
	free(readNum);
	if(errno != 0){
		free(*arr);
		return -1;
	}
	
	return size;
}

int quantElements(size_t sizeElem, char *path){
	FILE *file = fopen(path, "rb");
	if(file == NULL) return -1;
	
	rewind(file);	
	errno = 0;
	int quant = 0;
	
	while(fgetc(file) != EOF && fseek(file, -sizeof(char), SEEK_CUR) != -1){
		if(fseek(file, sizeElem, SEEK_CUR) == -1) break;
		quant++;
	};
	
	fclose(file);
	return errno == 0? quant : -1;
}

char *genLoadFileName(int size, const char complexity){
	time_t nowTime = time(NULL);
	struct tm *tmNow = localtime(&nowTime);
	
	char fileNamePattern[100];
	if(fileNamePattern == NULL) return NULL;
	
	char **timeFormated = timeFormat(tmNow);
	if(timeFormated == NULL) return NULL;
	
	sprintf(fileNamePattern, "%d%d%d%s%s%s_S%d_%c.cg", 
			tmNow->tm_mday, (tmNow->tm_mon + 1), (1900 + tmNow->tm_year),
			timeFormated[0], timeFormated[1], timeFormated[2],
			size, toupper((int)complexity));
	
	char *fileName = (char *)malloc(sizeof(char) * strlen(fileNamePattern));
	fileName = strcpy(fileName, fileNamePattern);
	
	//free(tmNow);
	
	return fileName;
}

#endif
