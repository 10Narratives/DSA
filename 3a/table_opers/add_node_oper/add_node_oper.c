#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "../../structs.h"
#include "../../structs_utils/structs_utils.h"
#include "../../utils/utils.h"

int is_table_overflow(Table *table){
	if((*table).csize + 1 > (*table).msize) return 1;
	return 0;
}

int is_init(Table *table){
	if((*table).csize != 0) return 1;
	return 0;
}

void do_new_ks(Table *table, char* new_key){
	KeySpace new_ks = {new_key, calloc(1, sizeof(List))};
	new_ks.list->size = 0;
	(*table).csize++;
	table->ks[table->csize - 1] = new_ks;
}

int insert(Table *table, char* new_key, char* new_data){
	int index = -1;

	if(is_init(table)){
		if(!have_key(table, new_key, &index)){
			if(!is_table_overflow(table)){
				do_new_ks(table, new_key);
				list_push((*table).ks[(*table).csize - 1].list, new_data);
			} else{
				return 1;
			}	
		} else{
		free(new_key);
		list_push(table->ks[index].list, new_data);
		}
	} else {
		do_new_ks(table, new_key);
		list_push((*table).ks[(*table).csize - 1].list, new_data);
	}


	return 0;
}

int add_node(Table *table){
	const char *errmsgs[] = {"Success:", "Error. Table overflow:"};
	printf("\n");
	char *new_key = readline("Enter new key -->");
	if(!new_key) return 0;
	char *new_data = readline("Enter new data -->");
	if(!new_data) return 0;
	printf("\n");
	int rc = -1;
	if((rc = insert(table, new_key, new_data)) == 1){
		printf("%s Can not add key %s.\n", errmsgs[rc], new_key);
		free(new_data);
		free(new_key);
	} else{
		printf("%s was added.\n", errmsgs[rc]);
	}
	printf("\n");
	return 1;
}


