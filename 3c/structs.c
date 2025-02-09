#include <stdlib.h>

#include "structs.h"
#include "utils.h"

Data *initData(char *data){
	Data *newData = calloc(1, sizeof(Data));
	newData->data = data;
	return newData;
}

KeySpace initKeySpace(char *key, Data *data){
	KeySpace newKeySpace = {0, key, data};
	return newKeySpace;
}

Table initTable(int msize){
	KeySpace *newData = malloc(msize * sizeof(KeySpace));
	for(int i = 0; i < msize; i++)
		newData[i] = initKeySpace(NULL, NULL);
	Table newTable = {msize, 0, newData};
	return newTable;
}

void deleteKeySpace(KeySpace *target){
	target->busy = 0;
	free(target->key);
	free(target->data->data);
	free(target->data);
	return;
}

void deleteTable(Table *target){
	for(int i = 0; i < target->msize; i++){
		if(target->data[i].busy == 1){
			deleteKeySpace(&target->data[i]);
		}
	}
	free(target->data);
	return;
}
