#include <stdio.h>
#include <stdlib.h>
#include "../structs.h"

char *readstr(char *prompt){
	printf("%s", prompt);

	char *str = malloc(80); 
	if(scanf(" %79[^\n]", str) < 1){
		free(str);
		return NULL;
	}

	str[79] = '\0';
	return str;
}
