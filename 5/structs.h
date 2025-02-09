#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Vertex{
	char *name;
	int arrSize;
	struct Edge *arr;
} Vertex;

typedef struct Edge{
	char level;
	Vertex *companion;
} Edge;

typedef struct Graph{
	int arrSize;
	Vertex *arr;
} Graph;

Graph initGraph();
Vertex initVertex(char *name);
Edge initEdge(int level, Vertex *companion);

int deleteEdgeBetween(Vertex *vet, int index);
int deleteVertex(Graph *graph, int index);
int deleteGraph(Graph *target);

int addVertex(Graph *graph, char *name);
int addEdgeBetween(Vertex *vet, Vertex *companion, int level);

int findVertex(Graph *graph, char *name, int *foundIndex);
int findEdgeBetween(Vertex *vert, Vertex *companion, int *foundIndex);

int changeName(Vertex *target, char *name);
int changeLevel(Edge *target, int level);

int printEdgeBetween(const Vertex vert, const Edge edge);
int printVertex(const Vertex vert);
int printGraph(Graph *target);

#endif
