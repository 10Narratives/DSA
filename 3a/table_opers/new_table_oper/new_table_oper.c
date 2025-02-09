#include <stdio.h>
#include <stdlib.h>
#include "../../structs.h"

void validate(int *val){
	while(scanf("%d", val) == 0){
         printf("Wrong value. Try again!\nEnter: ");
         scanf("%*[^\n]");
     }
}

Table init_start_table(){
	int t_s = 0;
	printf("Enter table size\n");
	validate(&t_s);

	while(t_s < 1){
		printf("Wrong table size. It must be more than 0. Try again!");
        validate(&t_s);
     }

    Table n_table = {calloc(t_s, sizeof(KeySpace)), t_s, 0, NULL, NULL, NULL, NULL};
    return n_table;
}

Table init_empty_table(int max_size){
	Table emp_table = {calloc(max_size, sizeof(KeySpace)), max_size, 0, NULL, NULL, NULL, NULL};
	return emp_table;
}
