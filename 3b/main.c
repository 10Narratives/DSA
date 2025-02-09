#include <stdio.h>
#include "dialog.h"
#include "utils.h"
#include "structs.h"
#include "views.h"
#include "models.h"

int main(){
	Table table = {0, 0, NULL};
	if(!initTable(&table, getInt("ENTER TABLE SIZE --> "), START_PROG))
		return 1;

	const char *msgs[] = {"0. QUIT", "1. ADD", "2. PRINT", "3. FIND", "4. DELETE", "5. IMPORT"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);

	int (*fptr[])(Table *) = {NULL, D_add, print, D_find, D_delete, D_import},
		rc = dialog(msgs, N);
	while(rc > 0){
		if(fptr[rc](&table) != SUCCESS) break;
		rc = dialog(msgs, N);
	}
	rebuild(&table);
	return 0;
}
