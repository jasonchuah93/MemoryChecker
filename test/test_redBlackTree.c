#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node mainNode,leftNode,rightNode,leftNodeChild,rightNodeChild;

void setUp(void){}

void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*	root		    root
*	 |    add record     |
*	 v    ----------->   v
*	NULL               mainNode
**/

void test_genericAddRedBlackTree_add_record_into_redBlackTree(void){
    char buffer[20];
    Record *record = createRecord(buffer,20);
    
    resetGenericNode(&mainNode,record);
    setGenericNode(&mainNode,NULL,NULL,'b');
    
    Node *root = NULL;
    addMemory(&root,&mainNode);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
    
    destroyRecord(record);
}

/*****************************************

	2 NODE tests

*******************************************/
/**
*    root		              root
*     |    	add subLeftNode	 	|
*     v    	--------------->      	v
*  mainNode               	    mainNode
*    / \                    	     /
*   -   -                      subLeftNode
**/

void test_genericAddRedBlackTree_add_leftNode_into_redBlackTree(void){
    char buffer[50],buffer2[200];
    Record *leftRecord = createRecord(buffer,50);
    Record *mainRecord = createRecord(buffer2,200);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    
    Node *root = &mainNode;
    addMemory(&root,&leftNode);
    //Main node
    TEST_ASSERT_EQUAL_PTR(&mainNode,root);
    TEST_ASSERT_EQUAL_NODE(&leftNode,NULL,'b',root);
    //LeftNode 
    TEST_ASSERT_NOT_NULL(root->left->dataPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&leftNode);
    
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
}

/**
*	     root		                root
*	      |    add subRightNode	         |
*	      v    --------------->              v
*	   mainNode                          mainNode
*     	    /	\                            /      \
*          -     -                          -   subRightNode
**/
void test_genericAddRedBlackTree_add_rightNode_into_redBlackTree(void){
    char buffer[100],buffer2[200];
    Record *mainRecord = createRecord(buffer,100);
    Record *rightRecord = createRecord(buffer2,200);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&rightNode,rightRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&rightNode,NULL,NULL,'r');
    
    Node *root = &mainNode;
    addMemory(&root,&rightNode);
    //MainNode
    TEST_ASSERT_EQUAL_PTR(&mainNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,&rightNode,'b',root);
    //RightNode
    TEST_ASSERT_NOT_NULL(root->right->dataPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&rightNode);
    
    destroyRecord(rightRecord);
    destroyRecord(mainRecord);
}

/*****************************************

	3 NODE tests

*******************************************/
/**
*	     root		          root
*	      |    add rightNode	    |
*	      v    --------------->         v
*	   mainNode                       mainNode
*           /  \                  	   /  \
*     leftNode  -                   leftNode  rightNode
**/

void test_genericAddRedBlackTree_add_rightNode_into_2_nodes_redBlackTree(void){
    char buffer[100],buffer2[200],buffer3[300];
    Record *leftRecord = createRecord(buffer,100);
    Record *mainRecord = createRecord(buffer2,200);
    Record *rightRecord = createRecord(buffer3,300);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&rightNode,rightRecord);
    setGenericNode(&mainNode,&leftNode,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&rightNode,NULL,NULL,'r');
    
    Node *root = &mainNode;
    addMemory(&root,&rightNode);
    
    TEST_ASSERT_EQUAL_PTR(&mainNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&leftNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&rightNode);
    TEST_ASSERT_EQUAL_NODE(&leftNode,&rightNode,'b',&mainNode);
    
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
    destroyRecord(rightRecord);
}

/**
*	     root		        root
*	      |     add leftNode	 |
*	      v     --------------->     v
*	   mainNode                   mainNode
*          /    \                     /      \
*         -   rightNode         leftNode    rightNode
**/

void test_genericAddRedBlackTree_add_leftNode_into_2_nodes_redBlackTree(void){
    char buffer[100],buffer2[200],buffer3[300];
    Record *leftRecord = createRecord(buffer,100);
    Record *mainRecord = createRecord(buffer2,200);
    Record *rightRecord = createRecord(buffer3,300);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&rightNode,rightRecord);
    setGenericNode(&mainNode,NULL,&rightNode,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&rightNode,NULL,NULL,'r');
    
    Node *root = &mainNode;
    addMemory(&root,&leftNode);
    
    TEST_ASSERT_EQUAL_PTR(&mainNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&leftNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&rightNode);
    TEST_ASSERT_EQUAL_NODE(&leftNode,&rightNode,'b',&mainNode);
    
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
    destroyRecord(rightRecord);
}

/**
*	     root		            root                                       root
*	      |    add rightNodeChild	     |                                          |
*	      v    -------------------->     v                  leftRotate              v  
*	   mainNode                       mainNode              at mainNode          rightNode
*          /     \                        /      \            ------------->          /   \
*         -    rightNode                 -    rightNode                        mainNode rightNodeChild
*                                                  \
*                                              rightNodeChild                                 
*
**/
void test_genericAddRedBlackTree_add_rightNodeChild_into_2_node_redBlackTree_and_leftRotate(void){
    char buffer[100],buffer2[200],buffer3[300];
    Record *mainRecord = createRecord(buffer,100);
    Record *rightRecord = createRecord(buffer2,200);
    Record *rightRecordChild = createRecord(buffer3,300);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&rightNode,rightRecord);
    resetGenericNode(&rightNodeChild,rightRecordChild);
    setGenericNode(&mainNode,NULL,&rightNode,'b');
    setGenericNode(&rightNode,NULL,NULL,'r');
    setGenericNode(&rightNodeChild,NULL,NULL,'r');
    
    Node *root = &mainNode;
    addMemory(&root,&rightNodeChild);
    
    TEST_ASSERT_EQUAL_PTR(&rightNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&mainNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&rightNodeChild);
    TEST_ASSERT_EQUAL_NODE(&mainNode,&rightNodeChild,'b',&rightNode);
    
    destroyRecord(mainRecord);
    destroyRecord(rightRecord);
    destroyRecord(rightRecordChild);
}

/**
*	root		                    root                              root
*	  |    add leftNodeChild	     |                                 |
*	  v    -------------------->         v        rightRotate              v  
*      mainNode                           mainNode    at mainNode           leftNode
*       /   \                             /    \      ------------->        /     \
* leftNode   -                      leftNode    -                    leftNodeChild mainNode
*                                   /
*                             leftNodeChild                                 
*
**/

void test_genericAddRedBlackTree_add_leftNodeChild_into_2_nodes_redBlackTree_and_rightRotate(void){
    char buffer[100],buffer2[200],buffer3[300];
    Record *leftRecordChild = createRecord(buffer,100);
    Record *leftRecord = createRecord(buffer2,200);
    Record *mainRecord = createRecord(buffer3,300);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&leftNodeChild,leftRecordChild);
    setGenericNode(&mainNode,&leftNode,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&leftNodeChild,NULL,NULL,'r');
    
    Node *root = &mainNode;
    addMemory(&root,&leftNodeChild);
    
    TEST_ASSERT_EQUAL_PTR(&leftNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&mainNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&leftNodeChild);
    TEST_ASSERT_EQUAL_NODE(&leftNodeChild,&mainNode,'b',&leftNode);
    
    destroyRecord(mainRecord);
    destroyRecord(leftRecord);
    destroyRecord(leftRecordChild);
}

/**
*	  root		                    root                            root
*	    |    add rightNodeChild	     |                               |
*	    v    -------------------->       v       leftRightRotate         v  
*	 mainNode                         mainNode     at mainNode       rightNodeChild
*       /      \                          /      \   --------------->      /     \
*     leftNode   -                     leftNode   -                    leftNode mainNode
*                                         \
*                                   rightNodeChild                                 
*
**/

void test_genericAddRedBlackTree_add_rightNodeChild_into_2_nodes_redBlackTree_and_leftRightRotate(void){
    char buffer[100],buffer2[200],buffer3[300];
    Record *leftRecord = createRecord(buffer,100);
    Record *rightRecordChild = createRecord(buffer2,200);
    Record *mainRecord = createRecord(buffer3,300);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&rightNodeChild,rightRecordChild);
    setGenericNode(&rightNodeChild,NULL,NULL,'r');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&mainNode,&leftNode,NULL,'b');
    
    Node *root = &mainNode;
    addMemory(&root,&rightNodeChild);
    
    TEST_ASSERT_EQUAL_PTR(&rightNodeChild,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&mainNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&leftNode);
    TEST_ASSERT_EQUAL_NODE(&leftNode,&mainNode,'b',&rightNodeChild);
    
    destroyRecord(rightRecordChild);    
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
}