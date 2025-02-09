#include "matrio.h"
#include "structs.h"
#include "matrio.h"
#include "alg.h"

int main(){
    //ввод матрицы
    Matr matrix = create_matr();
    //исполнение алгоритма
    int vector_len = 0, *vector = vector_counter(matrix, &vector_len);
    //вывод результата
    print_matr(matrix);
    print_vect(vector, vector_len);
    //удаление матрицы
    delete_matr(matrix);
    delete_vect(vector);
    return 0;
}
