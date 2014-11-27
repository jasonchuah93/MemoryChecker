#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
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
void genericAddRedBlackTree(Node **rootPtr,void *addNode,int(*priorityCompare)(void *target,void* fromRedBlackTree)){
	
}

void _addRedBlackTree(Node **rootPtr,Node *addNode){
  Node *root = *rootPtr;
  if(root == NULL){
	*rootPtr = addNode;
    return;
  }
  if (root->left!=NULL && root->right!=NULL){
    handleColor(rootPtr,addNode); 
  }
  if(root->data > addNode->data){
	_addRedBlackTree(&root->left,addNode);
  }else if(root->data < addNode->data){
	_addRedBlackTree(&root->right,addNode);
  }else{
	Throw(ERR_EQUIVALENT_NODE);
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

Node *genericDelRedBlackTree(Node *record,Record *recordCompare){

}