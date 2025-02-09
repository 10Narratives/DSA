#include <stdio.h>
#include "../../structs.h"

void list_print(const List *list){
	Node *ptr = list->head;
	printf("------List__Info------\n");
	printf("List size:       %d\n", (*list).size);
	printf("----------------------\n");
	while(ptr){
		printf("----------------------\n");
		printf("Version:        %d\n", ptr->version);
		printf("Data:           %s\n", ptr->data);
		printf("----------------------\n");
		ptr = ptr->next;
	}
}

void print_table_info(Table *table){
	printf("------Table_Info------\n");
	printf("Occupied space: %d\n", (*table).csize);
	printf("Total space:    %d\n", (*table).msize);
	if(table->imroot) printf("Import root:    %s\n", table->imroot);
	if(table->exroot)printf("Export root:    %s\n", table->exroot);
	printf("----------------------\n");
}

int print_table(Table *table){
	print_table_info(table);
    for(int i = 0; i < table->csize; i++){
    	printf("Nodes at key: %s\n", (*table).ks[i].key);    
		list_print((*table).ks[i].list);
    }
    return 1;
}
