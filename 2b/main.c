#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "utils.h"

int main(){
	char *str = readstr("Enter string: ");
	while(str){
		printf("Entered string: %s\n", str);
		general(str);
		free(str);
		str = readstr("Enter string: ");
	}
	printf("\n");
	return 0;
}
