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

int genInt(int len){
	int result = 0, incr = 0;
	for(int i = 0; i < len; i++){
		incr = rand() % 27;
		result *= 10;
		result += incr;
	}
	return result;
}

int T_add(Tree *tree){
	int key = getInt("ENTER KEY --> ");
	int data = getInt("ENTER DATA --> ");
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
	int lenOfInt = getInt("ENTER LENGHT OF INTEGER --> ");
	float programTime = 0;
	for(int i = 0; i < numberOfItems; i++){
		clock_t itTime = clock();
		add(tree, genInt(lenOfInt), genInt(lenOfInt));
		itTime = clock() - itTime;
		programTime += (float)itTime; 
	}
	float aver = (programTime/CLOCKS_PER_SEC) / numberOfItems;
	printf("OPERATION TIME: %f\n", aver);
	return SUCCESS;	
}

int T_find(Tree *tree){
	int key = getInt("ENTER KEY --> ");
	float programTime = 0;	
	clock_t itTime = clock();
	int findSize = 0;
	Node **foundNodes = find(tree, key, &findSize);
	if(foundNodes){
		for(int i = 0; i < findSize; i++)
			printf("{KEY %d DATA %d}\n", foundNodes[i]->key, foundNodes[i]->data);
	}
	itTime = clock() - itTime;
	programTime += ((float) itTime / CLOCKS_PER_SEC);
	printf("OPERATION TIME: %f\n", programTime);
	free(foundNodes);
	return SUCCESS;	
}

int T_delete(Tree *tree){
	int key = getInt("ENTER KEY --> ");
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
	return SUCCESS;
}

int D_timing(Tree *tree){
	const char *msgs[] = {"\t0. QUIT", "\t1. MULTIADD", "\t2. ADD", "\t3. DELETE FIRST", "\t4. FIND", "\t5. PRINT"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Tree *) = {NULL, T_multiadd, T_add, T_delete, T_find, print};
	int rc = dialog(msgs, N);
	while(rc > 0){
		if(!fptr[rc](tree)) break;
		rc = dialog(msgs, N);
	}

	return SUCCESS;
}
