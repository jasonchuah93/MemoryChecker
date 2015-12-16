#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "mock_MallocWrapper.h"
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*	root               root
*	 |    remove n10    |
*	 v    ---------->   v
*	n10                NULL   -----> removedNode = n10
**/

void test_removeRecord_remove_n10_from_root(void){
    Record r10 = {.memoryAllocateAddr =(void*)10};
	Node n10 = {.data=&r10 ,.color='b'};
    
	Node *root = &n10;
    
    Node *removedNode = removeRecord(&root,&n10);
    TEST_ASSERT_EQUAL_PTR(NULL,root);
    TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(removedNode,&n10);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
}

/**
*	root		        
*	 |    remove n20	  
*	 v    ----------->  Throw ERR_NODE_UNAVAILABLE 
*	n100             
**/

void test_removeRecord_remove_n20_from_n100_root_should_throw_error(void){
    CEXCEPTION_T err;
    Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r20 = {.memoryAllocateAddr =(void*)20};
    
	Node n100 = {.data=&r100 ,.color='r'};
	Node n20 = {.data=&r20 ,.color='r'};
	
	Node *root = NULL;
    addRecord(&root,&n100);
    Try{
        Node *removedNode = removeRecord(&root,&n20);
        TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown.But receive none");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_NODE_UNAVAILABLE,err);
    }
}

/*****************************************

	2 NODE TEST

*******************************************/
/**
*  root              root
*   |    remove n50   |
*   v    --------->   v
*  n100              n100 
*   /                / \ 
* n50               -  -
*
**/
void test_removeRecord_remove_n50_from_n100_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100 };
    Record r50 = {.memoryAllocateAddr =(void*)50 };
    
    Node n50 = {.data=&r50 ,.color='r'};
	Node n100 = {.data=&r100 ,.left = &n50 ,.color='b'};
	
	Node *root = &n100;
    
	Node *removedNode = removeRecord(&root,&n50);
	TEST_ASSERT_EQUAL_PTR(&n100,root);
    TEST_ASSERT_EQUAL_PTR(&n50,removedNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
}

/**
*  root               root
*   |    remove n250   |
*   v    ----------->  v
*  n100               n100 
*    \                / \ 
*    n250             -  -
*
**/

void test_removeRecord_remove_n250_from_n100_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r250 = {.memoryAllocateAddr =(void*)250};
    
	Node n250 = {.data=&r250 ,.color='r'};
	Node n100 = {.data=&r100 ,.right = &n250 ,.color='b'};
	
    Node *root = &n100;
    
	Node *removedNode = removeRecord(&root,&n250);
    TEST_ASSERT_EQUAL_PTR(&n100,root);
	TEST_ASSERT_EQUAL_PTR(&n250,removedNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
}

/**
*   root              root
*    |    remove n50   |
*    v    --------->   v
*   n100              n100 
*   /  \               / \ 
* n50  n250           -  n250
*
**/

void test_removeRecord_remove_n50_from_n50_n250_n100_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r50 = {.memoryAllocateAddr =(void*)50 };
    Record r250 = {.memoryAllocateAddr =(void*)250};
    
	Node n50 = {.data=&r50 ,.color='r'};
	Node n250 = {.data=&r250 ,.color='r'};
	Node n100 = {.data=&r100 ,.left = &n50 ,.right = &n250 ,.color='b'};
    
	Node *root = &n100;
    
    Node *removedNode = removeRecord(&root,&n50);
    TEST_ASSERT_EQUAL_PTR(&n100,root);
	TEST_ASSERT_EQUAL_PTR(&n50,removedNode);
	TEST_ASSERT_EQUAL_NODE(NULL,&n250,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n250);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
}
