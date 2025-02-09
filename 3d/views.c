#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>

#include "structs.h"
#include "models.h"

#define SUCCESS 1
#define FAILURE 0
#define FIRST_RECORD 12
#define HEAD_RECORD_LEN 12
#define HEAD_KEY_POS 4
#define HEAD_DATA_POS 8

int D_add(Table *table){
	char *errmsgs[] = {"FAILURE ADD!", "SUCCESS ADD!"};
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	char *data = readline("ENTER DATA --> ");
	if(!key)
		return FAILURE;
	printf("%s\n", errmsgs[add(table, key, data)]);
	free(key); free(data);
	return SUCCESS;
}

int print(Table *table){
	printf("KEYS\tDATA\n");
	for(int i = 0; i < table->msize; i++){
		if(getInteger(table->data, FIRST_RECORD + i * HEAD_RECORD_LEN)){
			char *key = getString(table->data, FIRST_RECORD + i * HEAD_RECORD_LEN + HEAD_KEY_POS);
			char *data = getString(table->data, FIRST_RECORD + i * HEAD_RECORD_LEN + HEAD_DATA_POS);
			printf("%s\t%s\n", key, data);
			free(key); free(data);
		}
	}
}

int D_find(Table *table){
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	char *data = NULL; int foundH = -1;
	if(find(table, key, &data, &foundH)){
		printf("KEY: %s DATA: %s\n", key, data);
		free(data);
	} else{
		printf("NOTHING WAS BEEN FOUND!\n");
	}
	free(key); 
	return SUCCESS;
}

int D_delete(Table *table){
	char *errmsgs[] = {"FAILURE DELETE!", "SUCCESS DELETE!"};
	char *key = readline("ENTER KEY --> ");
	if(!key)
		return FAILURE;
	printf("%s\n", errmsgs[delete(table, key)]);
	free(key);
	return SUCCESS;
}

int D_import(Table *table){
	char *fpath = readline("ENTER PATH --> ");
	if(!fpath)
		return FAILURE;
	FILE *file = fopen(fpath, "r"); free(fpath);
	import(table, file);
	return SUCCESS;
}
