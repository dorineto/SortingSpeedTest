#ifndef _SPEEDSORTTEXTUI_H_
#define _SPEEDSORTTEXTUI_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
	#include <direct.h>
	#include <windows.h>
	
	int searchLoad(CHAR fileName[MAX_PATH]);

	int searchLibs(CHAR fileName[MAX_PATH]);
#else
	#include <sys/stat.h>
	#include <dirent.h>
	
	int searchLoad(struct dirent *ent);

	int searchLibs(struct dirent *ent);
#endif

#include "configTest.h"
#include "utility.h"
#include "utilityTextUI.h"

/* Function definition */

configTest *configTestUI();

void createResultTable(configTest *ct, double **results);

bool createLoadUI(int *size, char *complexity);

/* Function implementation */

#ifdef _WIN32
	int searchLibs(CHAR fileName[MAX_PATH]){
		return  strstr(fileName, ".dll") != NULL;
	}
	
	int searchLoad(CHAR fileName[MAX_PATH]){
		return  strstr(fileName, ".cg") != NULL;
	}
#else
	int searchLibs(struct dirent *ent){
		return strstr(ent->d_name, ".so") != NULL;
	}

	int searchLoad(struct dirent *ent){
		return strstr(ent->d_name, ".cg") != NULL;
	}
#endif

configTest *configTestUI(){
	configTest *cgTest;
	if(!initConfigTest(&cgTest)) return NULL;
	
	printf("\nInsira a quantidade de repeticoes dos testes: ");
	scanf("%d", &cgTest->quantTent);
	
	char **auxArr;
	str **auxStr = (str **)malloc(sizeof(str *));
	list *optionsList = (list *)malloc(sizeof(list));
	if(!initList(optionsList, 5, 5)){
		printf("\nFalta de memoria para alocacao!\n");
		free(cgTest);
		return NULL;
	}
	
	char *paths[] = {"./cargas/", "./alg/"};
	
	for(int i = 0; i < 2; i++){
		clearList(optionsList);
		
		int quantLoad = listFiles(paths[i], &auxArr, i == 0? searchLoad : searchLibs);
		
		if(quantLoad == -1){
			printf("\nNao foi possivel pesquisar pelo arquivos\n");
			free(cgTest);
			free(optionsList);
			return NULL;
		}
		else if(quantLoad == 0){
			printf("\nNao possui arquivos no diretorio de pesquisa!\n");
			free(cgTest);
			free(optionsList);
			return NULL;
		}
		
		for(int j = 0; j < quantLoad; j++){
			initStr(auxStr, 50);
			strcpy((*auxStr)->value, auxArr[j]);
			push(optionsList, *auxStr);
		}
		
		
		int esc;
		do{
			esc = menuGenList(optionsList);
			if(esc != -1){
				if(i == 0)
					push(cgTest->arqLoad, popIndex(optionsList, esc));
				else
					push(cgTest->algSort, popIndex(optionsList, esc));
			}else{
				printf("\nOpcao Invalida\n");
			}
		}while((!isEmpty(optionsList)) && menuConfirm("adicionar mais um arquivo para o teste"));
		
		if((i == 0 && isEmpty(cgTest->arqLoad)) ||(i == 1 && isEmpty(cgTest->algSort))){
			free(auxArr);
			free(optionsList);
			return NULL;
		}
	}
	
	printf("\n\n-------------- Configuracao --------------\n");
	printf("Cargas: \n");
	for(int i = 0; i <= cgTest->arqLoad->currentIndex; i++)
		printf("%s\n", cgTest->arqLoad->values[i]->value);
	printf("\nAlgoritmos: \n");
	for(int i = 0; i <= cgTest->algSort->currentIndex; i++)
		printf("%s\n", cgTest->algSort->values[i]->value);
	printf("\nQuantidade de repeticoes: %d", cgTest->quantTent);
	printf("\n------------------------------------------\n");
	
	free(auxArr);
	free(optionsList);
	
	return menuConfirm("utilizar essa configuracao")? cgTest : NULL;
}

void createResultTable(configTest *ct, double **results){
	if(ct == NULL) return;
	
	char *arqName, *algName;
	char **algArqNames = (char **)malloc(sizeof(char *) * (ct->algSort->currentIndex + 1) * (ct->arqLoad->currentIndex + 1));
	
	int sizeFormat = 0;
	for(int i = 0; i <= ct->arqLoad->currentIndex; i++){
		for(int j = 0; j <= ct->algSort->currentIndex; j++){
			arqName = ct->arqLoad->values[i]->value;
			
			arqName = subString(arqName, indexOf(arqName, "_")+1, indexOf(arqName, ".cg"));
			
			algName = ct->algSort->values[j]->value;
			
			int auxIndex = indexOf(algName, ".dll");
			auxIndex = auxIndex == -1? indexOf(algName, ".so") : auxIndex;
			
			algName = subString(algName, 0, auxIndex);
			
			int size =  strlen(algName) + strlen(arqName) + 2;
			if(sizeFormat < size)
				sizeFormat = size;
			
			int index = i * (ct->algSort->currentIndex + 1) + j;
			algArqNames[index] = (char *)malloc(sizeof(char) * size);
			sprintf(algArqNames[index], "%s(%s)", algName, arqName);
		}
	}
	
	printf("\n%-*s ", sizeFormat, "Algoritmo(Carga)");
	
	char auxStr[8];
	for(int i = 1; i <= ct->quantTent; i++){
		printf("|");
		
		sprintf(auxStr, "%d", i);
		printAlignCenter(auxStr, 8);
	}
	printf("|");
	printAlignCenter("Media", 8);
	
	char *** timeFormated = (char ***)malloc(sizeof(char **));
	char strtime[9];
	for(int i = 0; i < (ct->algSort->currentIndex + 1) * (ct->arqLoad->currentIndex + 1); i++){
		printf("\n%-*s ", sizeFormat, algArqNames[i]);
		
		for(int j = 0; j <= ct->quantTent; j++){
			*timeFormated = timeFormatWSec((time_t)results[i][j]);
			
			printf("|");
			strcpy(strtime, "\0");
			
			if(strcmp((*timeFormated)[0], "00") != 0){
				strcat(strtime, (*timeFormated)[0]);
				strcat(strtime, ":");
			}
			
			if(strcmp((*timeFormated)[1], "00") != 0){
				strcat(strtime, (*timeFormated)[1]);
				strcat(strtime, ":");
			}
			
			strcat(strtime, (*timeFormated)[2]);
			
			printAlignCenter(strtime, 8);
			
			free(*timeFormated);
		}
	}
	
	free(algArqNames);
	free(arqName);
	free(algName);
}

bool createLoadUI(int *size, char *complexity){
	char *options[] = {"Melhor caso (ordem crescente)", "Caso Regular (ordem aleatoria)", "Pior caso (ordem decrescente)", "Voltar"};
	
	int esc = menuGen(options, 4);
	while(esc == -1){
		printf("\nOpcao invalida!\n");
		
		esc = menuGen(options, 4);
	}
	
	if(esc == 3)
		return false;
	
	switch(esc){
		case 0:  *complexity = 'b'; break;
		case 1:  *complexity = 'r'; break;
		default: *complexity = 'w';
	}
	
	int s;
	do{
		printf("\nInsira a quantidade de numeros gerados: ");
		scanf("%d", &s);
		
		if(s <= 0)
			printf("\nNumero invalido! O valor é igual o menor a zero.\n");
	}while(s <= 0);
	
	*size = s;
	
	printf("\n\nTamanho: %d\nComplexidade: %s\n", s, options[esc]);
	return menuConfirm("criar o arquivo com as configuracoes acima");
}

#endif
