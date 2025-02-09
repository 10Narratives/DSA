#include <stdio.h>
#include "readline/readline.h"
#include <stdlib.h>
#include "BFS.h"

#include "structs.h"
#include "utils.h"
#include "dialog.h"

#define SUCCESS 1
#define FAILURE 0


int D_addVertex(Graph *graph){
	char *name = readline("ENTER NEW NAME --> ");
	if(!name)
		return FAILURE;
	printf("\n");	
	int foundIndex = -1;
	if(!findVertex(graph, name, &foundIndex)){
		addVertex(graph, name);
		printf("SUCCESS ADD!\n\n");		
	} else{
		printf("VERTEX ALREADY EXISTS\n");
		free(name);
	}
	return SUCCESS;
}

int D_addEdge(Graph *graph){
	char *mainName = readline("ENTER MAIN NAME --> ");
	if(!mainName)
		return FAILURE;

	int foundMainIndex = -1;
	if(!findVertex(graph, mainName, &foundMainIndex)){
		printf("MAIN VERTEX WAS NOT BEEN FOUND\n");	
		free(mainName);
		return SUCCESS;
	}

	char *companionName = readline("ENTER COMPANION NAME --> ");
	if(!companionName){
		free(mainName);
		return FAILURE;		
	}

	int foundCompanionIndex = -1;
	if(!findVertex(graph, companionName, &foundCompanionIndex)){
		printf("COMPANION VERTEX WAS NOT BEEN FOUND\n");
		free(mainName);
		free(companionName);
		return SUCCESS;
	}
	free(mainName);
	free(companionName);
	int foundIndex = -1;
	if(findEdgeBetween(&graph->arr[foundMainIndex], &graph->arr[foundCompanionIndex], &foundIndex)){
		printf("EDGE ALREADY EXIST. DELETE IT BEFORE ADD\n");
		return SUCCESS;
	} else{
		int level = getInt("ENTER LEVEL --> ");
		addEdgeBetween(&graph->arr[foundMainIndex], &graph->arr[foundCompanionIndex], level);
		return SUCCESS;
	}
}

int D_add(Graph *graph){
	const char *msgs[] = {"\t0. NOT DO",  "\t1. VERTEX", "\t2. EDGE"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int rc = dialog(msgs, N),
		(*fptr[])(Graph *) = {NULL, D_addVertex, D_addEdge};

	while(rc > 0){
		if(!fptr[rc](graph)) break;
		rc -= 100;	
	}
	
	return SUCCESS;
}

int D_findVertex(Graph *graph){
	char *name = readline("ENTER FIND NAME --> ");
	if(!name)
		return FAILURE;
	printf("\n");	
	int foundIndex = -1;
	if(findVertex(graph, name, &foundIndex)){
		printf("SUCCESS FIND!\n");
		printVertex(graph->arr[foundIndex]);
		printf("\n");	
	} else
		printf("NOTHING WAS BEEN FOUND\n");
	free(name);
	return SUCCESS;
}

int D_findEdge(Graph *graph){
	char *mainName = readline("ENTER MAIN NAME --> ");
	if(!mainName)
		return FAILURE;
	int foundMainIndex = -1;
	if(!findVertex(graph, mainName, &foundMainIndex)){
		printf("MAIN VERTEX WAS NOT BEEN FOUND\n");	
		return SUCCESS;
	}
	char *companionName = readline("ENTER COMPANION NAME --> ");
	if(!companionName)
		return FAILURE;
	int foundCompanionIndex = -1;
	if(!findVertex(graph, companionName, &foundCompanionIndex)){
		printf("COMPANION VERTEX WAS NOT BEEN FOUND\n");
		return SUCCESS;
	}
	free(mainName);
	free(companionName);
	int foundIndex = -1;
	if(findEdgeBetween(&graph->arr[foundMainIndex], &graph->arr[foundCompanionIndex], &foundIndex)){
		printf("SUCCESS FIND!\n");
		printEdgeBetween(graph->arr[foundMainIndex], graph->arr[foundMainIndex].arr[foundIndex]);		
		return SUCCESS;
	} else{
		printf("NOTHING WAS BEEN FOUND\n");	
	}
    return 1;
}

int D_find(Graph *graph){
	const char *msgs[] = {"\t0. NOT DO",  "\t1. VERTEX", "\t2. EDGE"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int rc = dialog(msgs, N),
		(*fptr[])(Graph *) = {NULL, D_findVertex, D_findEdge};
	while(rc > 0){
		if(!fptr[rc](graph)) break;
		rc -= 100;	
	}
	return SUCCESS;
}


int D_deleteVertex(Graph *graph){
	char *name = readline("ENTER FIND NAME --> ");
	if(!name)
		return FAILURE;
	printf("\n");	
	int foundIndex = -1;
	if(findVertex(graph, name, &foundIndex)){
		printf("SUCCESS DELETE!\n");
		deleteVertex(graph, foundIndex);
		printf("\n");	
	} else
		printf("NOTHING WAS BEEN FOUND FOR DELETE\n");
	free(name);
	return SUCCESS;	
}

int D_deleteEdge(Graph *graph){
	char *mainName = readline("ENTER MAIN NAME --> ");
	if(!mainName)
		return FAILURE;
	int foundMainIndex = -1;
	if(!findVertex(graph, mainName, &foundMainIndex)){
		printf("MAIN VERTEX WAS NOT BEEN FOUND\n");	
		return SUCCESS;
	}
	char *companionName = readline("ENTER COMPANION NAME --> ");
	if(!companionName)
		return FAILURE;
	int foundCompanionIndex = -1;
	if(!findVertex(graph, companionName, &foundCompanionIndex)){
		printf("COMPANION VERTEX WAS NOT BEEN FOUND\n");
		return SUCCESS;
	}
	free(mainName);
	free(companionName);
	int foundIndex = -1;
	if(findEdgeBetween(&graph->arr[foundMainIndex], &graph->arr[foundCompanionIndex], &foundIndex)){
		printf("SUCCESS DELETE!\n");
		deleteEdgeBetween(&graph->arr[foundMainIndex], foundIndex);
		return SUCCESS;
	} else{
			printf("NOTHING WAS BEEN FOUND FOR DELETE\n");
			return SUCCESS;
	}
}

int D_delete(Graph *graph){
	const char *msgs[] = {"\t0. NOT DO",  "\t1. VERTEX", "\t2. EDGE"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int rc = dialog(msgs, N),
		(*fptr[])(Graph *) = {NULL, D_deleteVertex, D_deleteEdge};
	while(rc > 0){
		if(!fptr[rc](graph)) break;
		rc -= 100;	
	}
	return SUCCESS;
}

int D_changeVertex(Graph *graph){
	char *name = readline("ENTER CHANGE NAME --> ");
	if(!name)
		return FAILURE;
	printf("\n");	
	int foundIndex = -1;
	if(findVertex(graph, name, &foundIndex)){
		char *newName = readline("ENTER CHANGE NAME --> ");
		if(!newName)
			return FAILURE;		
		free(&graph->arr[foundIndex].name);
		changeName(&graph->arr[foundIndex], newName);
		printf("SUCCESS CHANGE!\n\n");
	} else
		printf("NOTHING WAS BEEN FOUND FOR DELETE\n");
	free(name);
	return SUCCESS;	
}

int D_changeEdge(Graph *graph){
	char *mainName = readline("ENTER MAIN NAME --> ");
	if(!mainName)
		return FAILURE;
	int foundMainIndex = -1;
	if(!findVertex(graph, mainName, &foundMainIndex)){
		printf("MAIN VERTEX WAS NOT BEEN FOUND\n");	
		return SUCCESS;
	}
	char *companionName = readline("ENTER COMPANION NAME --> ");
	if(!companionName)
		return FAILURE;
	int foundCompanionIndex = -1;
	if(!findVertex(graph, companionName, &foundCompanionIndex)){
		printf("COMPANION VERTEX WAS NOT BEEN FOUND\n");
		return SUCCESS;
	}
	free(mainName);
	free(companionName);
	int foundIndex = -1;
	if(findEdgeBetween(&graph->arr[foundMainIndex], &graph->arr[foundCompanionIndex], &foundIndex)){
		int newLevel = getInt("ENTER NEW LEVEL --> ");
		changeLevel(&graph->arr[foundMainIndex].arr[foundIndex], newLevel);
		printf("SUCCESS CHANGE!\n\n");
		return SUCCESS;
	} else{
		printf("NOTHING WAS BEEN FOUND FOR DELETE\n");
		return SUCCESS;	
	}
}

int D_change(Graph *graph){
	const char *msgs[] = {"\t0. NOT DO",  "\t1. VERTEX", "\t2. EDGE"};
	const int N = sizeof(msgs) / sizeof(msgs[0]);
	int rc = dialog(msgs, N),
		(*fptr[])(Graph *) = {NULL, D_changeVertex, D_changeEdge};
	while(rc > 0){
		if(!fptr[rc](graph)) break;
		rc -= 100;	
	}
	return SUCCESS;
}

int D_DFS(Graph *graph){
    int *ind = NULL;
    int count = 0;
    doBFS(*graph, "v", ind, &count);
    return SUCCESS;
}

int D_BellmanFord(Graph *graph){
    int *ind = NULL;
    int count = 0;
    doBellmanFord(*graph, "v", "l", ind, &count);
    return SUCCESS;
}

int D_WFI(Graph *graph){
    int index = 0;
    WFI(*graph, &index);
    return SUCCESS;
}
