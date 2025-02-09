#include <stdio.h>
#include "readline/readline.h"
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "utils.h"

#define ERR_MEM 0
#define SUCCESS 1;

int isFileExist(char *fpath){
	FILE *file = fopen(fpath, "rb");
	if(!file)
		return FILE_NOT_EXISTS;
	fclose(file);
	return FILE_EXISTS;
}

int isFileValid(char *fpath){
	FILE *file = fopen(fpath, "rb");
	int magicWord = 0;
	fread(&magicWord, 1, sizeof(int), file);
	fclose(file);
	if(magicWord != MAGIC_WORD)
		return FILE_NOT_VALID;
	return FILE_VALID;
}

int initTable(Table *target, int msize, int initRule){
	char *fpath = NULL;
	if(initRule == START_PROG){
		fpath = readline("ENTER PATH TO YOUR FILE -->");			
		if(!fpath)
			return ERR_MEM;
		int rc = getInt("CHOOSE. 0. NEW TABLE. 1. OLD TABLE");
		if(rc != NEW_TABLE){
			while(!isFileExist(fpath) || !isFileValid(fpath)){
				printf("WRONG INPUT OF FILE. TRY AGAIN\n");
				free(fpath);
				fpath = readline("ENTER PATH TO YOUR FILE -->");
				if(!fpath)
					return ERR_MEM;
			}
		}
		
	} else if(initRule == INIT_WITH_PATH){
		fpath = readline("ENTER PATH TO BUFFER FILE --> ");
		if(!fpath)
			return ERR_MEM;	
	}
	FILE *file = fopen(fpath, "wb+"); free(fpath);
	int magicWord = MAGIC_WORD, csize = 0, emptyAddress = 0;
	fwrite(&magicWord, 1, sizeof(int), file);
	fwrite(&msize, 1, sizeof(int), file);
	fwrite(&csize, 1, sizeof(int), file);
	for(int i = 0; i < msize; i++){
		fwrite(&emptyAddress, 1, sizeof(int), file);
		fwrite(&emptyAddress, 1, sizeof(int), file);
		fwrite(&emptyAddress, 1, sizeof(int), file);
	}
	Table newTable = {msize, csize, file};
	*target = newTable;
	return SUCCESS;
}

void setInteger(FILE *file, int target, int address){
	fseek(file, address, SEEK_SET);
	fwrite(&target, 1, sizeof(int), file);
	return;
}

void setString(FILE *file, char *target, int address){
	fseek(file, address, SEEK_SET);
	int targetLen = strlen(target);
	fwrite(&targetLen, 1, sizeof(int), file);
	fwrite(target, targetLen, sizeof(char), file);
	return;
}

int getInteger(FILE *file, int address){
	fseek(file, address, SEEK_SET);
	int integer = 0;
	fread(&integer, 1, sizeof(int), file);
	return integer;
}

char *getString(FILE *file, int address){
	fseek(file, address, SEEK_SET);
	int stringLen = 0;
	fread(&stringLen, 1, sizeof(int), file);
	char *string = malloc(stringLen + 1);
	fread(string, stringLen, sizeof(char), file);
	string[stringLen] = '\0';
	return string;
}

int getEndOfFile(FILE *file){
	fseek(file, 0, SEEK_END);
	int addressOfEndOfFile = ftell(file);
	return addressOfEndOfFile;
}

void increaseListLen(FILE *file, int address){
	int currLen = getInteger(file, address);
	currLen++;
	setInteger(file, currLen, address);
	return;
}

void reduceListLen(FILE *file, int address){
	int currLen = getInteger(file, address);
	currLen--;
	setInteger(file, currLen, address);
	return;
}
