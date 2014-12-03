#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "MemoryRecord.h"

void handleColor(Node **rootPtr,Node *deleteNode);
void addRedBlackTree(Node **rootPtr,Node *addNode);
void _addRedBlackTree(Node **rootPtr,Node *addNode);
void genericAddRedBlackTree(Node **rootPtr,Node *addNode, int(*memoryCompare)(void *newNode,void **rootPtr));
void _genericAddRedBlackTree(Node **rootPtr,Node *addNode, int(*memoryCompare)(void *newNode,void **rootPtr));


#endif // redBlackTree_H
