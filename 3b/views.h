#ifndef VIEWS_H
#define VIEWS_H
#include "structs.h"

#define SUCCESS 0
#define ERR_OFLOW 1
#define ERR_MEM 2
#define ERR_NOT_FOUND 2
#define ALL -1
#define ERR_NOT_EXIST 2

int D_add(Table *table);
int D_find(Table *table);
int D_delete(Table *table);
int D_import(Table *table);
int print(Table *table);

#endif
