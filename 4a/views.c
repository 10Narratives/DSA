#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"

#include "utils.h"
#include "structs.h"

#include "models.h"

#define SUCCESS 1
#define FAILURE 0
#define SPACE_AMOUT 3

int D_add(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	char *data = readline("ENTER DATA --> ");
	if(!data)
		return FAILURE;
	add(tree, key, data);
	return SUCCESS;
}

void printNode(Node *target, int sps){
	if(!target)
		return;
	printf("|-");
	for(int i = 0; i < sps; i++)
		printf("-");

	printf("{KEY: %s DATA: %s}\n", target->key, target->data);
		
	if(target->right){
		printf("R: ");
		printNode(target->right, sps + SPACE_AMOUT);
	}
	if(target->left){
		printf("L: ");
		printNode(target->left, sps + SPACE_AMOUT);
	}
	
}

int print(Tree *tree){
	int sps = 0;
	printNode(tree->root, sps);
	return SUCCESS;
}

int D_find(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	int foundLen = 0;
	Node **foundNodes = find(tree, key, &foundLen);
	if(!foundNodes){
		printf("NOTHING WAS BEEN FOUND\n");
	} else{
		for(int i = 0; i < foundLen; i++){
			printf("%d {KEY: %s DATA: %s}\n", i, foundNodes[i]->key, foundNodes[i]->data);
		}
		free(foundNodes);
		
	}
	free(key);
	return SUCCESS;
}

int D_delete(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	int foundLen = 0;
	Node **foundNodes = find(tree, key, &foundLen);
	if(!foundNodes){
		printf("NOTHING WAS BEEN FOUND\n");
	} else{
	
		if(foundLen == 1){
			delete(tree, foundNodes[0]);
		} else{
			for(int i = 0; i < foundLen; i++){
				printf("%d {KEY: %s DATA: %s}\n", i, foundNodes[i]->key, foundNodes[i]->data);
			}

			int deleteIndex = getInt("ENTER INDEX OF NODE WHICH YOU WOULD LIKE TO DELETE --> ");
			while(deleteIndex > foundLen - 1){
				printf("WRONG INPUT. ENTER AGAIN\n");
				deleteIndex = getInt("ENTER INDEX OF NODE WHICH YOU WOULD LIKE TO DELETE --> ");
			}
			delete(tree, foundNodes[deleteIndex]);
			
		}
	
		free(foundNodes);
		
	}
	free(key);
	return SUCCESS;
}

int D_bypass(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	int foundLen = 0;
	Node **foundNodes = find(tree, key, &foundLen);
	if(!foundNodes)
		printf("NOTHING WAS BEEN FOUND\n");
	else{
		bypass(foundNodes[0]->right);
		free(foundNodes);		
	}

	free(key);
	return SUCCESS;
}

int D_spfind(Tree *tree){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	spfind(tree, key);
	free(key);
	return SUCCESS;
}

int D_import(Tree *tree){
	char *fpath = readline("ENTER PATH --> ");
	if(!fpath)
		return FAILURE;
	FILE *file = fopen(fpath, "r"); free(fpath);
	if(!file){
		printf("FILE DOES NOT EXIST\n");
		return SUCCESS;
	}
	import(tree, file);
	return SUCCESS;
}
