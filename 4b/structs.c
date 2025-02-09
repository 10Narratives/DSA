#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

Tree *initTree(){
	Tree *newTree = malloc(sizeof(Tree));
	newTree->root = NULL;
	return newTree;
}

Node *getNode(int key, int data, Node *parent){
	Node *newNode = malloc(sizeof(Node));
	newNode->key = key;
	newNode->data = data;
	newNode->size = 0;
	newNode->right = NULL;
	newNode->left = NULL;
	newNode->parent = parent;
	return newNode;
}

void deleteNode(Node *target){
	free(target);
	return;
}

void deleteAllNode(Node *target){
	if(target){
		deleteAllNode(target->left);
		deleteAllNode(target->right);
		deleteNode(target);
	}
	return;
}

void deleteTree(Tree *target){
	Node *root = target->root;
	if(root)
		deleteAllNode(root);
	free(target);
	return;
}

Node *findMaxNode(Node *sourse){
	while(sourse->right)
		sourse = sourse->right;
	return sourse;
}

Node *findMinNode(Node *sourse){
	while(sourse->left)
		sourse = sourse->left;
	return sourse;
}
