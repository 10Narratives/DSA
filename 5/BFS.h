#ifndef BFS_H
#define BFS_H
#include "structs.h"

int doBFS(Graph graph, char *name, int *indexes, int *count);
int doBellmanFord(Graph graph, char *main, char *companion, int *indexes, int *count);
int WFI(Graph graph, int *index);

#endif
