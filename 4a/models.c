#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "structs.h"

#define SUCCESS 1
#define FAILURE 0

int add(Tree *tree, char *key, char *data){

	if(!tree->root){
		tree->root = getNode(key, data, NULL);
		return SUCCESS;
	}

	Node *tmp = tree->root;
	while(tmp){
		if(strcmp(tmp->key, key) <= 0){

			if(tmp->right){
				tmp = tmp->right;
				continue;
			} else{
				tmp->right = getNode(key, data, tmp);
				return SUCCESS;
			}
			
		} else{

			if(tmp->left){
				tmp = tmp->left;
				continue;
			} else{
				tmp->left = getNode(key, data, tmp);
				return SUCCESS;
			}
			
		} 
	}
}

Node **find(Tree *tree, char *key, int *foundLen){
	if(!tree->root)
		return NULL;

	Node **result = NULL,
		 *tmp = tree->root;
	while(tmp){
		if(strcmp(tmp->key, key) == 0){

			(*foundLen)++;
			result = realloc(result, (*foundLen) * sizeof(Node *));
			result[(*foundLen) - 1] = tmp;
			tmp = tmp->right;
			continue;
			
		} else if(strcmp(tmp->key, key) < 0){
			tmp = tmp->right;			
		}  else{		
			tmp = tmp->left;
		}
	}

	return result;
}

int delete(Tree *tree, Node *target){

	if(target->left && target->right){
	
		Node *localMax = findMaxNode(target->left);
		free(target->key);
		free(target->data);
		target->key = strdup(localMax->key);				
		target->data = strdup(localMax->data);				
		delete(tree, localMax);
		return SUCCESS;
	
	} else if(target->left){

		if(tree->root == target){
			tree->root = target->left;
		} else{
			if(target == target->parent->left)
				target->parent->left = target->left;
			else
				target->parent->right = target->left;
		}
	
	} else if(target->right){

		if(tree->root == target){
			tree->root = target->right;
		} else{
			if(target == target->parent->left)
				target->parent->right = target->right;
			else
				target->parent->right = target->right;
		}		
		
	} else{
		if(tree->root == target){
			tree->root = NULL;	
		} else {
			if(target == target->parent->left)
				target->parent->left = NULL;
			else
				target->parent->right = NULL;
				
		}
	}

	free(target->key);
	free(target->data);
	free(target);


	return SUCCESS;
}

int bypass(Node *target){
	if(target){
		bypass(target->left);
		bypass(target->right);
		printf("{KEY %s DATA %s}\n", target->key, target->data);
	}
}

int spfind(Tree *tree, char *key){
	Node **result = NULL; int resultSize = 0;

	Node *localMax = findMaxNode(tree->root); int max = atoi(localMax->key);
	Node *localMin = findMinNode(tree->root); int min = atoi(localMin->key);

	int mid = (max + min) / 2;
	int keyInt = atoi(key);

	if(keyInt >= mid){
		result = find(tree, localMin->key, &resultSize);
	}
	if(keyInt < mid){
		result = find(tree, localMax->key, &resultSize);
	}

	printf("%d ", resultSize);

	for(int i = 0; i < resultSize; i++)
		printf("{%s %s}\n", result[i]->key, result[i]->data);
	free(result);
	return SUCCESS;
}

int import(Tree *tree, FILE *file){
	char key[100]; char data[100];
	while(!feof(file)){
		if(fgets(key, 100, file) ==  NULL){
			return FAILURE;
		}
		if(fgets(data, 100, file) ==  NULL){
			return FAILURE;
		}
		key[strlen(key) - 1] = '\0';
		data[strlen(data) - 1] = '\0';
		add(tree, strdup(key), strdup(data));
	}
	return SUCCESS;
}
