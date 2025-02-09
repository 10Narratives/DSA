#ifndef VECTOR_H
#define VECTOR_H

typedef struct Item{
	char* data;
} Item;

typedef struct Stack{
	int vec_size;
	Item *array_of_items;
} Stack;

Stack* new();
void delete(Stack *stack);
int push(Stack *stack, char* data);
int pop(Stack *stack, char** data);
void print(const Stack *stack);
int len(const Stack *stack);

#endif
