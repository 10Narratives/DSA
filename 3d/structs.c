#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "structs.h"

#define SUCCESS 1
#define FAILURE 0
#define MWORD 10112

int initTable(Table *table, int msize){
	char *fpath = readline("ENTER PATH TO YOUR FILE --> ");
	while(!fpath){
		printf("MEMORY WAS NOT BEEN ALLOCATED\n");
		int rc = getInt("IF YOU WANT TO END PROGRAM PRESS -1");
		if(rc == -1)
			break;
		fpath = readline("ENTER NEW PATH --> ");
	}
	if(!fpath)
		return FAILURE;
	FILE *file = fopen(fpath, "wb+");
	free(fpath);
	int mword = MWORD, csize = 0;
	fwrite(&mword, 1, sizeof(int), file);
	fwrite(&msize, 1, sizeof(int), file);
	fwrite(&csize, 1, sizeof(int), file);
	int initInt = 0;
	for(int i = 0; i < msize * 3; i++)
		fwrite(&initInt, 1, sizeof(int), file);
	Table newTable = {msize, csize, file};
	*table = newTable;
	return SUCCESS;
}

int setString(FILE *file, char *target, int headPosition){
	if(!target)
		return FAILURE;
	fseek(file, 0, SEEK_END);
	int valueForHeadPos = ftell(file), targetLen = strlen(target);
	fwrite(&targetLen, 1, sizeof(int), file); fwrite(target, targetLen, sizeof(char), file);
	fseek(file, headPosition, SEEK_SET);
	fwrite(&valueForHeadPos, 1, sizeof(int), file);
	return SUCCESS;
}

char *getString(FILE *file, int headPosition){
	int bodyPosition = 0;
	fseek(file, headPosition, SEEK_SET); fread(&bodyPosition, 1, sizeof(int), file);
	int targetLen = 0; char *target = NULL;
	fseek(file, bodyPosition, SEEK_SET); fread(&targetLen, 1, sizeof(int), file);
	target = malloc(targetLen + 1);
	fread(target, targetLen, sizeof(char), file);
	target[targetLen] = '\0';
	return target;
}

int getInteger(FILE *file, int headPosition){
	fseek(file, headPosition, SEEK_SET);
	int state = -1; fread(&state, 1, sizeof(int), file);
	return state;
}

int setInteger(FILE *file, int headPosition, int newState){
	fseek(file, headPosition, SEEK_SET);
	fwrite(&newState, 1, sizeof(int), file);
	return SUCCESS;
}
