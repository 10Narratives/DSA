#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "../../utils/utils.h"
#include "../../structs.h"
#include "../../structs_utils/structs_utils.h"
#include "../new_table_oper/new_table_oper.h"
#include "../delete_table_oper/delete_table_oper.h"
#include "../print_table_oper/print_table_oper.h"
#include "../add_node_oper/add_node_oper.h"
#include "../../dialog/dialog.h"

int search_node(Table *table, char *search_key, int search_vers){
	if(table->csize == 0) return 1;

	int index = -1;
	if(have_key(table, search_key, &index) == 1){
		Table local = init_empty_table(1);

		if(search_vers == -1){
			do_new_ks(&local, strdup(table->ks[index].key));
			free(local.ks[0].list);
			local.ks[0].list = table->ks[index].list;
			print_table(&local);
			local.ks[0].list = NULL;
			delete_table(&local);
			return 0;
		} else if(have_version(table->ks[index].list, search_vers)){
			Node *buf = NULL; find_node(table->ks[index].list, &buf, search_vers);
			do_new_ks(&local, strdup(table->ks[index].key));
			list_push(local.ks[0].list, strdup(buf->data));
			print_table(&local);
			delete_table(&local);
			return 0;			
		} else{
			return 2;
		}

	} else {
		return 1;
	}
	
	return 0;	
}

int search(Table *table){
	const char *errmsgs[] = {"Success: info was found", "Error: key do not exist", "Error: version do not exist"};
	//char *search_key = readstr("Enter key --> ");
	char *search_key = readline("Enter key --> ");
	printf("Enter version. If you want to search all key press '-1'. Enter --> ");
	int search_vers = get_int();
	
	printf("\n");
	int rc = search_node(table, search_key, search_vers);
	printf("%s\n", errmsgs[rc]);
	printf("\n");
	free(search_key);

	return 1;
}
