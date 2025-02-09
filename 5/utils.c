#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

int getInt(char *prompt){
	printf("%s\n", prompt);
	int res = 0;
	while(scanf("%d", &res) < 1){
		printf("WRONG VALUE. TRY AGAIN --> ");
		scanf("%*[^\n]");
	}
	return res;
}

Queue *queueInit() {
    Queue *queue = calloc(1, sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

int pushQueue(Queue *queue, char *name) {
    if(name) {
        Node *node = calloc(1, sizeof(Node));
        node->nameVertex = name;
        node->next = NULL;
        if(queue->tail) {
            queue->tail->next = node;
        } else {
            queue->head = node;
        }
        queue->tail = node;
    } else {
        return 1;
    }
    return 0;
}

int popQueue(Queue *queue, char **info) {
    
    Node *node = NULL;
    if(queue->head == NULL) {
        return 0;
    } 
    
    node = queue->head;
    *info = node->nameVertex;
    
    if (queue->head == queue->tail) {
        queue->tail = NULL;
    }
    
    queue->head = queue->head->next;
    
    free(node);
    return 1;
}

void deleteQueue(Queue *queue) {
    if(queue) {
        Node *node = queue->head;
        Node *delete = NULL;
        while (node) {
            delete = node;
            node = node->next;
            free(delete);
        }
        free(queue);
    }
}
