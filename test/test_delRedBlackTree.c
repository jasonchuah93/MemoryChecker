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
void test_removeRecord_remove_size_100_from_200_root_and_add_into_new_root(void){
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Node n200 = {.data=&r200 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n200);
    addRecord(&root,&n100);
	
	Node *removedNode1 = removeRecord(&root,&n100);
	Node *removedNode2 = removeRecord(&root,&n200);
	
	TEST_ASSERT_EQUAL_PTR(root,NULL);
	TEST_ASSERT_EQUAL_PTR(removedNode1,&n100);
	TEST_ASSERT_EQUAL_PTR(removedNode2,&n200);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode2);
	
	Node *newRoot = NULL;
	addRecord(&newRoot,removedNode1);
	addRecord(&newRoot,removedNode2);
	
	TEST_ASSERT_EQUAL_PTR(newRoot,removedNode1);
	TEST_ASSERT_EQUAL_PTR(newRoot->right,removedNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,removedNode2,'b',newRoot);
}

/**
*    root              root
*     |     del n200    |
*     v     -------->   v
*    n200              n200	    
*    /  \              / \
*  n100  -            -   -
**/
void test_removeRecord_remove_roots_and_add_into_new_root(void){
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Node n200 = {.data=&r200 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n200);
    addRecord(&root,&n100);
	
	Node *removedNode1 = removeRecord(&root,&n100);
	Node *removedNode2 = removeRecord(&root,&n200);
	
	TEST_ASSERT_EQUAL_PTR(root,NULL);
	TEST_ASSERT_EQUAL_PTR(removedNode1,&n100);
	TEST_ASSERT_EQUAL_PTR(removedNode2,&n200);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode1);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode2);
	
	Node *newRoot = NULL;
	addRecord(&newRoot,removedNode1);
	addRecord(&newRoot,removedNode2);
	
	TEST_ASSERT_EQUAL_PTR(newRoot,removedNode1);
	TEST_ASSERT_EQUAL_PTR(newRoot->right,removedNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,removedNode2,'b',newRoot);
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
*  root               root
*   |    remove n100   |
*   v    ----------->  v
*  n100               n250 
*    \                / \ 
*    n250             -  -
*
**/
void test_removeRecord_remove_n100_from_n250_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r250 = {.memoryAllocateAddr =(void*)250};
    
	Node n250 = {.data=&r250 ,.color='r'};
	Node n100 = {.data=&r100 ,.right = &n250 ,.color='b'};

    Node *root = &n100;
    Node *removedNode = removeRecord(&root,&n100);
    
	TEST_ASSERT_EQUAL(&n250,root);
	TEST_ASSERT_EQUAL_PTR(&n100,removedNode);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
}

/*****************************************

	3 NODE TEST

*******************************************/
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
	Node n100 = {.data=&r100 ,.color='r'};
    
	Node *root = NULL;
	addRecord(&root,&n100);
	addRecord(&root,&n50);
	addRecord(&root,&n250);
	Node *removedNode = removeRecord(&root,&n50);
    TEST_ASSERT_EQUAL_PTR(&n100,root);
	TEST_ASSERT_EQUAL_PTR(&n50,removedNode);
	TEST_ASSERT_EQUAL_NODE(NULL,&n250,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n250);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
}

/**
*   root              root                root
*    |    remove n250   |   remove n100    |
*    v    --------->    v   ----------->   v
*   n100              n100                n50
*   /  \               / \ 
* n50  n250          n50  -
*
**/
void test_removeRecord_remove_n250_and_n100_from_n50_n250_n100_root(void){
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
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',removedNode);
	
	Node *removedNode2 = removeRecord(&root,&n100);
	TEST_ASSERT_EQUAL_PTR(&n50,root);
	TEST_ASSERT_EQUAL_PTR(&n100,removedNode2);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
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
	TEST_ASSERT_EQUAL(memoryAddr(root->left),memoryAddr(&n50));
	TEST_ASSERT_EQUAL(memoryAddr(removedNode),memoryAddr(&n100));
	TEST_ASSERT_EQUAL_NODE(&n50,NULL,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
}

/**
*   root            root             root                root                 root
*    |   add n400    |    add n500    |     leftRotate    |        add n300    |
*    v   -------->   v   --------->   v     ---------->   v       --------->   v
*   n100            n100             n100                n400                 n400
*                     \                \                 /  \                /   \
*                     n400            n400            n100  n500           n100  n500
*                                        \                                   \
*                                       n500                                n300
*
*                root                        root                   root
*                 |                           |                       |
* add n200        v      rightLeftRotate      v      rightRotate      v
* -------->      n400    --------------->    n400    ----------->    n200
*                / \                         /  \                    / \
*             n100  n500                   n200 n500              n100 n400
*                \                         /  \                        / \
*                n300                    n100 n300                   n300 n500
*                /
*              n200
*
*               root                     root                     root
*                |                        |                        |
* remove n400    v      remove n200       v    leftRightRotate     v
*------------>  n200    ---------->      n500  --------------->   n300
*               /  \                     /                        / \
*             n100 n500                n100                    n100 n500       
*                  /                     \
*                n300                   n300
*
*
*

**/
void test_for_safeFree(void){
	Record r100 = {.memoryAllocateAddr =(void*)100};
    Record r200 = {.memoryAllocateAddr =(void*)200};
    Record r300 = {.memoryAllocateAddr =(void*)300};
    Record r400 = {.memoryAllocateAddr =(void*)400};
	Record r500 = {.memoryAllocateAddr =(void*)500};
	
	Node n100 = {.data=&r100 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n400 = {.data=&r400 ,.color='r'};
	Node n500 = {.data=&r500 ,.color='r'};
	
	Node *root = NULL; 
	addRecord(&root,&n100);
	addRecord(&root,&n400);
	addRecord(&root,&n500);
	addRecord(&root,&n300);
	addRecord(&root,&n200);
	
	Node *removedNode = removeRecord(&root,&n400);
	
	TEST_ASSERT_EQUAL(&n200,root);
	TEST_ASSERT_EQUAL(&n400,removedNode);
	TEST_ASSERT_EQUAL_NODE(&n100,&n500,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n300);
	TEST_ASSERT_EQUAL_NODE(&n300,NULL,'b',&n500);
	TEST_ASSERT_EQUAL(memoryAddr(root->left),memoryAddr(&n100));
	TEST_ASSERT_EQUAL(memoryAddr(root->right),memoryAddr(&n500));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
	
	Node *removedNode2 = removeRecord(&root,&n200);
	TEST_ASSERT_EQUAL(&n300,root);
	TEST_ASSERT_EQUAL_NODE(&n100,&n500,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n500);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',removedNode);
}

/**
*   root                 root                    root
*    |    remove n400     |                       |
*    v    ----------->    v      leftRotate       v
*   n600                 n600    ---------->    n700
*   /  \                 / \                    /   \
* n400  n700            -  n700               n600  n800
*        \                   \
*        n800               n800
**/
void test_for_del_left_node_should_balance_the_tree(void){
	Record r400 = {.memoryAllocateAddr =(void*)400};
	Record r600 = {.memoryAllocateAddr =(void*)600};
	Record r700 = {.memoryAllocateAddr =(void*)700};
	Record r800 = {.memoryAllocateAddr =(void*)800};
	
	Node n400 = {.data=&r400 ,.color='r'};
	Node n600 = {.data=&r600 ,.color='r'};
	Node n700 = {.data=&r700 ,.color='r'};
	Node n800 = {.data=&r800 ,.color='r'};
	
	Node *root = NULL; 
	addRecord(&root,&n600);
	addRecord(&root,&n400);
	addRecord(&root,&n700);
	addRecord(&root,&n800);
	
	Node *removedNode = removeRecord(&root,&n400);
	
	TEST_ASSERT_EQUAL(&n700,root);
	TEST_ASSERT_EQUAL(&n400,removedNode);
	TEST_ASSERT_EQUAL_NODE(&n600,&n800,'b',root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n600);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n800);
}
