#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>

#include "structs.h"
#include "views.h"
#include "models.h"

#define BALANCE_CONST 0.6
#define SUCCESS 1
#define FAILURE 0

int calcSize(Node *target){
	int res = 1;
	if(target){
		int left = calcSize(target->left);
		int right = calcSize(target->right);
		res = right + left;
		target->size = res - 1;
	}
	return res;
}

void placeSizes(Node *root){
	if(root){
		placeSizes(root->left);
		placeSizes(root->right);
		calcSize(root);
	}
}

int push(Node ***array, Node *target, int *arrayLen){
	target->left = NULL;
	target->right = NULL;
	target->parent = NULL;

	(*arrayLen)++;
	(*array) = realloc((*array), (*arrayLen) * sizeof(Node *));
	(*array)[(*arrayLen) - 1] = target;
}

int convertToArray(Node *target, Node ***array, int *arrayLen){
	if(target){
		convertToArray(target->left, array, arrayLen);
		convertToArray(target->right, array, arrayLen);
		push(array, target, arrayLen);
	}
}

int convertToTree(Node **sourse, Tree *target, int low, int top){
	if(low > top)
		return FAILURE;
	int mid = (low + top) / 2;
	add(target, sourse[mid]->key, sourse[mid]->data);
	convertToTree(sourse, target, low + mid + 1, top);
	convertToTree(sourse, target, low, top - mid - 1);
}

int rebuild(Node **target){
	int arrayLen = 0;
	Node **array = NULL;
	convertToArray(target[0], &array, &arrayLen);

	Tree *localTree = malloc(sizeof(Tree));
	localTree->root = NULL;

	convertToTree(array, localTree, 0, arrayLen - 1);

	deleteAllNode(target[0]);
	target[0] = localTree->root;

	free(localTree);
	free(array);
	
}

int check(Node **root){
	if(root[0]){
		if(root[0]->left){
			if(root[0]->size * BALANCE_CONST <= root[0]->left->size){
				printf("DISBALANCE LEFT!\n");
				rebuild(root);
				return SUCCESS;
			}
		}
		if(root[0]->right){
			if(root[0]->size * BALANCE_CONST <= root[0]->right->size){
				printf("DISBALANCE RIGHT!\n");
				rebuild(root);
				return SUCCESS;
			}
		}
		check(&root[0]->left);
		check(&root[0]->right);
	}
}

int balance(Tree *tree){
	placeSizes(tree->root);
	check(&tree->root);
}
