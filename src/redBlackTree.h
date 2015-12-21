#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

//Make these define for easy programming
#define addRecord(rootPtr,newNode) genericAddRedBlackTree(rootPtr,newNode,addRecordCompare)
#define findRecord(rootPtr,targetMemory) genericFindRedBlackTree(rootPtr,targetMemory,findAndRemoveRecordCompare)
#define removeRecord(rootPtr,targetMemory) genericDelRedBlackTree(rootPtr,targetMemory,findAndRemoveRecordCompare)
#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addRecordCompare)(Node **rootPtr,Node *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Node *newNode));

Node *genericFindRedBlackTree(Node **rootPtr,char *targetMemory, int(*findAndRemoveRecordCompare)(Node **rootPtr,char *targetMemory));

Node *genericDelRedBlackTree(Node **rootPtr,char *targetMemory, int(*findAndRemoveRecordCompare)(Node **rootPtr,char *targetMemory));
Node *_genericDelRedBlackTree(Node **rootPtr,char *targetMemory, int(*compareRecord)(Node **rootPtr,char *targetMemory));

Node *removeNextLargerSuccessor(Node **rootPtr);


#endif // redBlackTree_H
