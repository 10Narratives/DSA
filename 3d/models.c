#include <stdio.h>
#include "readline/readline.h"
#include <string.h>
#include <stdlib.h>

#include "hashFuncs.h"
#include "structs.h"

#define SUCCESS 1
#define FAILURE 0
#define FIRST_RECORD 12
#define HEAD_RECORD_LEN 12
#define HEAD_KEY_POS 4
#define HEAD_DATA_POS 8
#define BUSY 1
#define FREE 0
#define MSIZE 4
#define CSIZE 8
#define MAGIC_WORD 10112

int find(Table *table, char *key, char **data, int *foundH){
	int h = genHash(key, table->msize);
	while(getInteger(table->data, FIRST_RECORD + h * HEAD_RECORD_LEN)){
		char *str = getString(table->data, FIRST_RECORD + h * HEAD_RECORD_LEN + HEAD_KEY_POS);
		if(strcmp(key, str) == 0){
			*data = str;
			*foundH = h;
			return SUCCESS;
		}
		h += incHash(key, table->msize);
		if(h > table->msize - 1)	
			h  = 0;
	}

	return FAILURE;
}

int add(Table *table, char *key, char *data){
	if(table->msize == table->csize)
		return FAILURE;

	char *localData = NULL; int foundH = -1;
	if(find(table, key, &localData, &foundH)){
		free(localData);
		return FAILURE;
	}

	int h = genHash(key, table->msize);
	while(getInteger(table->data, FIRST_RECORD + h * HEAD_RECORD_LEN)){
		h += incHash(key, table->msize);
		if(h > table->msize - 1)	
			h  = 0;
	}

	setInteger(table->data, FIRST_RECORD + h * HEAD_RECORD_LEN, BUSY);
	setString(table->data, key, FIRST_RECORD + h * HEAD_RECORD_LEN + HEAD_KEY_POS);
	setString(table->data, data, FIRST_RECORD + h * HEAD_RECORD_LEN + HEAD_DATA_POS);
	table->csize++;
	setInteger(table->data, CSIZE, table->csize);
	return SUCCESS;
}

int delete(Table *table, char *key){
	if(table->csize == 0)
		return FAILURE;

	char *localData = NULL; int foundH  = -1;
	if(!find(table, key, &localData, &foundH))
		return FAILURE;
	free(localData);

	setInteger(table->data, FIRST_RECORD + foundH * HEAD_RECORD_LEN, FREE);
	table->csize--;
	setInteger(table->data, CSIZE, table->csize);

	return SUCCESS;	
}

int import(Table *table, FILE *file){
	char key[100], data[100];
	while(!feof(file)){
		if(!fgets(key, 100, file))
			return FAILURE;
		if(!fgets(data, 100, file))
			return FAILURE;
		key[strlen(key) - 1] = '\0';
		data[strlen(data) - 1] = '\0';		
		add(table, key, data);
 
	}
	return SUCCESS;
}

int rebuild(Table *table){
	Table newTable = {0, 0, NULL}; 
	initTable(&newTable, table->msize);
	for(int i = 0; i < table->msize; i++){
		if(getInteger(table->data, FIRST_RECORD + i * HEAD_RECORD_LEN)){
			char *key = getString(table->data, FIRST_RECORD + i * HEAD_RECORD_LEN + HEAD_KEY_POS);
			char *data = getString(table->data, FIRST_RECORD + i * HEAD_RECORD_LEN + HEAD_DATA_POS);
			add(&newTable, key, data);
			free(key); free(data);
		}
	}
	return SUCCESS;
}
