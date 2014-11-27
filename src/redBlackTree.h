#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"

void handleColor(Node **rootPtr,Node *deleteNode);
void addRedBlackTree(Node **rootPtr,Node *deleteNode);
void genericAddRedBlackTree(Node **rootPtr,void *addNode,int(*addDelRecordCompare)(void *target,void* fromRedBlackTree));
void _addRedBlackTree(Node **rootPtr,Node *addNode);

#endif // redBlackTree_H
