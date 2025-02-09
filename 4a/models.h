#ifndef MODELS_H
#define MODELS_H
#include "structs.h"
#include <stdio.h>

int add(Tree *tree, char *key, char *data);
Node **find(Tree *tree, char *key, int *foundLen);
int delete(Tree *tree, Node *target);
int bypass(Node *target);
int spfind(Tree *target, char *key);
int import(Tree *tree, FILE *file);

#endif
