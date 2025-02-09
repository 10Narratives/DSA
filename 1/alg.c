#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int figures_counter(int num){
    int result = 0;
    int num_mod = (num > 0) ? num : (-1)*num;
    while(num_mod > 0){
        result += num_mod%10;
        num_mod /= 10;
    }
    return result;
}

int line_counter(Line line){
    int first_summ = figures_counter(line.array_in_line[0]), result = 0;
    for(int i = 0; i < line.line_size; i++){
        if(first_summ == figures_counter(line.array_in_line[i])) result += line.array_in_line[i]; 
    }
    return result;
}

int *vector_counter(Matr matrix, int *vector_len){
    int *local_vector = calloc(0, sizeof(int));
    for(int i = 0; i < matrix.matrix_size; i++){
        (*vector_len)++;
        local_vector = realloc(local_vector, (*vector_len) * sizeof(int));
        local_vector[i] = line_counter(matrix.array_of_lines[i]);
    }
    return local_vector;
}

void print_vect(int *vector, int vector_len){
    for(int i = 0; i < vector_len; i++){
        printf("%d element in vector is %d\n", i, vector[i]);
    }
}

void delete_vect(int *vector){
    free(vector);
}
