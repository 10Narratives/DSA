#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct Item{
	char* data;
	struct Item *next;
} Item;

typedef struct Stack{
	Item *head;
} Stack;

Stack* new();
void delete(Stack *stack);
int push(Stack *stack, char* data);
int pop(Stack *stack, char** data);
int len(const Stack *stack);

#endif
