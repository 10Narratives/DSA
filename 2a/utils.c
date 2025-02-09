#include <stdio.h>
#include <stdlib.h>

char *readstr(char *prompt){
	printf("%s", prompt);

	char* str = malloc(80 * sizeof(char));
	if(scanf(" %79[^\n]", str) < 1){
		free(str);
		return NULL;
	}

	str[79] = '\0';
	return str;
}
