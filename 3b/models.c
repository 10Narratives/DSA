#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "views.h"

#define CHECK_ONLY -2
#define ALL_RECORDS -1
#define MSIZE_FOR_FIND 1

int checkOnly(Table *table, char *key, int *index){
	for(int i = 0; i < table->msize; i++){
		if(getInteger(table->file, ADDRESS_OF_KEY(i)) > 0){
			char *currKey = getString(table->file, getInteger(table->file, ADDRESS_OF_KEY(i)));
			if(strcmp(currKey, key) == 0){
				*index = i;
				free(currKey);
				return SUCCESS;
			}
			free(currKey);
		}
	}
	return ERR_NOT_FOUND;
}

int add(Table *table, char *key, char *data){
	if(table->msize == table->csize)
		return ERR_OFLOW;
		
	int index = -1;
	if(checkOnly(table, key, &index) == SUCCESS){
		int addressOfData = getEndOfFile(table->file);
		int addressOfLastRecord = getInteger(table->file, ADDRESS_OF_LAST_RECORD(index));
		setString(table->file, data, addressOfData);
		increaseListLen(table->file, ADDRESS_OF_LIST_LEN(index));
		setInteger(table->file, addressOfLastRecord, ADDRESS_OF_NEXT_RECORD(data, addressOfData));
		setInteger(table->file, addressOfData, ADDRESS_OF_LAST_RECORD(index));
		return SUCCESS;	
	}
	int i = 0;
	for(i = 0; i < table->msize; i++)
		if(getInteger(table->file, ADDRESS_OF_KEY(i)) == 0) break;	

	int addressOfKey = getEndOfFile(table->file);
	setString(table->file, key, addressOfKey);
	int addressOfData = getEndOfFile(table->file);
	setString(table->file, data, addressOfData);
	setInteger(table->file, 0, ADDRESS_OF_NEXT_RECORD(data, addressOfData));
	increaseListLen(table->file, ADDRESS_OF_LIST_LEN(i));
	setInteger(table->file, addressOfKey, ADDRESS_OF_KEY(i));
	setInteger(table->file, addressOfData, ADDRESS_OF_LAST_RECORD(i));
	table->csize++;
	setInteger(table->file, table->csize, ADDRESS_OF_CSIZE);
	return SUCCESS;
}

int copyAll(Table *sourse, Table *newPlace, int foundIndex){
	int listLen = getInteger(sourse->file, ADDRESS_OF_LIST_LEN(foundIndex)); 
	char *key = getString(sourse->file, getInteger(sourse->file, ADDRESS_OF_KEY(foundIndex)));
	
	int addressOfCurrData = getInteger(sourse->file, ADDRESS_OF_LAST_RECORD(foundIndex));
	char *currData = getString(sourse->file, addressOfCurrData);
	for(int i = listLen; i > 0; i--){
		add(newPlace, key, currData);
		addressOfCurrData = getInteger(sourse->file, ADDRESS_OF_NEXT_RECORD(currData, addressOfCurrData));
		free(currData);
		currData = getString(sourse->file, addressOfCurrData);
	}
	free(currData);
	free(key);
	return SUCCESS;	
}

int copyRelease(Table *sourse, Table *newPlace, int foundIndex, int release){
	char *key = getString(sourse->file, getInteger(sourse->file, ADDRESS_OF_KEY(foundIndex)));
	int addressOfCurrData = getInteger(sourse->file, ADDRESS_OF_LAST_RECORD(foundIndex));
	char *currData = getString(sourse->file, addressOfCurrData);
	for(int i = getInteger(sourse->file, ADDRESS_OF_LIST_LEN(foundIndex)); i > 0; i--){
		if(release > i) break;
		if(release == i){
			add(newPlace, key, currData);
			free(currData);
			free(key);
			return SUCCESS;
		}
		addressOfCurrData = getInteger(sourse->file, ADDRESS_OF_NEXT_RECORD(currData, addressOfCurrData));
		free(currData);
		currData = getString(sourse->file, addressOfCurrData);
	}
	free(currData);
	free(key);
	return SUCCESS;	
}


int deleteAll(Table *table, int deleteIndex){
	setInteger(table->file, 0, ADDRESS_OF_LIST_LEN(deleteIndex));
	setInteger(table->file, 0, ADDRESS_OF_KEY(deleteIndex));
	setInteger(table->file, 0, ADDRESS_OF_LAST_RECORD(deleteIndex));
	table->csize--;
	setInteger(table->file, table->csize, ADDRESS_OF_CSIZE);	
	return SUCCESS;
}

int deleteRelease(Table *table, int deleteIndex, int release){
	char *key = getString(table->file, getInteger(table->file, ADDRESS_OF_KEY(deleteIndex)));
	int addressOfCurrData = getInteger(table->file, ADDRESS_OF_LAST_RECORD(deleteIndex));
	int addressOfPrevData = 0;
	char *prevData = NULL;
	char *currData = getString(table->file, addressOfCurrData);
	int listLen = getInteger(table->file, ADDRESS_OF_LIST_LEN(deleteIndex));
	if(listLen == 1){
		deleteAll(table, deleteIndex);
		reduceListLen(table->file, ADDRESS_OF_LIST_LEN(deleteIndex));
		return SUCCESS;
	}
	for(int i = listLen; i > 0; i--){
		if(release > i) break;
		if(release == i){
			if(i == listLen){
				setInteger(table->file, getInteger(table->file, ADDRESS_OF_NEXT_RECORD(currData, addressOfCurrData)), ADDRESS_OF_LAST_RECORD(deleteIndex));
			} else{
				setInteger(table->file, getInteger(table->file, ADDRESS_OF_NEXT_RECORD(currData, addressOfCurrData)), ADDRESS_OF_NEXT_RECORD(prevData, addressOfPrevData));
			}
			free(currData);
			free(key);
			if(prevData) free(prevData);
			reduceListLen(table->file, ADDRESS_OF_LIST_LEN(deleteIndex));
			return SUCCESS;
		}
		addressOfPrevData = addressOfCurrData;
		if(prevData) free(prevData);
		prevData = strdup(currData);
		addressOfCurrData = getInteger(table->file, ADDRESS_OF_NEXT_RECORD(currData, addressOfCurrData));
		free(currData);
		currData = getString(table->file, addressOfCurrData);
	}
	free(currData);
	free(key);
	return SUCCESS;	
}

int import(Table *table, FILE *file){
	char key[100], data[100];
	while(!feof(file)){
		if(!fgets(key, 100, file))
			return ERR_MEM;
		if(!fgets(data, 100, file))
			return ERR_MEM;
		key[strlen(key) - 1] = '\0';
		data[strlen(data) - 1] = '\0';
		char *addingKey = strdup(key);
		char *addingData = strdup(data);
		add(table, addingKey, addingData);
		free(addingKey);
		free(addingData);
	}
	return SUCCESS;
}

int rebuild(Table *table){
	Table newTable = {0, 0, NULL};
	if(!initTable(&newTable, table->msize, INIT_WITH_PATH))
		return ERR_MEM;
	for(int i = 0; i < table->msize; i++){
		if(getInteger(table->file, ADDRESS_OF_LIST_LEN(i)) != 0){
			copyAll(table, &newTable, i);
		}
	}
	*table = newTable;
	return SUCCESS;		
}
