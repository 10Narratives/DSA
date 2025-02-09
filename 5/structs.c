#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

#define SUCCESS 1
#define FAILURE 0

Graph initGraph(){
	int arrSize = 0;
	Vertex *arr = calloc(arrSize, sizeof(Vertex));
	Graph newGraph = {arrSize, arr};
	return newGraph;	
}

Vertex initVertex(char *name){
	int arrSize = 0;
	Edge *arr = calloc(arrSize, sizeof(Edge));
	Vertex newVertex = {name, arrSize, arr};
	return newVertex;	
}

Edge initEdge(int level, Vertex *companion){
	Edge newEdge = {level, companion};
	return newEdge;
}

int deleteEdgeBetween(Vertex *vert, int index){
	vert->arr[index].companion = NULL;

	vert->arrSize--;
	Edge *newArr = calloc(vert->arrSize, sizeof(Edge));
	for(int i = 0, j = 0; i < vert->arrSize - 1; i++){
		if(i != index){
			newArr[i] = vert->arr[j];
			j++;
		}
	}
	
	free(vert->arr);
	vert->arr = newArr;
	return SUCCESS;
}

int deleteVertex(Graph *graph, int index){
	for(int i = 0; i < graph->arr[index].arrSize; i++){
		deleteEdgeBetween(&graph->arr[index], i);
	}
	free(graph->arr[index].arr);
	free(graph->arr[index].name);
	return SUCCESS;
}

int deleteGraph(Graph *target){
	for(int i = 0; i < target->arrSize; i++)
		deleteVertex(target, i);
	free(target->arr);
	return SUCCESS;
}

int addVertex(Graph *graph, char *name){
	graph->arrSize++;
	graph->arr = realloc(graph->arr, graph->arrSize * sizeof(Vertex));
	graph->arr[graph->arrSize - 1] = initVertex(name);
	return SUCCESS;
}

int addEdgeBetween(Vertex *vert, Vertex *companion, int level){
	vert->arrSize++;
	vert->arr = realloc(vert->arr, vert->arrSize * sizeof(Edge));
	vert->arr[vert->arrSize - 1] = initEdge(level, companion);
	return SUCCESS;
}

int findVertex(Graph *target, char *name, int *foundIndex){
	if(!target->arr)
		return FAILURE;
	for(int i = 0; i < target->arrSize; i++){
		if(strcmp(target->arr[i].name, name) == 0){
			*foundIndex = i;
			return SUCCESS;
		}  
	}
	return FAILURE;
}

int findEdgeBetween(Vertex *vert, Vertex *companion, int *foundIndex){
	if(!vert->arr)
		return FAILURE;
	for(int i = 0; i < vert->arrSize; i++){
		if(vert->arr[i].companion == companion){
			*foundIndex = i;
			return SUCCESS;
		}
	}
	return FAILURE;
}

int changeName(Vertex *target, char *name){
	target->name = name;
	return SUCCESS;
}

int changeLevel(Edge *target, int level){
	target->level = level;
	return SUCCESS;
}

int printEdgeBetween(const Vertex vert, const Edge edge){
	printf("{%s ]-(%d)-[ %s} ", vert.name, edge.level, edge.companion->name);
	return SUCCESS;
}

int printVertex(const Vertex vert){
	printf("%s: ", vert.name);
	for(int i = 0; i < vert.arrSize; i++)
		printEdgeBetween(vert, vert.arr[i]);
	printf("\n");
    return 0;
}

int printGraph(Graph *target){
	for(int i = 0; i < target->arrSize; i++)
		printVertex(target->arr[i]);
	return SUCCESS; 
}
