#ifndef MODELS_H
#define MODELS_H
#include "structs.h"
#include <stdio.h>

int checkOnly(Table *table, char *key, int *index);
int add(Table *table, char *key, char *data);
int copyAll(Table *sourse, Table *newPlace, int foundIndex);
int copyRelease(Table *sourse, Table *newPlace, int foundIndex, int release);
int deleteAll(Table *table, int deleteIndex);
int deleteRelease(Table *sourse, int deleteIndex, int release);
int import(Table *table, FILE *file);
int rebuild(Table *table);

#endif
