#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "hashFuncs.h"
#include "views.h"

//TODO этот файнд можно оставить как есть, но для использования в диплоговй фунции поиска надо другой немного. См. туду в диплоговом файле 
KeySpace *find(Table *table, char *key, int *foundH){
	int h = genHash(key, table->msize); // с расчёт основного хеша
	while(table->data[h].busy == 1){
		if(strcmp(table->data[h].key, key) == 0){
			if(foundH) *foundH = h;
			return &table->data[h];
		}
		h += incHash(key, table->msize); // инкремирование основного хеша
		if(h > table->msize - 1) // поправка на размер таблицы
			h = 0;
	}
	return NULL;
} // алгорит расчёта хеша, описанный выше, используется во всех остальных функциях

int add(Table *table, char *key, char *info){
	if(table->msize == table->csize)
		return ERR_OVERFLOW;

	if(find(table, key, NULL))
		return ERR_DUP;

	int h = genHash(key, table->msize);
	while(table->data[h].busy == 1){
		h += incHash(key, table->msize);
		if(h > table->msize - 1)
			h = 0;
	}
	
	table->data[h] = initKeySpace(key, initData(info));
	table->data[h].busy = 1;

	return SUCCESS;
}

int delete(Table *table, char *key){
	int h = -1; 
	if(!find(table, key, &h))
		return ERR_NOT_FOUND;
	else
		deleteKeySpace(&table->data[h]);
	return SUCCESS;
}

int import(Table *table, FILE *sourse){
	char key[100], info[100];
	while(!feof(sourse)){
		if(fgets(key, 100, sourse) == NULL)
			return ERR_MEM;
		if(fgets(info, 100, sourse) == NULL)
			return ERR_MEM;
		key[strlen(key) - 1] = '\0';
		info[strlen(info) - 1] = '\0';
		char *addingKey = strdup(key), *addingInfo = strdup(info);
		if(!add(table, addingKey, addingInfo)){
			free(addingKey);
			free(addingInfo);
		}				
	}
	return SUCCESS;
}
