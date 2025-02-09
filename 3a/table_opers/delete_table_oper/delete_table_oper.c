#include <stdio.h>
#include <stdlib.h>
#include "../../structs.h"
#include "../../structs_utils/structs_utils.h"

int delete_table(Table *table){
	for(int i = 0; i < (*table).csize; i++){
			delete_list((*table).ks[i].list);
			free((*table).ks[i].key);
	}
	free(table->imroot);
	free(table->exroot);
	free(table->ks);
}
