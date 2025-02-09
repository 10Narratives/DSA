#ifndef MODELS_H
#define MODELS_H
#include "structs.h"
#include <stdio.h>

int add(Table *table, char *key, char *info); //добывление в таблицу, из данных строк собирает объект вставляемый в таблицу
int import(Table *table, FILE *sourse); //использует функцию добавления
KeySpace *find(Table *table, char *key, int *foundH); // отдаёт указатель на найденный объект и черех параметр отдаёт на верх индекс найденого ключа
int delete(Table *table, char *key); // использует функцию поиска

#endif
