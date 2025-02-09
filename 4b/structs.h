#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Node{
	int key, data, size;
	struct Node *right, *left, *parent;
} Node;

typedef struct Tree{
	Node *root;
} Tree;

Tree *initTree();
Node *getNode(int key, int data, Node *parent);

void deleteNode(Node *target);
void deleteAllNode(Node *target);
void deleteTree(Tree *target);

Node *findMaxNode(Node *sourse);
Node *findMinNode(Node *sourse);

#endif
