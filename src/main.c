#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "speedSortTextUI.h"
#include "loadController.h"
#include "tester.h"
#include "utilityTextUI.h"
#include "utility.h"

double **speedTestIntegration(configTest *configT);

char *checkDirsEmpty();

int main(){
	setupDirs();
	
	char *opcoes[] = {"Criar arquivo de carga", "Fazer teste de desempenho", "Sair"};
	int esc; 
	do{
		esc = menuGen(opcoes, 3);
		fflush(stdin);
		
		switch(esc){
			case 0: { // Criar Arquivo de carga
				int size;
				char comp;
				
				if(!createLoadUI(&size, &comp))
					continue;
				
				char *fileName = genLoadFileName(size, comp);
				
				char *ret = createLoad(size, fileName, comp);
				if(strlen(ret) != 0){
					printf("\n%s\n", ret);
					
					free(ret);
					free(fileName);
					continue;
				}
				
				printf("\nO arquivo %s foi criado com sucesso!\n", fileName);
				
				free(fileName);
			}
			break;
			
			case 1: { // Teste de desenpenho
				char *ret = checkDirsEmpty();
				if(strlen(ret) != 0){
					printf("\n%s\n", ret);
					
					free(ret);
					continue;
				}
			
				configTest *cgt = configTestUI();
				if(cgt == NULL)
					continue;
				
				double **results = speedTestIntegration(cgt);
				if(results == NULL){
					printf("\nErro ao tentar obter os resultados do teste!\n");
					
					free(cgt);
					continue;
				}
					
				createResultTable(cgt, results);
				printf("\n");
				
				free(cgt);
				free(results);
			}
			break;
			
			case 2: break; // Sair
			default:
				printf("\nOpcao invalida!\n");
		}
	}while(esc != 2);
	
	return 0;
}

char *checkDirsEmpty(){
	bool checkEmpty = false;
	char **auxChar;
	
	checkEmpty = listFiles("./cargas/", &auxChar, searchLoad) == 0;
	if(checkEmpty)
		return "O diretorio de cargas esta vazio!";
	
	free(auxChar);
	
	checkEmpty = listFiles("./alg/", &auxChar, searchLibs) == 0;
	if(checkEmpty)
		return "O diretorio de algoritmos esta vazio!";
	
	free(auxChar);
	return "";
}

double **speedTestIntegration(configTest *configT){
	if(configT == NULL) return NULL;
	
	int rowCount = (configT->arqLoad->currentIndex + 1) * (configT->algSort->currentIndex + 1);
	double **results = (double **)malloc(sizeof(double *) * rowCount);
	if(results == NULL)
		return NULL;
	
	int *arr, size;
	for(int i = 0; i <= configT->arqLoad->currentIndex; i++){
		size = readLoad(configT->arqLoad->values[i]->value, &arr);
		if(size == -1 || size == 0){
			popIndex(configT->arqLoad, i);
			free(arr);
			continue;
		}

		for(int j = 0; j <= configT->algSort->currentIndex; j++){
			int index = i * (configT->algSort->currentIndex + 1) + j;
			
			char *ret = makeSpeedTest(arr, size, configT->quantTent, configT->algSort->values[j]->value, &results[index]);
			if(strlen(ret) != 0){
				printf("\n%s\n", ret);
				popIndex(configT->algSort, j);
			}
		}

		free(arr);
	}
	
	rowCount = (configT->arqLoad->currentIndex + 1) * (configT->algSort->currentIndex + 1);
	results = (double **)realloc(results, sizeof(double *) * rowCount);
	if(results == NULL) return NULL;
	
	return results;
}
