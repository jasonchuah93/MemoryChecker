#include <stdio.h>
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "ErrorCode.h"
#include "CException.h"

/*******************************************
    This function use handle the color
    of node in the RedBlackTree
*********************************************/

void handleColor(Node **rootPtr,Node *deleteNode){
	if((*rootPtr)->left->color == 'r' && (*rootPtr)->right->color == 'r'){
		(*rootPtr)->color ='r';
		(*rootPtr)->left->color ='b';
		(*rootPtr)->right->color ='b';
	}
}

/*********************************************************************
* This function will add a new record into the red black tree
*
*	Input: 	rootPtr			the root of the tree
*			newNode			the new member of the tree
			compare			pointer to a function to decide the rules to add record
*
*	Destroy: none
*	
**********************************************************************/

void genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*addRecordCompare)(Node **rootPtr,Node *newNode)){
    _genericAddRedBlackTree(rootPtr,newNode,addRecordCompare);    
    (*rootPtr)->color='b';
	if((*rootPtr)->left != NULL && (*rootPtr)->right != NULL)
		if((*rootPtr)->left->color == 'b' && (*rootPtr)->right->color == 'b')
			(*rootPtr)->color='r';
}

void _genericAddRedBlackTree(Node **rootPtr,Node *newNode, int(*compareRecord)(Node **rootPtr,Node *newNode)){
	int compare=0;
    if(*rootPtr == NULL){
		*rootPtr = newNode;
        (*rootPtr)->color='r';
		return;
    }
    
	if ((*rootPtr)->left!=NULL && (*rootPtr)->right!=NULL){
        handleColor(rootPtr,newNode);
	}
	
	compare = compareRecord(rootPtr,newNode);
    
	if(compare == 1){
		
        _genericAddRedBlackTree(&(*rootPtr)->left,newNode,compareRecord);
	}
    else if(compare == -1){
		
        _genericAddRedBlackTree(&(*rootPtr)->right,newNode,compareRecord);
	}
    else if(compare == 0){
		printf("2nd test");
		Throw(ERR_EQUIVALENT_RECORD);
	}
	
	if((*rootPtr)->left!=NULL){
		if((*rootPtr)->left->left !=NULL){
			if((*rootPtr)->left->color == 'r' && (*rootPtr)->left->left->color == 'r'){
				rightRotate(rootPtr);
				(*rootPtr)->right->color = 'r';
			}
		}else if((*rootPtr)->left->right !=NULL){
			if((*rootPtr)->left->color == 'r' && (*rootPtr)->left->right->color == 'r'){
				leftRightRotate(rootPtr);
				(*rootPtr)->right->color = 'r';
			}
		}
	}else if((*rootPtr)->right!=NULL){
		if((*rootPtr)->right->right != NULL){
			if((*rootPtr)->right->color == 'r' && (*rootPtr)->right->right->color == 'r'){
				leftRotate(rootPtr);
				(*rootPtr)->left->color = 'r';
			}
		}else if((*rootPtr)->right->left !=NULL){
			if((*rootPtr)->right->color == 'r' && (*rootPtr)->right->left->color == 'r'){
				rightLeftRotate(rootPtr);
				(*rootPtr)->left->color = 'r';
			}
		}
	}
	
	if((*rootPtr)->right !=NULL && (*rootPtr)->right->left !=NULL){
		if((*rootPtr)->right->color == 'r' && (*rootPtr)->right->left->color == 'r'){
			(*rootPtr)->right->left->color = 'b';
			(*rootPtr)->right->right->color = 'b';
		}
	}
}

/*********************************************************************
* This function will find record in the red black tree
*
*	Input: 	rootPtr			the root of the tree
*			targerMemory	the memory user want to look for in tree
			compare			pointer to a function to decide the rules to find record
*	
*	Output: targerRoot		the found record
*
*	Destroy: none
*	
**********************************************************************/
/*
Node *genericFindRedBlackTree(Node **rootPtr,void *targetMemory, int(*findRecordCompare)(Node **rootPtr,void *targetMemory)){
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
*/
/*********************************************************************
* This function will delete record in the red black tree
*
*	Input: 	rootPtr			the root of the tree
*			deleteNode		the record that will delete
			compare			pointer to a function to decide the rules to delete record
*	
*	Output: targerRoot		the deleted record
*
*	Destroy: none
*	
**********************************************************************/

Node *genericDelRedBlackTree(Node **rootPtr,char *targetMemory, int(*findAndRemoveRecordCompare)(Node **rootPtr,char *targetMemory)){
    Node *node = _genericDelRedBlackTree(rootPtr,targetMemory,findAndRemoveRecordCompare);
    if(*rootPtr!=NULL)
        (*rootPtr)->color='b';
    return node;
}

Node *_genericDelRedBlackTree(Node **rootPtr,char *targetMemory, int(*compareRecord)(Node **rootPtr,char *targetMemory)){
    int compare ; char tempColor; Node *targetMemoryRecord;
    ((Record*)((Node*)targetMemoryRecord)->data)->memoryAllocateAddr = targetMemory;
	Node *node , *tempRoot ,*tempLeftChild, *tempRightChild, *root = *rootPtr;
    compare = compareRecord(&root,targetMemory);
    if(compare == 0){
        if(rightChild){
            tempRoot = removeNextLargerSuccessor(&rightChild);
            tempLeftChild = leftChild ; tempRightChild = rightChild;
            tempColor = (*rootPtr)->color; 
            *rootPtr = tempRoot;
            leftChild=tempLeftChild; rightChild = tempRightChild;
            (*rootPtr)->color=tempColor;
            restructureRedBlackTree(rootPtr,targetMemoryRecord);
        }else if(leftChild){
            rightRotate(rootPtr);
            node = removeNextLargerSuccessor(&rightChild);
            (*rootPtr)->color = 'b';
        }else{
            *rootPtr=NULL;
			node = targetMemoryRecord;
        }
        return node;
    }else{
        if(leftChild == NULL && rightChild == NULL){
            Throw(ERR_NODE_UNAVAILABLE);
        }else if(compare == 1){
            node= _genericDelRedBlackTree(&leftChild,targetMemory,compareRecord);
        }else if(compare == -1){
            node= _genericDelRedBlackTree(&rightChild,targetMemory,compareRecord);
        }
    }
    restructureRedBlackTree(rootPtr,targetMemoryRecord);
    return node;
}

/*******************************************
    This function use to remove the most 
    left node in the RedBlackTree
*********************************************/
Node *removeNextLargerSuccessor(Node **rootPtr){
	Node *removeNode;
	
	if(leftChild !=NULL){
        removeNode = removeNextLargerSuccessor(&leftChild);
    }else if(rightChild == NULL){
		removeNode = *rootPtr;
        *rootPtr = NULL;
        return removeNode;
	}else if(rightChild->color == 'r'){
		removeNode = *rootPtr;
		*rootPtr = rightChild;
		(*rootPtr)->color = 'b';
        return removeNode;
	}
    restructureRedBlackTree(rootPtr,removeNode);
    return removeNode;
}

