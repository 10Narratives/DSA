#ifndef ADD_NODE_OPER
#define ADD_NODE_OPER
#include "../../structs.h"

void do_new_ks(Table *table, char *new_key);
int insert(Table *table, char *new_key, char *new_data);
int add_node(Table *table);

#endif

