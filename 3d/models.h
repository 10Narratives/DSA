#ifndef MODELS_H
#define MODELS_H
#include "structs.h"
#include <stdio.h>

int add(Table *table, char *key, char *data);
int find(Table *table, char *key, char **data, int *foundH);
int delete(Table *table, char *key);
int import(Table *table, FILE *file);
int rebuild(Table *table);

#endif
