#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>

typedef struct Node{
	int version;
	char *data;
	struct Node *next;
}Node;

typedef struct List{
	int size;
	Node *head;
} List;

typedef struct KeySpace {
	char *key;
	List *list;
} KeySpace;

typedef struct Table {
	KeySpace *ks;
	int msize;
	int csize;
	char* imroot;
	char* exroot;
	FILE *imtable;
	FILE *extable;
} Table;

#endif
