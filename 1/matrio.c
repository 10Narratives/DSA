#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"

Line input_line(int i_line){
    printf("Enter the size of %d line: ", i_line);
    int line_size = 0;
    validate(&line_size);

    Line local_line = {line_size, calloc(line_size, sizeof(int))};
    for(int i = 0; i < line_size; i++){
        printf("Enter the value of %d element in %d line: ", i, i_line);
        validate(&local_line.array_in_line[i]);
    }

    return local_line;
}

Matr create_matr(){
    int matrix_size = 0;
    printf("Enter matrix size: ");
    validate(&matrix_size);

    Matr local_matrix = {matrix_size, calloc(matrix_size, sizeof(Line))};
    for(int i = 0; i < matrix_size; i++){
        local_matrix.array_of_lines[i] = input_line(i);
    }

    return local_matrix;
}

void print_matr(Matr matrix){
    for(int i = 0; i < matrix.matrix_size;i++){
        for(int j = 0; j < matrix.array_of_lines[i].line_size; j++){
            printf("%d ", matrix.array_of_lines[i].array_in_line[j]);
        }
        printf("\n");
    }
}

void delete_matr(Matr matrix){
    for(int i = 0; i < matrix.matrix_size;i++){
        free(matrix.array_of_lines[i].array_in_line);
    }
    free(matrix.array_of_lines);
}
