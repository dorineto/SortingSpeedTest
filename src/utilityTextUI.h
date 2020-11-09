#ifndef _UTILITYTEXTUI_H_
#define _UTILITYTEXTUI_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utility.h"
#include "list.h"

/* Function definition */

int menuGen(char *options[], int size);

int menuGenList(list *options);

bool menuConfirm(char *action);

void printAlignCenter(char *text, int width);

/* Function implemention*/

int menuGen(char *options[], int size){ 
	if(size <= 0 || options == NULL) return -1;
	
	printf("\n");
	for(int i = 0; i < size; i++){
		printf("%d - %s\n", (i + 1), options[i]);
	}
	
	int ret;
	
	printf("\nEscolha uma das opcoes acima: ");
	scanf("%d", &ret);
	
	if(ret <= 0 || ret > size)
		return -1;
	
	return ret - 1;
}

int menuGenList(list *options){ 
	if(options == NULL || isEmpty(options)) return -1;
	
	printf("\n");
	for(int i = 0; i <= options->currentIndex; i++){
		printf("%d - %s\n", (i + 1), options->values[i]->value);
	}
	
	int ret;
	
	printf("\nEscolha uma das opcoes acima: ");
	scanf("%d", &ret);
	
	if(ret <= 0 || ret > options->currentIndex + 1)
		return -1;
	
	return ret - 1;
}

bool menuConfirm(char *action){
	char esc[3];
	
	printf("\nDeseja %s? (S/n): ", action);
	scanf("%s", esc);
	
	toLowerStr(esc);
	return strncmp("sim", esc, strlen(esc)) == 0;
}

void printAlignCenter(char *text, int width){
	int left = (width - strlen(text));
	if(left < 0){
		printf("%s", text);
		return;
	}
	
	left /= 2;
	int right = (width - strlen(text)) - left;
	
	printf("%*s%s%*s", left, "", text, right, "");
}
#endif