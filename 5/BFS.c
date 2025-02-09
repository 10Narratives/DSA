#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <limits.h>

#include "structs.h"

#define SUCCESS 1
#define FAILURE 0

int doBFS(Graph graph, char *name, int *indexes, int *count){   // Подается название человека, от которого пойдет поиск
    char* info = NULL;
    Graph visited = initGraph();   // Просмотренные вершины (для того, чтоб для них не писать таблицы и прочие структуры данных хранятся как граф)
    int index, indexVisited;
    
    if(!findVertex(&graph, name, &index)) {
        return FAILURE;
    }
    
    Queue *queue = queueInit();
    pushQueue(queue, graph.arr[index].name);
    addVertex(&visited, graph.arr[index].name); // вершина просмотрена
    
    while (popQueue(queue, &info)) {    // Пока очередь не опустеет
        findVertex(&graph, info, &index);  
        for (int i = 0; i < graph.arr[index].arrSize; i++) {
            if(graph.arr[index].arr[i].level > 0){  // Условие связи
                if(!findVertex(&visited, graph.arr[index].arr[i].companion->name, &indexVisited)) {  //если человека нет в просмотренных добавляется в очередь и просмотрен
                    pushQueue(queue, graph.arr[index].arr[i].companion->name);  
                    addVertex(&visited, graph.arr[index].arr[i].companion->name);
                    (*count)++;
                    indexes = realloc(indexes, *count*sizeof(int));
                    indexes[*count - 1] = indexVisited;
                }
            }
        }
    }
    
    deleteGraph(&visited);
    deleteQueue(queue);
    
    return SUCCESS;
}

int doBellmanFord(Graph graph, char *main, char *companion, int *indexes, int *count){
    
    if(!indexes) {
        free(indexes);
        indexes = NULL;
    }
    int *weights = calloc(graph.arrSize, sizeof(int)); // Массив с весами
    int *prev = calloc(graph.arrSize, sizeof(int)); // Массив предков (для восстановления пути)
    
    for (int i = 0; i < graph.arrSize; i++) {
        weights[i] = INT_MAX;
        prev[i] = -2;
    }
    
    int index;
    findVertex(&graph, main, &index);
    weights[index] = 0;
    
    for (int i = 0; i < graph.arrSize; i++) {
        for (int b = 0; b < graph.arrSize; b++) {
            if(weights[b] == INT_MAX) {
                continue;
            }
            for (int c = 0; c < graph.arr[b].arrSize; c++) {
                findVertex(&graph, graph.arr[b].arr[c].companion->name, &index);
                if(weights[index] == INT_MAX || weights[index] < weights[b] + graph.arr[b].arr[c].level) { // Если новый вес меньше - то берем его
                    weights[index] = weights[b] + graph.arr[b].arr[c].level;
                    prev[index] = b;
                }
            }
        }
    }
    
    findVertex(&graph, companion, &index);
    int finish = index;
    *count = 0;
    while (finish != -1 && weights[finish] != INT_MAX) {
        (*count)++;
        indexes = realloc(indexes, *count*sizeof(int));
        indexes[*count - 1] = finish;
        finish = prev[finish];
    }
    
    free(weights);
    free(prev);
    
    if(weights[index] == INT_MAX) {
        return FAILURE;
    }
    return SUCCESS;
}

int WFI(Graph graph, char *name, int *index) {
    int dist[graph.arrSize][graph.arrSize]; //матрица весов
    int ind1, ind2 = 0;
    
    int indexS;
    if(!findVertex(&graph, name, &indexS)) {
        return FAILURE;
    }
    // инициализируем матрицу: Если i = j => (i,j) = 0; Если есть путь от i -> j => (i, j) = вес; Если нет пути (i,j) = INT_MIN
    for (int i = 0; i < graph.arrSize; i++) {
        for (int b = 0; b < graph.arrSize; b++) {
            if(findEdgeBetween(&graph.arr[i], &graph.arr[b], &ind1)){
                dist[i][b] = graph.arr[i].arr[ind1].level;
            } else {
                if(i == b) {
                    dist[i][b] = 0;
                } else {
                    dist[i][b] = INT_MIN;
                }
            }
        }
    }
    // Если возьмем и проведем путь через k, и если он больше - берем его вес
    for (int k = 0; k < graph.arrSize; k++) {
        for (int i = 0; i < graph.arrSize; i++) {
            for (int b = 0; b < graph.arrSize; b++) {
                if(findEdgeBetween(&graph.arr[i], &graph.arr[k], &ind1) && findEdgeBetween(&graph.arr[k], &graph.arr[b], &ind2)) {
                    if(dist[i][b] < graph.arr[i].arr[ind1].level + graph.arr[k].arr[ind2].level) {
                        dist[i][b] = graph.arr[i].arr[ind1].level + graph.arr[k].arr[ind2].level;
                    }
                    
                }
            }
        }
    }
    
    int max = INT_MIN;
    int flag = graph.arrSize;
    
    for (int i = 0; i < graph.arrSize; i++) {
        if(dist[indexS][i] != INT_MIN) {
            flag--;
            if(dist[indexS][i] > max) {
                max = dist[indexS][i];
                *index = i;
            }
        }
    }
    if(flag == graph.arrSize) {
        return FAILURE;
    }
    
    return SUCCESS;
}
