#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Data{
	char *data;
} Data;

typedef struct KeySpace{
	int busy;
	char *key;
	Data *data; // TODO info хорошо бы храгить отдельной структурой.
} KeySpace;

typedef struct Table{
	int msize, csize; // зачем нужен csize в перемеанной таблице? 
	KeySpace *data;
} Table;

Data *initData(char *data);
KeySpace initKeySpace(char *key, Data *data);
void deleteKeySpace(KeySpace *target);

Table initTable(int msize);
void deleteTable(Table *target);

#endif
