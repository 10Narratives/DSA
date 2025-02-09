#ifndef VIEWS_H
#define VIEWS_H
#include "structs.h"

int D_add(Graph *);
int D_find(Graph *);
int D_delete(Graph *);
int D_change(Graph *);

int D_addVertex(Graph *);
int D_addEdge(Graph *);

int D_findVertex(Graph *);
int D_findEdge(Graph *);

int D_deleteVertex(Graph *);
int D_deleteEdge(Graph *);

int D_changeVertex(Graph *);
int D_changeEdge(Graph *);

int D_DFS(Graph *graph);
int D_BellmanFord(Graph *graph);
int D_WFI(Graph *graph);


#endif
