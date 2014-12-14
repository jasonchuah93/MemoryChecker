#ifndef redBlackTree_H
#define redBlackTree_H

#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

#define addRecord(rootPtr,newNode) genericAddRedBlackTree(rootPtr,newNode,addAndDelRecordCompare)
#define findRecord(rootPtr,targetMemory) genericFindRedBlackTree(rootPtr,targetMemory,findRecordCompare)
#define deleteRecord(rootPtr,deleteNode) genericDelRedBlackTree(rootPtr,deleteNode,addAndDelRecordCompare)
#define leftChild (*rootPtr)->left
#define rightChild (*rootPtr)->right
#define leftGrandChild (*rootPtr)->left->left
#define rightGrandChild (*rootPtr)->right->right
#define leftRightGrandChild (*rootPtr)->left->right
#define rightLeftGrandChild (*rootPtr)->right->left

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addAndDelRecordCompare)(Node **rootPtr,Record *newNode));
void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Record *newNode));
Node *genericFindRedBlackTree(Node **rootPtr,Node *targetMemory, int(*findRecordCompare)(Node **rootPtr,void *targetMemory));
Node *genericDelRedBlackTree(Node **rootPtr,Node *deleteNode, int(*addAndDelRecordCompare)(Node **rootPtr,Record *newNode));  
Node *_genericDelRedBlackTree(Node **rootPtr,Node *deleteNode, int(*compareRecord)(Node **rootPtr,Record *newNode));
Node *removeNextLargerSuccessor(Node **rootPtr);

#endif // redBlackTree_H
