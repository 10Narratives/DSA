#include <stdio.h>
#include "dialog.h"

#include "structs.h"

#include "views.h"
#include "timing.h"

int main(){
	const char *msgs[] = {"0. QUIT", "1. ADD", "2. PRINT", "3. FIND", "4. DELETE", "5. BYPASS", "6. SPECIAL FIND", "7. IMPORT", "8. TIMING"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Tree *) = {NULL, D_add, print, D_find, D_delete, D_bypass, D_spfind, D_import, D_timing},
		rc = dialog(msgs, N);

	Tree *tree = initTree();
	while(rc > 0){
		if(!fptr[rc](tree)) break;
		rc = dialog(msgs, N);
	}
	deleteTree(tree);
	return 1;
}
