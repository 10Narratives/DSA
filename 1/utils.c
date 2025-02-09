#include <stdio.h>

void validate(int *value){
    while(scanf("%d", value) == 0){
        printf("Wrong input. Try again: ");
        scanf("%*[^\n]");
    }
}
