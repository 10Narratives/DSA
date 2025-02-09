#ifndef ALG_H
#define ALG_H
#include "structs.h"

int figures_counter(int num);
int line_counter(Line line);
int *vector_counter(Matr matrix, int *vector_len);
void print_vect(int *vector, int vector_len);
void delete_vect(int *vector);

#endif
