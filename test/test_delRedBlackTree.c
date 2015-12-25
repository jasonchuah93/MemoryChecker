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
#include "safeMalloc.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

/*****************************************

	1 NODE TEST

*******************************************/
/**
*    root              root
*     |     del n200    |
*     v     -------->   v
*    n200              null	    
*    
*    
**/
void test_removeRecord_remove_n200_and_root_become_null(void){
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Node n200 = {.data=&r200 ,.color='r'};
	
	Node *root = NULL;
    addRecord(&root,&n200);
    Node *removedNode = removeRecord(&root,&n200);
		
	TEST_ASSERT_EQUAL_PTR(root,NULL);
	TEST_ASSERT_EQUAL_PTR(removedNode,&n200);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
}

/*****************************************

	2 NODE TEST

*******************************************/
/**
*    root              root
*     |     del n100    |
*     v     -------->   v
*    n200              n200	    
*    /  \              / \
*  n100  -            -   -
**/
void test_removeRecord_remove_size_100_from_200_root(void){
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Node n200 = {.data=&r200 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n200);
    addRecord(&root,&n100);
	
	Node *removedNode = removeRecord(&root,&n100);
	TEST_ASSERT_EQUAL_PTR(root,&n200);
	TEST_ASSERT_EQUAL_PTR(removedNode,&n100);
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

/**
*   root              root
*    |    remove n250   |
*    v    --------->   v
*   n100              n100 
*   /  \               / \ 
* n50  n250          n50  -
*
**/
void test_removeRecord_remove_n250_from_n50_n250_n100_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r50 = {.memoryAllocateAddr =(void*)50 };
    Record r250 = {.memoryAllocateAddr =(void*)250};
    
	Node n50 = {.data=&r50 ,.color='r'};
	Node n250 = {.data=&r250 ,.color='r'};
	Node n100 = {.data=&r100 ,.left = &n50 ,.right = &n250 ,.color='b'};
    
	Node *root = &n100;
    
    Node *removedNode = removeRecord(&root,&n250);
    TEST_ASSERT_EQUAL_PTR(&n100,root);
	TEST_ASSERT_EQUAL_PTR(&n250,removedNode);
	TEST_ASSERT_EQUAL_NODE(&n50,NULL,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
}

/**
*   root              root
*    |    remove n100   |
*    v    --------->    v
*   n100               n250 
*   /  \               / \ 
* n50  n250          n50  -
*
**/
void test_removeRecord_remove_n100_from_n50_n250_n100_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r50 = {.memoryAllocateAddr =(void*)50 };
    Record r250 = {.memoryAllocateAddr =(void*)250};
    
	Node n50 = {.data=&r50 ,.color='r'};
	Node n250 = {.data=&r250 ,.color='r'};
	Node n100 = {.data=&r100 ,.left = &n50 ,.right = &n250 ,.color='b'};
    
	Node *root = &n100;
    
    Node *removedNode = removeRecord(&root,&n100);
    TEST_ASSERT_EQUAL_PTR(&n250,root);
	TEST_ASSERT_EQUAL_PTR(&n100,removedNode);
	TEST_ASSERT_EQUAL_NODE(&n50,NULL,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
}

