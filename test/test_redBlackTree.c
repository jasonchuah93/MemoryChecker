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
    Record record = {.memory = (void*)200};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&record);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR((Node*)&record,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&record);
    
    destroyRecord(&record);
}

/*****************************************

	2 NODE tests

*******************************************/
/**
*    root		              root
*     |    	add leftNode	 	|
*     v    	--------------->      	v
*  mainNode               	    mainNode
*    / \                    	     /
*   -   -                      leftNode
**/

void test_genericAddRedBlackTree_add_leftNode_into_redBlackTree(void){
    Record leftRecord = {.memory =(void*)100 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&leftRecord);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&mainRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&leftRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&leftRecord,NULL,'b',root);
    
    destroyRecord(&leftRecord);
    destroyRecord(&mainRecord);
}

/**
*	     root		                root
*	      |    add rightNode	         |
*	      v    --------------->              v
*	   mainNode                          mainNode
*     	    /	\                            /      \
*          -     -                          -   rightNode
**/
void test_genericAddRedBlackTree_add_rightNode_into_redBlackTree(void){
    Record rightRecord = {.memory =(void*)300 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&rightRecord);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&mainRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&rightRecord);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&rightRecord,'b',root);
    
    destroyRecord(&rightRecord);
    destroyRecord(&mainRecord);
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
    Record leftRecord = {.memory =(void*)100 ,.color = 'r'};  
    Record rightRecord = {.memory =(void*)300 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&leftRecord);
    addRecord(&root,(Node*)&rightRecord);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&mainRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&leftRecord);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&rightRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&leftRecord,(Node*)&rightRecord,'b',root);
    
    destroyRecord(&leftRecord);
    destroyRecord(&rightRecord);
    destroyRecord(&mainRecord);
    
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
    Record leftRecord = {.memory =(void*)100 ,.color = 'r'};  
    Record rightRecord = {.memory =(void*)300 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&rightRecord);
    addRecord(&root,(Node*)&leftRecord);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&mainRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&rightRecord);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&leftRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&leftRecord,(Node*)&rightRecord,'b',root);
    
    destroyRecord(&leftRecord);
    destroyRecord(&rightRecord);
    destroyRecord(&mainRecord);
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
    Record rightRecordChild = {.memory =(void*)400 ,.color = 'r'};  
    Record rightRecord = {.memory =(void*)300 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&rightRecord);
    addRecord(&root,(Node*)&rightRecordChild);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&rightRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&rightRecordChild);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&mainRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&mainRecord,(Node*)&rightRecordChild,'b',(Node*)&rightRecord);
    
    destroyRecord(&rightRecordChild);
    destroyRecord(&rightRecord);
    destroyRecord(&mainRecord);
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
    Record leftRecordChild = {.memory =(void*)50 ,.color = 'r'};  
    Record leftRecord = {.memory =(void*)100 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&leftRecord);
    addRecord(&root,(Node*)&leftRecordChild);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&leftRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&leftRecordChild);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&mainRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&leftRecordChild,(Node*)&mainRecord,'b',(Node*)&leftRecord);
    
    destroyRecord(&mainRecord);
    destroyRecord(&leftRecord);
    destroyRecord(&leftRecordChild);
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
    Record rightRecordChild = {.memory =(void*)200 ,.color = 'r'};  
    Record leftRecord = {.memory =(void*)100 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)300 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&leftRecord);
    addRecord(&root,(Node*)&rightRecordChild);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&rightRecordChild,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&mainRecord);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&leftRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&leftRecord,(Node*)&mainRecord,'b',(Node*)&rightRecordChild);
    
    destroyRecord(&rightRecordChild);    
    destroyRecord(&leftRecord);
    destroyRecord(&mainRecord);
}

/**
*	  root		                root                                    root
*	    |    add leftNodeChild	 |                                       |
*	    v    -------------------->   v              rightLeftRotate          v  
*	 mainNode                       mainNode          at mainNode         leftNodeChild
*        /    \                        /      \         ------------->          /   \
*       -     rightNode               -  rightNode                        mainNode rightNode
*                                            /
*                                       leftNodeChild                                 
*
**/
void test_genericAddRedBlackTree_add_leftNodeChild_into_2_nodes_redBlackTree_and_rightLeftRotate(void){
    Record leftRecordChild = {.memory =(void*)250 ,.color = 'r'};  
    Record rightRecord = {.memory =(void*)300 ,.color = 'r'};  
    Record mainRecord = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&rightRecord);
    addRecord(&root,(Node*)&leftRecordChild);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&leftRecordChild,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&mainRecord);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&rightRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)&mainRecord,(Node*)&rightRecord,'b',(Node*)&leftRecordChild);
    
    destroyRecord(&mainRecord);
    destroyRecord(&leftRecordChild);    
    destroyRecord(&rightRecord);
}

/*****************************************

	Error tests

*******************************************/

/**
*          root	                 root
*            |	 add mainNode	  |
*	     v   ----------->	  v
*	 mainNode              mainNode
*				  |
*			       Throw Error
**/

void test_genericAddRedBlackTree_should_throw_equivalent_error_for_node_with_equal_address_of_memory(void){
	ErrorCode e;
    Record mainRecord1 = {.memory=(void*)100,.color='b'};
    Record mainRecord2 = {.memory=(void*)100,.color='b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&mainRecord1);
    Try
	{
        addRecord(&root,(Node*)&mainRecord2);
		TEST_FAIL_MESSAGE("Should throw equivalent error ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_EQUIVALENT_MEMORY,e);
	}
}


