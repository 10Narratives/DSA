#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node{
	char *key, *data;
	struct Node *right, *left, *parent;
} Node;

typedef struct Tree{
	Node *root;
} Tree;

Tree *initTree();
Node *getNode(char *key, char *data, Node *parent);

void deleteNode(Node *target);
void deleteTree(Tree *target);

Node *findMaxNode(Node *sourse);
Node *findMinNode(Node *sourse);

#endif
