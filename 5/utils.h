#ifndef UTILS_H
#define UTILS_H

typedef struct Node {
    char *nameVertex;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;



int getInt(char *prompt);

Queue *queueInit();
int pushQueue(Queue *queue, char *name);
int popQueue(Queue *queue, char **info);
void deleteQueue(Queue *queue);

#endif
