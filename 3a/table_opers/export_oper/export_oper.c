#include <stdio.h>
#include "../../structs.h"
#include "../../utils/utils.h"
#include "readline/readline.h"

int export_process(Table *table, char *froot){
	table->exroot = froot;
	table->extable = fopen(froot, "w");
	fprintf(table->extable, "%d\n", table->csize);
	for(int i = 0; i < table->csize; i++){
		fprintf(table->extable, "%s\n", table->ks[i].key);
		Node *ptr = table->ks[i].list->head;
		while(ptr->next){
			fprintf(table->extable, "%s-->", ptr->data);	
			ptr = ptr->next;
		}
		fprintf(table->extable, "%s\n", ptr->data);	
	}
	fclose(table->extable);
	return 0;
}

int export(Table *table){
	if(table->csize == 0){
		printf("Nothing to export!\n");
		return 1;
	}
	printf("\n");
	//char *froot  = readstr("Enter root -->");
	char *froot  = readline("Enter root -->");
	printf("\n");

	export_process(table, froot);
	
	return 1;
}
