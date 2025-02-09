#ifndef MODELS_H
#define MODELS_H
#include "structs.h"
#include <stdio.h>

int add(Tree *root, int key, int data);
Node **find(Tree *tree, int key, int *foundLen);
int delete(Tree *tree, Node *target);
int bypass(Node *target, int low, int top);
int spfind(Tree *target, int key);
int import(Tree *tree, FILE *file);

#endif
