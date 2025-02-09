#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "dialog.h"
#include "structs.h"
#include "models.h"
#include "views.h"

#define SUCCESS 1
#define FAILURE 0

char *genStr(int len){
	const char sourse[37] = "qwertyasdfghzxcvbnQWERTYASDFGHZXCVBN";
	char *str = malloc((len + 1) * sizeof(char));
	for(int i = 0; i < len; i++){
		str[i] = sourse[rand() % 36];
	}
	str[len] = '\0';
	return str;
}

int T_add(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	char *data = readline("ENTER DATA --> ");
	if(!data)
		return FAILURE;
	float programTime = 0;	
	clock_t itTime = clock();
	add(tree, key, data);
	itTime = clock() - itTime;
	programTime += ((float) itTime / CLOCKS_PER_SEC);
	printf("OPERATION TIME: %f\n", programTime);
	return SUCCESS;
}

int T_multiadd(Tree *tree){
	int numberOfItems = getInt("ENTER NUMBER OF ITEMS --> ");
	int lenOfStr = getInt("ENTER LENGHT OF STRINGS --> ");
	float programTime = 0;
	for(int i = 0; i < numberOfItems; i++){
		clock_t itTime = clock();
		add(tree, genStr(lenOfStr), genStr(lenOfStr));
		itTime = clock() - itTime;
		programTime += (float)itTime; 
	}
	float aver = (programTime/CLOCKS_PER_SEC) / numberOfItems;
	printf("OPERATION TIME: %f\n", aver);
	return SUCCESS;	
}

int T_find(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	float programTime = 0;	
	clock_t itTime = clock();
	int findSize = 0;
	Node **foundNodes = find(tree, key, &findSize);
	if(foundNodes){
		for(int i = 0; i < findSize; i++)
			printf("{KEY %s DATA %s}\n", foundNodes[i]->key, foundNodes[i]->data);
	}
	itTime = clock() - itTime;
	programTime += ((float) itTime / CLOCKS_PER_SEC);
	printf("OPERATION TIME: %f\n", programTime);
	free(foundNodes);
	free(key);
	return SUCCESS;	
}

int T_delete(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	float programTime = 0;	
	clock_t itTime = clock();
	int findSize = 0;
	Node **foundNodes = find(tree, key, &findSize);
	if(foundNodes){
		delete(tree, foundNodes[0]);
	}
	itTime = clock() - itTime;
	programTime += ((float) itTime / CLOCKS_PER_SEC);
	printf("OPERATION TIME: %f\n", programTime);
	free(foundNodes);
	free(key);
	return SUCCESS;
}

int T_spfind(Tree *tree){
	float programTime = 0;	
	clock_t itTime = clock();
	D_spfind(tree);
	itTime = clock() - itTime;
	programTime += ((float) itTime / CLOCKS_PER_SEC);
	printf("OPERATION TIME: %f\n", programTime);	
}

int D_timing(Tree *tree){
	int numberOfItems = getInt("ENTER NUMBER OF ITEMS --> ");
	int lenOfStr = getInt("ENTER LENGHT OF STRINGS --> ");
	for(int i = 0; i < numberOfItems; i++)
		add(tree, genStr(lenOfStr), genStr(lenOfStr));

	const char *msgs[] = {"\t0. QUIT", "\t1. MULTIADD", "\t2. ADD", "\t3. DELETE FIRST", "\t4. FIND", "\t5. SPECIAL FIND"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Tree *) = {NULL, T_multiadd, T_add, T_delete, T_find, T_spfind};
	int rc = dialog(msgs, N);
	while(rc > 0){
		if(!fptr[rc](tree)) break;
		rc = dialog(msgs, N);
	}

	return SUCCESS;
}
