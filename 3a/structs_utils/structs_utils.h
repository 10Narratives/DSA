#ifndef STRUCTS_UTILS_H
#define STRUCTS_UTILS_H
#include "../structs.h"

int have_key(Table *table, char *checking_key, int *index);
int have_version(List *list, int vers);
int list_delete_node(List *list, int vers);
int delete_list(List *list);
int list_push(List *list, char *data);
List *copy_list(List *source);
Node *copy_node(Node *source);
int find_node(List *list, Node **buf, int vers;);

#endif
