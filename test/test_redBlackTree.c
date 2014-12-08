#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "NodePtr.h"
#include "InitNode.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node mainNode,subLeftNode,subRightNode,subLeftNodeChild,subRightNodeChild;

void setUp(void){
	
}

void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*	root		        root
*	 |    add mainNode	 |
*	 v    ------>        v
*	NULL                mainNode
**/

void test_genericAddRedBlackTree_add_mainNode_into_empty_redBlackTree(void){
    Record *record = createRecord("5555AAAA",100);
    setGenericNode(&mainNode,record);
    Node *rootPtr = NULL;
    
    addMemory(&rootPtr,&mainNode);
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NULL(rootPtr->right);
    TEST_ASSERT_NULL(rootPtr->left);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',rootPtr);
    
    Record *readRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("5555AAAA",readRecord->memory);
    TEST_ASSERT_EQUAL(100,readRecord->size);
    TEST_ASSERT_EQUAL(35,readRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readRecord->fileName);
}

/*****************************************

	2 NODE tests

*******************************************/
/**
*	root		            root
*	 |    add subLeftNode	 |
*	 v    ------------>      v
*	mainNode               mainNode
*    / \                    /
*   -  -               subLeftNode
**/

void test_genericAddRedBlackTree_add_subLeftNode_into_redBlackTree(void){
    Record *mainRecord = createRecord("5555AAAA",100);
    Record *subLeftRecord = createRecord("5A5A5A",50);
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subLeftNode,subLeftRecord);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subLeftNode);
    
    //Main node
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->left);
    TEST_ASSERT_NULL(rootPtr->right);
    TEST_ASSERT_EQUAL_NODE(&subLeftNode,NULL,'b',rootPtr);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("5555AAAA",readMainRecord->memory);
    TEST_ASSERT_EQUAL(100,readMainRecord->size);
    TEST_ASSERT_EQUAL(68,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubLeftNode
    TEST_ASSERT_NOT_NULL(rootPtr->left->dataPtr);
    TEST_ASSERT_NULL(rootPtr->left->left);
    TEST_ASSERT_NULL(rootPtr->left->right);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subLeftNode);
    
    Record *readSubRecord =(Record*)rootPtr->left->dataPtr;
    TEST_ASSERT_EQUAL_STRING("5A5A5A",readSubRecord->memory);
    TEST_ASSERT_EQUAL(50,readSubRecord->size);
    TEST_ASSERT_EQUAL(69,readSubRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRecord->fileName);
    
}

/**
*	     root		                root
*	      |    add subRightNode	     |
*	      v    --------------->      v
*	   mainNode                   mainNode
*     /        \                  /      \
*    -          -                -   subRightNode
**/
void test_genericAddRedBlackTree_add_subRightNode_into_redBlackTree(void){
    Record *mainRecord = createRecord("0x123",100);
    Record *subRightRecord = createRecord("0x789",250);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subRightNode,subRightRecord);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subRightNode);
    
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NULL(rootPtr->left);
    TEST_ASSERT_NOT_NULL(rootPtr->right);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123",readMainRecord->memory);
    TEST_ASSERT_EQUAL(100,readMainRecord->size);
    TEST_ASSERT_EQUAL(111,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubRightNode
    TEST_ASSERT_NOT_NULL(rootPtr->right->dataPtr);
    TEST_ASSERT_NULL(rootPtr->right->left);
    TEST_ASSERT_NULL(rootPtr->right->right);
    
    Record *readSubRightRecord =(Record*)rootPtr->right->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubRightRecord->memory);
    TEST_ASSERT_EQUAL(250,readSubRightRecord->size);
    TEST_ASSERT_EQUAL(112,readSubRightRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecord->fileName);
    
    TEST_ASSERT_EQUAL_NODE(NULL,&subRightNode,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subRightNode);
    
}

/*****************************************

	3 NODE tests

*******************************************/
/**
*	     root		                root
*	      |    add subRightNode	     |
*	      v    --------------->      v
*	   mainNode                   mainNode
*     /        \                  /      \
*  subLeftNode  -         subLeftNode  subRightNode
**/

void test_genericAddRedBlackTree_add_subRightNode_into_2_node_redBlackTree(void){
    Record *mainRecord = createRecord("0x123",100);
    Record *subLeftRecord = createRecord("0x456",50);
    Record *subRightRecord = createRecord("0x789",250);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subLeftNode,subLeftRecord);
    setGenericNode(&subRightNode,subRightRecord);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subLeftNode);
    addMemory(&rootPtr,&subRightNode);
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->left);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123",readMainRecord->memory);
    TEST_ASSERT_EQUAL(100,readMainRecord->size);
    TEST_ASSERT_EQUAL(162,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubLeftNode
    TEST_ASSERT_NOT_NULL(rootPtr->left->dataPtr);
    TEST_ASSERT_NULL(rootPtr->left->left);
    TEST_ASSERT_NULL(rootPtr->left->right);
    
    Record *readSubLeftRecord =(Record*)rootPtr->left->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x456",readSubLeftRecord->memory);
    TEST_ASSERT_EQUAL(50,readSubLeftRecord->size);
    TEST_ASSERT_EQUAL(163,readSubLeftRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubLeftRecord->fileName);
    
    //SubRightNode
    TEST_ASSERT_NOT_NULL(rootPtr->right->dataPtr);
    TEST_ASSERT_NULL(rootPtr->right->left);
    TEST_ASSERT_NULL(rootPtr->right->right);
    
    Record *readSubRightRecord =(Record*)rootPtr->right->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubRightRecord->memory);
    TEST_ASSERT_EQUAL(250,readSubRightRecord->size);
    TEST_ASSERT_EQUAL(164,readSubRightRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecord->fileName);
    
    TEST_ASSERT_EQUAL_NODE(&subLeftNode,&subRightNode,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subLeftNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subRightNode);
}

/**
*	     root		                root
*	      |    add subLeftNode	     |
*	      v    --------------->      v
*	   mainNode                   mainNode
*     /        \                  /      \
*    -        subRightNode subLeftNode  subRightNode
**/

void test_genericAddRedBlackTree_add_subLeftNode_into_2_node_redBlackTree(void){
    Record *mainRecord = createRecord("0x123",100);
    Record *subLeftRecord = createRecord("0x456",50);
    Record *subRightRecord = createRecord("0x789",250);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subLeftNode,subLeftRecord);
    setGenericNode(&subRightNode,subRightRecord);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subRightNode);
    addMemory(&rootPtr,&subLeftNode);
    
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->right);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123",readMainRecord->memory);
    TEST_ASSERT_EQUAL(100,readMainRecord->size);
    TEST_ASSERT_EQUAL(220,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubRightNode
    TEST_ASSERT_NOT_NULL(rootPtr->right->dataPtr);
    TEST_ASSERT_NULL(rootPtr->right->left);
    TEST_ASSERT_NULL(rootPtr->right->right);
    
    Record *readSubRightRecord =(Record*)rootPtr->right->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubRightRecord->memory);
    TEST_ASSERT_EQUAL(250,readSubRightRecord->size);
    TEST_ASSERT_EQUAL(222,readSubRightRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecord->fileName);
    
    //SubLeftNode
    TEST_ASSERT_NOT_NULL(rootPtr->left->dataPtr);
    TEST_ASSERT_NULL(rootPtr->left->left);
    TEST_ASSERT_NULL(rootPtr->left->right);
    
    Record *readSubLeftRecord =(Record*)rootPtr->left->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x456",readSubLeftRecord->memory);
    TEST_ASSERT_EQUAL(50,readSubLeftRecord->size);
    TEST_ASSERT_EQUAL(221,readSubLeftRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubLeftRecord->fileName);
    
    TEST_ASSERT_EQUAL_NODE(&subLeftNode,&subRightNode,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subLeftNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subRightNode);
}

/**
*	     root		                    root                                       root
*	      |    add subRightNodeChild	 |                                          |
*	      v    -------------------->     v                  leftRotate              v  
*	   mainNode                       mainNode              at mainNode         subRightNode
*     /        \                      /      \            ------------->          /   \
*    -        subRightNode           -  subRightNode                        mainNode subRightNodeChild
*                                              \
*                                          subRightNodeChild                                 
*
**/
void test_genericAddRedBlackTree_add_subRightNodeChild_into_2_node_redBlackTree_and_leftRotate(void){
    Record *mainRecord = createRecord("0x123",100);
    Record *subRightRecord = createRecord("0x789",250);
    Record *subRightRecordChild = createRecord("0x456778",500);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subRightNode,subRightRecord);
    setGenericNode(&subRightNodeChild,subRightRecordChild);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subRightNode);
    addMemory(&rootPtr->right,&subRightNodeChild);
    
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(rightChild);
    TEST_ASSERT_NULL(leftChild);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123",readMainRecord->memory);
    TEST_ASSERT_EQUAL(100,readMainRecord->size);
    TEST_ASSERT_EQUAL(281,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubRightNode
    TEST_ASSERT_NOT_NULL(rightChild->dataPtr);
    TEST_ASSERT_NULL(rightLeftGrandChild);
    TEST_ASSERT_NOT_NULL(rightGrandChild);
    
    Record *readSubRightRecord =(Record*)rightChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubRightRecord->memory);
    TEST_ASSERT_EQUAL(250,readSubRightRecord->size);
    TEST_ASSERT_EQUAL(282,readSubRightRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecord->fileName);
    
    //SubRightNodeChild
    TEST_ASSERT_NOT_NULL(rightGrandChild->dataPtr);
    TEST_ASSERT_NULL(rightGrandChild->left);
    TEST_ASSERT_NULL(rightGrandChild->right);
    
    Record *readSubRightRecordChild =(Record*)rightGrandChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x456778",readSubRightRecordChild->memory);
    TEST_ASSERT_EQUAL(500,readSubRightRecordChild->size);
    TEST_ASSERT_EQUAL(283,readSubRightRecordChild->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecordChild->fileName);
    
    TEST_ASSERT_EQUAL_NODE(NULL,&subRightNode,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,&subRightNodeChild,'b',&subRightNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subRightNodeChild);
}

/**
*	     root		                    root                              root
*	      |    add subLeftNodeChild	     |                                 |
*	      v    -------------------->     v         rightRotate             v  
*	   mainNode                       mainNode     at mainNode         subLeftNode
*     /        \                      /      \   ------------->          /     \
* subLeftNode   -                subLeftNode   -             subLeftNodeChild mainNode
*                                   /
*                           subLeftNodeChild                                 
*
**/

void test_genericAddRedBlackTree_add_subLeftNodeChild_into_2_node_redBlackTree_and_rightRotate(void){
    Record *mainRecord = createRecord("0x123456789",1000);
    Record *subLeftRecord = createRecord("0x789",500);
    Record *subLeftRecordChild = createRecord("0x45",50);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subLeftNode,subLeftRecord);
    setGenericNode(&subLeftNodeChild,subLeftRecordChild);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subLeftNode);
    addMemory(&rootPtr->left,&subLeftNodeChild);
    
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(leftChild);
    TEST_ASSERT_NULL(rightChild);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123456789",readMainRecord->memory);
    TEST_ASSERT_EQUAL(1000,readMainRecord->size);
    TEST_ASSERT_EQUAL(344,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubLeftNode
    TEST_ASSERT_NOT_NULL(leftChild->dataPtr);
    TEST_ASSERT_NULL(leftRightGrandChild);
    TEST_ASSERT_NOT_NULL(leftGrandChild);
    
    Record *readSubLeftRecord =(Record*)leftChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubLeftRecord->memory);
    TEST_ASSERT_EQUAL(500,readSubLeftRecord->size);
    TEST_ASSERT_EQUAL(345,readSubLeftRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubLeftRecord->fileName);
    
    //SubLeftNodeChild
    TEST_ASSERT_NOT_NULL(leftGrandChild->dataPtr);
    TEST_ASSERT_NULL(leftGrandChild->left);
    TEST_ASSERT_NULL(leftGrandChild->right);
    
    Record *readSubLeftRecordChild =(Record*)leftGrandChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x45",readSubLeftRecordChild->memory);
    TEST_ASSERT_EQUAL(50,readSubLeftRecordChild->size);
    TEST_ASSERT_EQUAL(346,readSubLeftRecordChild->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubLeftRecordChild->fileName);
    
    TEST_ASSERT_EQUAL_NODE(&subLeftNode,NULL,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(&subLeftNodeChild,NULL,'b',&subLeftNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subLeftNodeChild);
}

/**
*	     root		                    root                                root
*	      |    add subRightNodeChild	     |                               |
*	      v    -------------------->     v       leftRightRotate             v  
*	   mainNode                       mainNode     at mainNode         subRightNodeChild
*     /        \                      /      \   ------------->          /     \
* subLeftNode   -                subLeftNode   -                 subLeftNode mainNode
*                                     \
*                                subRightNodeChild                                 
*
**/

void test_genericAddRedBlackTree_add_subRightNodeChild_into_2_node_redBlackTree_and_leftRightRotate(void){
    Record *mainRecord = createRecord("0x123456789",1000);
    Record *subLeftRecord = createRecord("0x789",500);
    Record *subRightRecordChild = createRecord("0x4556",700);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subLeftNode,subLeftRecord);
    setGenericNode(&subRightNodeChild,subRightRecordChild);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subLeftNode);
    addMemory(&rootPtr->left,&subRightNodeChild);
    
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(leftChild);
    TEST_ASSERT_NULL(rightChild);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123456789",readMainRecord->memory);
    TEST_ASSERT_EQUAL(1000,readMainRecord->size);
    TEST_ASSERT_EQUAL(407,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubLeftNode
    TEST_ASSERT_NOT_NULL(leftChild->dataPtr);
    TEST_ASSERT_NOT_NULL(leftRightGrandChild);
    TEST_ASSERT_NULL(leftGrandChild);
    
    Record *readSubLeftRecord =(Record*)leftChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubLeftRecord->memory);
    TEST_ASSERT_EQUAL(500,readSubLeftRecord->size);
    TEST_ASSERT_EQUAL(408,readSubLeftRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubLeftRecord->fileName);
    
    //SubRightNodeChild
    TEST_ASSERT_NOT_NULL(leftRightGrandChild->dataPtr);
    TEST_ASSERT_NULL(leftRightGrandChild->left);
    TEST_ASSERT_NULL(leftRightGrandChild->right);
    
    Record *readSubRightRecordChild =(Record*)leftRightGrandChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x4556",readSubRightRecordChild->memory);
    TEST_ASSERT_EQUAL(700,readSubRightRecordChild->size);
    TEST_ASSERT_EQUAL(409,readSubRightRecordChild->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecordChild->fileName);
    
    TEST_ASSERT_EQUAL_NODE(&subLeftNode,NULL,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(NULL,&subRightNodeChild,'b',&subLeftNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subRightNodeChild);
}

/**
*	     root		                    root                                       root
*	      |    add subRightNodeChild	 |                                          |
*	      v    -------------------->     v                  leftRotate              v  
*	   mainNode                       mainNode              at mainNode         subLeftNode
*     /        \                      /      \            ------------->          /   \
*    -        subRightNode           -  subRightNode                        mainNode subRightNodeChild
*                                            /
*                                    subLeftNodeChild                                 
*
**/
void test_genericAddRedBlackTree_add_subLeftNodeChild_into_2_node_redBlackTree_and_rightLeftRotate(void){
    Record *mainRecord = createRecord("0x123",100);
    Record *subRightRecord = createRecord("0x789",250);
    Record *subLeftRecordChild = createRecord("0x456",200);
    
    setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subRightNode,subRightRecord);
    setGenericNode(&subLeftNodeChild,subLeftRecordChild);
    Node *rootPtr = &mainNode;
    addMemory(&rootPtr,&subRightNode);
    addMemory(&rootPtr->right,&subLeftNodeChild);
    
    //MainNode
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NOT_NULL(rightChild);
    TEST_ASSERT_NULL(leftChild);
    
    Record *readMainRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x123",readMainRecord->memory);
    TEST_ASSERT_EQUAL(100,readMainRecord->size);
    TEST_ASSERT_EQUAL(469,readMainRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readMainRecord->fileName);
    
    //SubRightNode
    TEST_ASSERT_NOT_NULL(rightChild->dataPtr);
    TEST_ASSERT_NOT_NULL(rightLeftGrandChild);
    TEST_ASSERT_NULL(rightGrandChild);
    
    Record *readSubRightRecord =(Record*)rightChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x789",readSubRightRecord->memory);
    TEST_ASSERT_EQUAL(250,readSubRightRecord->size);
    TEST_ASSERT_EQUAL(470,readSubRightRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubRightRecord->fileName);
    
    //SubLeftNodeChild
    TEST_ASSERT_NOT_NULL(rightLeftGrandChild->dataPtr);
    TEST_ASSERT_NULL(rightLeftGrandChild->left);
    TEST_ASSERT_NULL(rightLeftGrandChild->right);
    
    Record *readSubLeftRecordChild =(Record*)rightLeftGrandChild->dataPtr;
    TEST_ASSERT_EQUAL_STRING("0x456",readSubLeftRecordChild->memory);
    TEST_ASSERT_EQUAL(200,readSubLeftRecordChild->size);
    TEST_ASSERT_EQUAL(471,readSubLeftRecordChild->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readSubLeftRecordChild->fileName);
    
    TEST_ASSERT_EQUAL_NODE(NULL,&subRightNode,'b',rootPtr);
    TEST_ASSERT_EQUAL_NODE(&subLeftNodeChild,NULL,'b',&subRightNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&subLeftNodeChild);
}

/*****************************************

	Error tests

*******************************************/

/**
*		root	             root
*		 |	add subLeftNode	  |
*		 v   ----------->	  v
*	 mainNode              mainNode
*				             /
*			           subLeftNode   (Throw Error)
**/

void test_genericAddRedBlackTree_should_throw_equivalent_error_for_node_with_same_infomation(void){
	Record *mainRecord = createRecord("0x123",100);
    Record *subLeftRecord = createRecord("0x123",100);
	setGenericNode(&mainNode,mainRecord);
    setGenericNode(&subLeftNode,subLeftRecord);
    Node *root = &mainNode;

	ErrorCode e;

	Try
	{
        addMemory(&root,&subLeftNode);
		TEST_FAIL_MESSAGE("Should throw equivalent error ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_EQUIVALENT_MEMORY ,e);
	}
}


