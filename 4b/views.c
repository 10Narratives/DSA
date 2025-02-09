#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"

#include "utils.h"
#include "structs.h"

#include "models.h"
#include "balance.h"

#define SUCCESS 1
#define FAILURE 0
#define SPACE_AMOUT 3

int D_add(Tree *tree){
	int key = getInt("ENTER KEY -->");
	int data = getInt("ENTER DATA -->");
	add(tree, key, data);
	balance(tree);
	return SUCCESS;
}

void printNode(Node *target, int sps){
	if(!target)
		return;
	printf("|-");
	for(int i = 0; i < sps; i++)
		printf("-");

	printf("{KEY: %d DATA: %d SIZE: %d}\n", target->key, target->data, target->size);
		
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
	int key = getInt("ENTER KEY -->");
	int foundLen = 0;
	Node **foundNodes = find(tree, key, &foundLen);
	if(!foundNodes){
		printf("NOTHING WAS BEEN FOUND\n");
	} else{
		for(int i = 0; i < foundLen; i++){
			printf("%d {KEY: %d DATA: %d}\n", i, foundNodes[i]->key, foundNodes[i]->data);
		}
		free(foundNodes);
		
	}
	return SUCCESS;
}

int D_delete(Tree *tree){
	int key = getInt("ENTER KEY --> ");
	int foundLen = 0;
	Node **foundNodes = find(tree, key, &foundLen);
	if(!foundNodes){
		printf("NOTHING WAS BEEN FOUND\n");
	} else{
	
		if(foundLen == 1){
			delete(tree, foundNodes[0]);
		} else{
			for(int i = 0; i < foundLen; i++){
				printf("%d {KEY: %d DATA: %d}\n", i, foundNodes[i]->key, foundNodes[i]->data);
			}

			int deleteIndex = getInt("ENTER INDEX OF NODE WHICH YOU WOULD LIKE TO DELETE --> ");
			while(deleteIndex > foundLen - 1){
				printf("WRONG INPUT. ENTER AGAIN\n");
				deleteIndex = getInt("ENTER INDEX OF NODE WHICH YOU WOULD LIKE TO DELETE --> ");
			}
			delete(tree, foundNodes[deleteIndex]);
			
		}
		balance(tree);
		free(foundNodes);
		
	}
	return SUCCESS;
}

int D_bypass(Tree *tree){
	if(!tree->root)
		return SUCCESS;
	int low = getInt("ENTER LOW EDGE --> ");
	int top = getInt("ENTER TOP EDGE --> ");
	bypass(tree->root, low, top);
	return SUCCESS;
}

int D_spfind(Tree *tree){
	if(!tree->root)
		return SUCCESS;
	int foundLen = 0;
	Node **foundNodes = find(tree, findMaxNode(tree->root)->key, &foundLen);
	for(int i = 0; i < foundLen; i++)
		printf("{KEY %d DATA %d}\n", foundNodes[i]->key, foundNodes[i]->data);	
	free(foundNodes);
	return SUCCESS;
}

int D_import(Tree *tree){
	char *fpath = readline("ENTER PATH --> ");
	if(!fpath)
		return SUCCESS;
	FILE *file = fopen(fpath, "r"); free(fpath);
	if(!file){
		printf("FILE DOES NOT EXIST\n");
		return SUCCESS;
	}
	import(tree, file);
	balance(tree);
	return SUCCESS;
}
