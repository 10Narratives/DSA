#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "structs.h"

#define SUCCESS 1
#define FAILURE 0

int add(Tree *root, int key, int data){

	if(!root->root){
		root->root = getNode(key, data, NULL);
		return SUCCESS;
	}

	Node *tmp = root->root;
	while(tmp){
		if(tmp->key <= key){

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

Node **find(Tree *tree, int key, int *foundLen){
	if(!tree->root)
		return NULL;

	Node **result = NULL,
		 *tmp = tree->root;
	while(tmp){
		if(tmp->key == key){

			(*foundLen)++;
			result = realloc(result, (*foundLen) * sizeof(Node *));
			result[(*foundLen) - 1] = tmp;
			tmp = tmp->right;
			continue;
			
		} else if(tmp->key <= key){
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
		target->key = localMax->key;				
		target->data = localMax->data;				
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

	free(target);

	return SUCCESS;
}

int bypass(Node *target, int low, int top){
	if(target){
		if((target->key >= low) && (target->key <= top)){
			printf("{KEY %d DATA %d}\n", target->key, target->data);
			bypass(target->left, low, top);
			bypass(target->right, low, top);
		}
	}
}

int import(Tree *tree, FILE *file){
	int key = 0, data = 0;
	while(!feof(file)){
		fscanf(file, "%d", &key);
		fscanf(file, "%d", &data);
		add(tree, key, data);
	}
	return SUCCESS;
}
