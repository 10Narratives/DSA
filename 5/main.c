#include <stdio.h>
#include <stdlib.h>

#include "dialog.h"
#include "structs.h"
#include "views.h"
#include "BFS.h"

int main(){
    //printWelcome();
    const char *msgs[] = {"0. QUIT", "1. ADD", "2. DELETE", "3. FIND", "4. PRINT GRAPH", "5. CHANGE", "6. DO BFS", "7. BELLMAN FORD", "8. WFI"};
    const int N = sizeof(msgs) / sizeof(msgs[0]);

    Graph graph = initGraph();

    int (*fptr[])(Graph *) = {NULL, D_add, D_find, D_delete, printGraph, D_change, D_DFS, D_BellmanFord, D_WFI};

    int rc = dialog(msgs, N);
    while(rc > 0){
        if(!fptr[rc](&graph)) break;
        rc = dialog(msgs, N);
    }

    deleteGraph(&graph);
    //printBye();
    return 0;
}
