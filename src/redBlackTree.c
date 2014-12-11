#include <stdio.h>
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "ErrorCode.h"
#include "CException.h"

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addAndDelRecordCompare)(void **rootPtr,void *newNode)){
    _genericAddRedBlackTree(rootPtr,newNode,addAndDelRecordCompare);    
    (*rootPtr)->color='b';
}

void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compare)(void **rootPtr,void *newNode)){
    Node *root = *rootPtr;
    int _compare;
    if(root == NULL){
        *rootPtr = newNode;
        return;
    }    
    _compare = compare((void*)rootPtr,newNode);
    if(_compare == 1){
        _genericAddRedBlackTree(&root->left,newNode,compare);
    }else if(_compare == -1){
        _genericAddRedBlackTree(&root->right,newNode,compare);
    }else if(_compare == 0){
        Throw(ERR_EQUIVALENT_MEMORY);
    }
    if(root->left!=NULL && root->right==NULL){
        if(root->left->left !=NULL){
            rightRotate(rootPtr);
        }else if(root->left->right !=NULL){
            leftRightRotate(rootPtr);
        }
    }else if(root->left==NULL && root->right!=NULL){
        if(root->right->right !=NULL){
            leftRotate(rootPtr);
        }else if(root->right->left !=NULL){
            rightLeftRotate(rootPtr);
        }
    }
}

