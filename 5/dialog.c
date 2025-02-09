#include <stdio.h>

#include "utils.h"

#define SPS 100

void printDivider(){
	for(int i = 0; i < SPS; i++)
		printf("-");
	printf("\n");	
}

void printWelcome(){
	for(int i = 0; i < (SPS - 8)/2; i++)
		printf("-");
	printf("WELCOME!");
	for(int i = 0; i < (SPS - 8)/2; i++)
		printf("-");
	printf("\n");
}

void printBye(){
	for(int i = 0; i < (SPS - 4)/2; i++)
		printf("-");
	printf("BYE!");
	for(int i = 0; i < (SPS - 4)/2; i++)
		printf("-");
	printf("\n");
}

int dialog(const char *msgs[], const int N){
	printDivider();
	for(int i = 0; i < N; i++)
		printf("%s\n", msgs[i]);
	int rc = getInt("ENTER YOUR CHOISE --> ");
	while(rc > N){
		printf("WRONG CHOISE. TRY AGAIN --> ");
		rc = getInt("ENTER YOUR CHOISE --> ");
	}
	printDivider();
	return rc;
}
