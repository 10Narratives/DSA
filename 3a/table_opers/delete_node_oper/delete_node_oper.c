#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "../../structs.h"
#include "../../structs_utils/structs_utils.h"
#include "../../utils/utils.h" 
#include "../../dialog/dialog.h"
#include "../delete_table_oper/delete_table_oper.h"

int delete(Table *table, char *del_key, int del_vers){
	if(table->csize == 0) return 1;

	int index = -1;
	if(have_key(table, del_key, &index)){
		if(del_vers == -1 || table->ks[index].list->size == 1){
			free(table->ks[index].key);
			delete_list(table->ks[index].list);
			for(int i = 0; i < table->csize - 1; i++){
				table->ks[i] = table->ks[i + 1];
			}
			table->csize--;
			printf("Rule\n");
			return 0;
		} else if(have_version(table->ks[index].list, del_vers)){
			list_delete_node(table->ks[index].list, del_vers);
			return 0;			
		} else {
			return 2;
		}	
	} else{
		return 1;	
	}
}

int delete_node(Table *table){
	const char *errmsgs[] = {"Success: info was deleted", "Error: key do not exist", "Error: version do not exist"};

	//char *del_key = readstr("Enter key --> ");
	char *del_key = readline("Enter key --> ");
	printf("Enter version. If you want to remove all key press '-1'. Enter --> ");
	int del_vers = get_int();
	
	printf("\n");
	int rc = delete(table, del_key, del_vers);
	printf("%s\n", errmsgs[rc]);
	printf("\n");
	free(del_key);

	return 1;
}

		
