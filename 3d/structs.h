#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>

/*
File scheme:
------------------------
mWord|msize|csize|rcoff| \
rcoff|rcoff|rcoff|rcoff|  head  
rcoff|rcoff|rcoff|rcoff| /
------------------------
rckey|rcdat|rckey|rcdat|\
gbage|gbage|rckey|rcdat| \
rckey|rcdat|rckey|rcdat|  body
rckey|rcdat|rckey|rcdat| /
rckey|rcdat|rckey|rcdat|/
-----------------------
Legend:
mWord - magic word. Program uses 10112 code
msize - the maximum size of a table
csize - the current size of a table
rcoff - record offset looks like: {state + key offset + data offset}
rckey - record key looks like: {keyLen + array of chars}
rcdat - record data looks like: {dataLen + array of chars}
gbage - garbage which may turn out to be (file sould be rebuilt after program work)
*/

typedef struct Table{
	int msize, csize;
	FILE *data; 
} Table;

int initTable(Table *table, int msize);

char *getString(FILE *file, int headPosition);
int setString(FILE *file, char *target, int headPosition);

int getInteger(FILE *file, int headPosition);
int setInteger(FILE *file, int headPosition, int newState);

#endif
