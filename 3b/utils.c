#include <stdio.h>

int getInt(char *prompt){
	printf("%s\n", prompt);
	int res = 0;
	while(scanf("%d", &res) < 1){
		printf("WRONG VALUE. TRY AGAIN --> ");
		scanf("%*[^\n]");
	}
	return res;
}
