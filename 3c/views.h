#ifndef VIEWS_H
#define VIEWS_H
#include "structs.h"

#define SUCCESS 1
#define ERR_MEM 0
#define ERR_DUP 0
#define ERR_OVERFLOW 0
#define ERR_NOT_FOUND 0

int D_add(Table *table);
int D_import(Table *table);
int print(Table *table);
int D_find(Table *table);
int D_delete(Table *table);

#endif
