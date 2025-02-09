#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Stack* new(){
	Stack *new_s = calloc(1, sizeof(Stack));
	return new_s;
}

void delete(Stack *stack){
	for (int i = 0; i < stack->vec_size; i++) {
		free(stack->array_of_items[i].data);
	}
	free(stack->array_of_items);
	free(stack);
}

int push(Stack *stack, char *data){
	Item new = {data};
	stack->vec_size++;
	stack->array_of_items = realloc(stack->array_of_items, stack->vec_size * sizeof(Item));
	for(int i = stack->vec_size - 1; i > 0; i--){
		stack->array_of_items[i] = stack->array_of_items[i - 1];
	}
	stack->array_of_items[0] = new;
	return 0;
}

int pop(Stack *stack, char **data){
	if (stack->vec_size == 0) return 1;
	*data = stack->array_of_items[0].data;
	for(int i = 0; i < stack->vec_size - 1; i++){
		stack->array_of_items[i] = stack->array_of_items[i + 1];
	}
	stack->vec_size--;
	stack->array_of_items = realloc(stack->array_of_items, stack->vec_size * sizeof(Item));
	return 0;
}

void print(const Stack *stack){
	for(int i = 0; i < stack->vec_size; i++){
		printf("%s ", stack->array_of_items[i].data);
	}
	printf("\n");
}

int len(const Stack *stack){
	return stack->vec_size;
}
