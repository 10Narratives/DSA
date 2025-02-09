#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>

#include "structs.h"
#include "views.h"
#include "models.h"
#include "utils.h"

int D_add(Table *table){
	const char* errmsgs[] = {"SUCCESS ADD!", "TABLE IS OVERFLOW!", "MEMORY WAS NOT BEEN ALLOCATED!"};
	char *key = readline("ENTER KEY --> ");
	if(!key){
		printf("\n%s\n\n", errmsgs[ERR_MEM]);
		return ERR_MEM;
	}	
	char *data = readline("ENTER DATA --> ");
	if(!data){
		printf("\n%s\n\n", errmsgs[ERR_MEM]);
		return ERR_MEM;
	}	
	printf("\n%s\n\n", errmsgs[add(table, key, data)]);
	free(key); free(data);
	return SUCCESS;
}

int printKeySpace(FILE *file, int index){
	int listLen = getInteger(file, ADDRESS_OF_LIST_LEN(index));
	char *currKey = getString(file, getInteger(file, ADDRESS_OF_KEY(index)));
	printf("%s %d ", currKey, listLen);

	int addressOfCurrData = getInteger(file, ADDRESS_OF_LAST_RECORD(index));
	char *currData = getString(file, addressOfCurrData);
	for(int i = getInteger(file, ADDRESS_OF_LIST_LEN(index)); i > 0; i--){
		printf("%s ", currData);
		addressOfCurrData = getInteger(file, ADDRESS_OF_NEXT_RECORD(currData, addressOfCurrData));
		free(currData);
		currData = getString(file, addressOfCurrData);
	}
	free(currData);
	free(currKey);
	printf("\n");
}

int print(Table *table){
	printf("TABLE MAIN INFO:\nMSIZE: %d\nCSIZE: %d\n", table->msize, table->csize);
	printf("KEY LIST_LEN DATA:\n");
	for(int i = 0; i < table->msize; i++){
		if(getInteger(table->file, ADDRESS_OF_KEY(i)) == 0) continue;
		printKeySpace(table->file, i);
	}
	printf("\n\n\n\n");
	return SUCCESS;
}

int D_find(Table *table){
	const char *errmsgs[] = {"SUCCESS FIND!", "KEY WAS NOT BEEN FOUND!", "MEMORY WAS NOT BEEN ALLOCATED!"};
	Table foundTable = {0, 0, NULL};
	if(!initTable(&foundTable, 1, INIT_WITH_PATH)){
		printf("\n%s\n\n", errmsgs[ERR_MEM]);
		return ERR_MEM;
	}
	char *key = readline("ENTER KEY--> ");
	if(!key){
		printf("\n%s\n\n", errmsgs[ERR_MEM]);
		return ERR_MEM;
	}
	int foundIndex = -1;
	if(checkOnly(table, key, &foundIndex) == ERR_NOT_FOUND){
		printf("\n%s\n\n", errmsgs[ERR_NOT_FOUND]);
		return SUCCESS;
	}
	free(key);
	int rule = getInt("ENTER INDEX OF DATA. IF YOU WANT TO FIND ALL -1 -->");
	if(rule == ALL){
		copyAll(table, &foundTable, foundIndex);
		print(&foundTable);
	} else{
		copyRelease(table, &foundTable, foundIndex, rule);
		print(&foundTable);
	}	
	return SUCCESS;
}

int D_delete(Table *table){
	const char *errmsgs[] = {"SUCCESS DELETE!", "KEY WAS NOT BEEN FOUND!", "MEMORY WAS NOT BEEN ALLOCATED!"};
	Table deleteTable = {0, 0, NULL};
	if(!initTable(&deleteTable, 1, INIT_WITH_PATH)){
		printf("\n%s\n\n", errmsgs[ERR_MEM]);
		return ERR_MEM;
	}
	char *key = readline("ENTER KEY--> ");
	if(!key){
		printf("\n%s\n\n", errmsgs[ERR_MEM]);
		return ERR_MEM;
	}
	int deleteIndex = -1;
	if(checkOnly(table, key, &deleteIndex) == ERR_NOT_FOUND){
		printf("\n%s\n\n", errmsgs[ERR_NOT_FOUND]);
		return SUCCESS;
	}
	free(key);
	int rule = getInt("ENTER INDEX OF DATA. IF YOU WANT TO DELETE ALL -1 -->");
	if(rule == ALL){
		copyAll(table, &deleteTable, deleteIndex);
		deleteAll(table, deleteIndex);
	} else{
		copyRelease(table, &deleteTable, deleteIndex, rule);
		deleteRelease(table, deleteIndex, rule);
	}	
	return SUCCESS;
}

int D_import(Table *table){
	char *fpath = readline("ENTER PATH YOUR FILE --> ");
	if(!fpath)
		return ERR_MEM;
	FILE *file = fopen(fpath, "r");
	import(table, file);
	free(fpath);
	fclose(file);
	return SUCCESS;	
}
