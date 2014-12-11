#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

#define addMemory(rootPtr,addNode) genericAddRedBlackTree(rootPtr,addNode,addAndDelRecordCompare)
#define leftChild (rootPtr)->left
#define rightChild (rootPtr)->right
#define leftGrandChild (rootPtr)->left->left
#define rightGrandChild (rootPtr)->right->right
#define leftRightGrandChild (rootPtr)->left->right
#define rightLeftGrandChild (rootPtr)->right->left

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addAndDelRecordCompare)(void **rootPtr,void *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compare)(void **rootPtr,void *newNode));
  


#endif // redBlackTree_H
