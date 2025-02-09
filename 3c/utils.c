#include <stdio.h>

int getInt(char *prompt){
	printf("%s", prompt);
	int res = 0;
	while(scanf("%d", &res) < 1){
		printf("WRONG INPUT. TRY AGAIN.\n");
		scanf("%*[^\n]");
	}
	return res;
}
