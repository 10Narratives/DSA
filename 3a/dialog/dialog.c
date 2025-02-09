#include <stdio.h>

int get_int(){
	int res = 0;
	while(scanf("%d", &res) == 0){
		printf("Illegal value. Try again: \n");
		scanf("%*[^\n]");
	}
	return res;
}

int dialog(const char *msgs[], int N){
	
	for(int i = 0; i < N; i++) printf("%s\n", msgs[i]);
	printf("Make choice --> ");
	int res = get_int();
	printf("\n");
	if(res == 0) return res;
	while(res < 0 || res >= N){
		printf("Wrong choice. Try again!\n");
		res = get_int();
	}
	return res;
}

