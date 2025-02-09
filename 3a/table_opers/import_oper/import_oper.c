#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "../add_node_oper/add_node_oper.h"
#include "../../utils/utils.h"
#include "../../structs.h"
#include "../../structs_utils/structs_utils.h"

int import(Table *table){
	char *fpath = readline("ENTER PATH YO YOUR FILE --> ");
	if(!fpath)
		return 0;
	FILE *file = fopen(fpath, "r");
	free(fpath);
	char key[100], data[100];
	while(!feof(file)){
		if(fgets(key, 100, file) == NULL)
			return 1;
		if(fgets(data, 100, file) == NULL)
			return 1;
		key[strlen(key) - 1] = '\0';
		data[strlen(data) - 1] = '\0';
		char *addingKey = strdup(key);
		char *addingData = strdup(data);
		if(!insert(table, addingKey, addingData)){
			free(addingKey);
			free(addingData);
		}
		
	}
	return 1;
}
