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

void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compare)(Node **rootPtr,Record *newNode)){
    Node *root = *rootPtr;
    int _compare;
    if(root == NULL){
        *rootPtr = newNode;
        return;
    }
    /*
    if (root->left!=NULL && root->right!=NULL){
        handleColor(rootPtr,newNode); 
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
    */
}

