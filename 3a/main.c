#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "utils/utils.h"
#include "dialog/dialog.h"

#include "table_opers/add_node_oper/add_node_oper.h"
#include "table_opers/delete_node_oper/delete_node_oper.h"
#include "table_opers/delete_table_oper/delete_table_oper.h"
#include "table_opers/new_table_oper/new_table_oper.h"
#include "table_opers/print_table_oper/print_table_oper.h"
#include "table_opers/search_node_oper/search_node_oper.h"
#include "table_opers/import_oper/import_oper.h"
#include "table_opers/export_oper/export_oper.h"

int main(){
	printf("!-----Start_Work-----!\n");
	int (*fptr[])(Table *) = {NULL, add_node, delete_node, search, print_table, import, export};
	Table table = init_start_table();
	const char *msgs[] = {"0. Quit", "1. Add", "2. Delete", "3. Search", "4. Print", "5. Import", "6. Export"};
	int N = sizeof(msgs)/sizeof(msgs[0]);
	int rc = dialog(msgs, N);
	while(rc > 0){
		if(!fptr[rc](&table)) break;
		rc = dialog(msgs, N);
	}
	delete_table(&table);
	printf("!------End_Work------!\n");
	return 0;
}
