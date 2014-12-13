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
    Record *record = createRecord(buffer,100);
    resetGenericNode(&mainNode,record);
    setGenericNode(&mainNode,NULL,NULL,'b');
    Node *root = NULL;
    addMemory(&root,&mainNode);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_NOT_NULL(root->dataPtr);
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
    char buffer[100],buffer2[200];
    Record *leftRecord = createRecord(buffer,100);
    Record *mainRecord = createRecord(buffer2,100);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    Node *root = &mainNode;
    addMemory(&root,&leftNode);
    //Main node
    TEST_ASSERT_EQUAL_PTR(&mainNode,root);
    TEST_ASSERT_NOT_NULL(root->dataPtr);
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
    Record *rightRecord = createRecord(buffer2,250);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&rightNode,rightRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&rightNode,NULL,NULL,'r');
    Node *root = &mainNode;
    addMemory(&root,&rightNode);
    //MainNode
    TEST_ASSERT_EQUAL_PTR(&mainNode,root);
    TEST_ASSERT_NOT_NULL(root->dataPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,&rightNode,'b',root);
    //RightNode
    TEST_ASSERT_NOT_NULL(root->right->dataPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&rightNode);
}
