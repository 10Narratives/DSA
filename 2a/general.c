#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int is_oper(char *word){
	if(strcmp(word, "+") == 0 || strcmp(word, "-") == 0 || strcmp(word, "*") == 0 || strcmp(word, "/") == 0){
		return 1;
	}
	return 0;
}

int is_oper_in(char *word){
	if(strchr(word, '+') != NULL || strchr(word, '-') != NULL || strchr(word, '*') != NULL || strchr(word, '/') != NULL){
		return 1;
	}
	return 0;
}


void concat(char **s1, const char *s2){
    const size_t len1 = strlen(*s1);
    const size_t len2 = strlen(s2);
    *s1 = realloc(*s1, len1 + len2 + 1);
    strcat(*s1, s2);
}


int connect(Stack *st, char *word){
	if(len(st) <= 1){
		printf("Error. Illegel string!\n");
		return 1;
	}
	char* first = NULL, *second = NULL;
	pop(st, &second);
	pop(st, &first);
	char *res = calloc(1, sizeof(char));
	concat(&res, "(");
	concat(&res, first);
	free(first);
	concat(&res, " ");
	concat(&res, word);
	concat(&res, " ");
	concat(&res, second);
	free(second);
	concat(&res, ")");
	push(st, res);
	return 0;
}

int general(char *str){
	char *word = strtok(str, " "); Stack *st = new();
	while(word != NULL){
		int word_len = strlen(word);
		if(word_len > 0){
			if(!is_oper(word)){
				if(!is_oper_in(word)){
					push(st, strdup(word));
				} else{
					printf("Error. Illegal word: %s\n", word);
					delete(st);
					return 1;

				}
			} else {
				if(connect(st, word) == 1){
					delete(st);
					return 1;	
				}
			}
		}
		word = strtok(NULL, " ");
	}
	if(len(st) > 1){
		printf("Error. Illegel string!\n");
	} else{
		char *res = NULL; pop(st, &res); printf("Result: %s\n", res);
		if (res != str) free(res);
	}
	delete(st);
	return 0;
}
