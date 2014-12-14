#include <stdio.h>
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "ErrorCode.h"
#include "CException.h"

void handleColor(Node **rootPtr,Node *deleteNode){
  Node *root = *rootPtr;
  if(root->left->color == 'r' && root->right->color == 'r'){
        root->left->color ='b';
        root->right->color ='b';
        root->color ='r';
      }
}

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addAndDelRecordCompare)(Node **rootPtr,Record *newNode)){
    _genericAddRedBlackTree(rootPtr,newNode,addAndDelRecordCompare);    
    (*rootPtr)->color='b';
}

void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Record *newNode)){
    Node *root = *rootPtr;
    int compare=0;
    if(root == NULL){
        *rootPtr = newNode;
        return;
    }
    if (root->left!=NULL && root->right!=NULL){
        handleColor(rootPtr,newNode); 
    }
    compare = compareRecord(&root,(Record*)newNode);
    if(compare == 1){
        _genericAddRedBlackTree(&root->left,newNode,compareRecord);
    }else if(compare == -1){
        _genericAddRedBlackTree(&root->right,newNode,compareRecord);
    }else if(compare == 0){
        Throw(ERR_EQUIVALENT_MEMORY);
    }

    if(root->left!=NULL && root->right==NULL){
        if(root->left->left !=NULL){
            if(root->left->color == 'r' && root->left->left->color == 'r'){
                rightRotate(rootPtr);
            }
        }else if(root->left->right !=NULL){
            if(root->left->color == 'r' && root->left->right->color == 'r'){
                leftRightRotate(rootPtr);
            }
        }
    }else if(root->left==NULL && root->right!=NULL){
        if(root->right->right !=NULL){
            if(root->right->color == 'r' && root->right->right->color == 'r'){
                leftRotate(rootPtr);
            }
        }else if(root->right->left !=NULL){
            if(root->right->color == 'r' && root->right->left->color == 'r'){
                rightLeftRotate(rootPtr);
            }
        }
    }
}


Node *genericFindRedBlackTree(Node **rootPtr,Node *targetMemory, int(*findRecordCompare)(Node **rootPtr,void *targetMemory)){
    int compare ;
    Node *root = *rootPtr;
    Node *targetRoot=NULL;
    
    compare = findRecordCompare(rootPtr,(void*)targetMemory);
    if(compare == 0){
        targetRoot = *rootPtr;
    }
    else if(compare == 1){
        targetRoot = genericFindRedBlackTree(&root->left,(void*)targetMemory,findRecordCompare);
    }else if(compare == -1){
        targetRoot = genericFindRedBlackTree(&root->right,(void*)targetMemory,findRecordCompare);
    }
    
    return targetRoot;
    
}

Node *genericDelRedBlackTree(Node **rootPtr,Node *deleteNode, int(*addAndDelRecordCompare)(Node **rootPtr,Record *deleteNode)){
    Node *node = _genericDelRedBlackTree(rootPtr,deleteNode,addAndDelRecordCompare);
    if(*rootPtr!=NULL)
        (*rootPtr)->color='b';
  return node;
}

Node *_genericDelRedBlackTree(Node **rootPtr,Node *deleteNode, int(*compareRecord)(Node **rootPtr,Record *newNode)){
    int compare ; char tempColor;
    Node *node , *tempRoot ,*tempLeftChild, *tempRightChild, *root = *rootPtr;
    if(root==deleteNode){
        *rootPtr = NULL;
    }else{
        if(leftChild == NULL && rightChild == NULL){
                Throw(ERR_NODE_UNAVAILABLE);
        }
    }
    
    return node;
}