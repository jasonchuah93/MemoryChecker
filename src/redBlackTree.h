#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"

#define addRedBlackTree(rooPtr,addNode) \
	genericAddBlackTree(rootPtr,addNode,addDelRecordCompare);

void handleColor(Node **rootPtr,Node *deleteNode);
void genericAddRedBlackTree(Node **rootPtr,void *addNode,int(*priorityCompare)(void *target,void *fromRedBlackTree));
void _addRedBlackTree(Node **rootPtr,Node *addNode);

#endif // redBlackTree_H
