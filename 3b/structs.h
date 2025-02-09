#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include <string.h>

/*
File scheme:
|mwrd|msze|csze|llen|
|kadd|ladd|0000|0000|
|0000|0000|0000|0000|
|0000|klen|karr|dlen|
|darr|nrec|gbge|....|

Legend:
mwrd - magic word 10112
msze - max size of table
csze - cur size of table
0000 - empty place (no address)
koff - key addres in body part of file
ladd - last record address in body part of file
klen - key lenght
karr - array of chars which contain key
dlen - data lenght
darr - array of chars whick contain data
nrec - address of next data record
gbge - garbage 
*/
#define MAGIC_WORD 10112
#define ADDRESS_OF_CSIZE 8
#define ADDRESS_OF_FIRST_RECORD 12
#define ADDRESS_OF_LIST_LEN(i) ADDRESS_OF_FIRST_RECORD + 3 * i * sizeof(int)
#define ADDRESS_OF_KEY(i) ADDRESS_OF_LIST_LEN(i) + sizeof(int)
#define ADDRESS_OF_LAST_RECORD(i) ADDRESS_OF_KEY(i) + sizeof(int) 
#define ADDRESS_OF_NEXT_RECORD(data, addressOfData) addressOfData + sizeof(int) + strlen(data)

#define START_PROG 10112
#define FILE_EXISTS 1
#define FILE_NOT_EXISTS 0
#define FILE_VALID 1
#define FILE_NOT_VALID 0
#define NEW_TABLE 0
#define OLD_TABLE 1
#define INIT_WITH_PATH 1
#define INIT_WITHOUT_PATH 0

typedef struct Table{
	int msize, csize;
	FILE *file;
} Table;

int initTable(Table *target, int msize, int initRule);

void setInteger(FILE *file, int target, int address);
void setString(FILE *file, char *target, int address);
int getInteger(FILE *file, int address);
char *getString(FILE *file, int address);

int getEndOfFile(FILE *file);

void increaseListLen(FILE *file, int address);
void reduceListLen(FILE *file, int address);

#endif
