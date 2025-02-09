#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Stack* new(){
	return (Stack *) calloc(1, sizeof(Stack));	
}

void delete(Stack *stack){
	Item *ptr = stack->head, *ptr_prev = NULL;

	while(ptr){
		ptr_prev = ptr;
		ptr = ptr->next;
		free(ptr_prev->data);
		free(ptr_prev);
	}

	free(stack);	
}

int push(Stack *stack, char* data){
	Item *new = malloc(sizeof(Item));
	if(!new) return 1;

	new->data =data;
	new->next = stack->head;
	stack->head = new;
	return 0;
}

int pop(Stack *stack, char** data){
	if(!stack->head) return 1;

	*data = stack->head->data;
	Item *head = stack->head;
	stack->head = head->next;
	free(head);
	return 0;	
}

int len(const Stack *stack){
	Item *ptr = stack->head;
	int counter = 0;
	while(ptr){
		ptr = ptr->next;
		counter++;
	}
	return counter;
}
