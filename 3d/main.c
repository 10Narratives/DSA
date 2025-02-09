#include <stdio.h>

#include "dialog.h"
#include "utils.h"
#include "structs.h"
#include "views.h"
#include "models.h"

int main(){
	Table table = {0, 0, NULL};
	initTable(&table, getInt("ENTER TABLE SIZE --> "));
	const char *msgs[] = {"0. QUIT", "1. ADD", "2. PRINT", "3. FIND", "4. DELETE", "5. IMPORT"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Table *table) = {NULL, D_add, print, D_find, D_delete, D_import},
		rc = dialog(msgs, N);

	while(rc > 0){
		if(!fptr[rc](&table)) break;
		rc = dialog(msgs, N);
	}

	rebuild(&table);
	return 1;
}
