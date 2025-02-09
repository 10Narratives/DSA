#include <stdio.h>
#include "utils.h"
#include "structs.h"
#include "views.h"
#include "dialog.h"


int main(){
	const char *msgs[] = {"1. ADD", "2. IMPORT", "3. PRINT", "4. FIND", "5. DELETE","0. QUIT"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Table *) = {NULL, D_add, D_import, print, D_find, D_delete}; // массив функий

	Table table = initTable(getInt("ENTER TABLE SIZE --> ")); // getInt(char *prompt) - функция, обрабатывающая ввод числа
	int rc = dialog(msgs, N); // dialog(char *msgs, int N) - функция, выводящая в поток вывода варианты работы с программой
	while(rc > 0){
		if(fptr[rc](&table) != SUCCESS) break;
		rc = dialog(msgs, N);
	}
	deleteTable(&table);
	return 1;
}
