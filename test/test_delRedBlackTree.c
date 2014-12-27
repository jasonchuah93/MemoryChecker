#include "unity.h"
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
*	 |    remove r10    |
*	 v    ---------->   v
*	r10                NULL
**/

void test_genericDelRedBlackTree_remove_r10_from_redBlackTree(void){
    Record r10 = {.memory =(void*)10 , .color ='b'};
    Node *root =NULL;
    Node *freeRoot = NULL;
    addRecord(&root,(Node*)&r10);
    freeRoot = deleteRecord(&root,(Node*)&r10);
    TEST_ASSERT_EQUAL_PTR(NULL,root);
    TEST_ASSERT_EQUAL_PTR((Node*)&r10,freeRoot);
}

/**
*	root		        
*	 |    remove r20	  
*	 v    ----------->  Throw ERR_NODE_UNAVAILABLE 
*	r100             
**/

void test_delRedBlackTree_remove_r20_from_tree_with_r100_should_throw_error(void){
    CEXCEPTION_T err;
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r20 = {.memory =(void*)20 , .color ='r'};
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    Try{
        deleteRecord(&root,(Node*)&r20);
        TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown.But receive none");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_NODE_UNAVAILABLE,err);
    }
}

/*****************************************

	2 height level tests

*******************************************/
/**
*  root              root
*   |    remove r50   |
*   v    --------->   v
*  r100              r100 
*   /                / \ 
* r50               -  -
*
**/


void test_delRedBlackTree_remove_r50_from_tree_with_r100(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    
    Node *root =NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,NULL,'b',(Node*)&r100);
    //Delete r50
    deleteRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r100);
}

/**
*  root               root
*   |    remove r250   |
*   v    --------->    v
*  r100               r100 
*    \                / \ 
*    r250             -  -
*
**/

void test_delRedBlackTree_remove_r250_from_tree_with_r100(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r250 = {.memory =(void*)250 , .color ='r'};
    
    Node *root =NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r250);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r250);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r250,'b',(Node*)&r100);
    //Delete r250
    deleteRecord(&root,(Node*)&r250);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r100);
}

/**
*   root              root
*    |    remove r50   |
*    v    --------->   v
*   r100              r100 
*   /  \               / \ 
* r50  r250           -  r250
*
**/

void test_delRedBlackTree_remove_r50_from_tree_with_r100_r250(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r250 = {.memory =(void*)250 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r250);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r250);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r250,'b',(Node*)&r100);
    //Delete r50
    deleteRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r250,'b',(Node*)&r100);
}

/**
*   root              root
*    |    remove r250   |
*    v    ---------->   v
*   r100               r100 
*   /  \               / \ 
* r50  r250          r50  -
*
**/

void test_delRedBlackTree_remove_r250_from_tree_with_r100_r250(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r250 = {.memory =(void*)250 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r250);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r250);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r250,'b',(Node*)&r100);
    //Delete r250
    deleteRecord(&root,(Node*)&r250);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,NULL,'b',(Node*)&r100);
}

/*****************************************

	3 height level tests

*******************************************/

/**
*     root                       root
*      |                          |
*      v                          v
*     r100                       r200
*    /  \      remove r50       /   \
*  r50 r200    leftRotate    r100  r300
*      /  \    ----------->    \    
*    r150 r300                r150
*
**/

void test_delRedBlackTree_remove_r50_from_tree_with_r50_r100_r150_r200_r300(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    
    //Delete r50
    deleteRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r150,'b',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,(Node*)&r300,'b',(Node*)&r200);
}

/**
*    root                       root
*     |                          |
*     v                          v
*    r100                       r50
*    /  \    remove r200       /   \
*  r50  r200 rightRotate      r10   r100
* /  \      ----------->     / \   / \   
*r10 r80                    -  -  r80 -
*
**/

void test_delRedBlackTree_remove_r200_from_tree_with_r10_r50_r80_r100_r200(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r200
    deleteRecord(&root,(Node*)&r200);
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE((Node*)&r80,NULL,'b',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r100,'b',(Node*)&r50);
}

/**
*    root                       root
*     |                          |
*     v                          v
*    r100                       r100
*    /  \    remove r50        /   \
*  r50  r200 rightRotate      r80   r200
* /  \      ----------->     / \    / \   
*r10 r80                    r10 -  -  -
*
**/

void test_delRedBlackTree_remove_r50_from_tree_with_r10_r50_r80_r100_r200(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r200
    deleteRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,NULL,'b',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r80,(Node*)&r200,'b',(Node*)&r100);
}

/**
*      root                           root
*       |                              |
*       v                              v
*      r100                           r100
*     /    \                         /    \
*   r50    r200    remove r10      r50   r200
*  /  \    /  \    ----------->     / \    / \   
* r10 r80 r150 r300               -  r80 r150  r300
*
**/

void test_delRedBlackTree_remove_r10_from_tree_with_r10_r50_r80_r100_r200_r150_r300(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r10
    deleteRecord(&root,(Node*)&r10);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
}

/**
*      root                           root
*       |                              |
*       v                              v
*      r100                           r100
*     /    \                         /    \
*   r50    r200    remove r80      r50   r200
*  /  \    /  \    ----------->     / \    / \   
* r10 r80 r150 r300               r10  - r150  r300
*
**/

void test_delRedBlackTree_remove_r80_from_tree_with_r10_r50_r80_r100_r200_r150_r300(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r80
    deleteRecord(&root,(Node*)&r80);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,NULL,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
}

/**
*      root                           root
*       |                              |
*       v                              v
*      r100                           r100
*     /    \                         /    \
*   r50    r200    remove r150      r50   r200
*  /  \    /  \    ----------->     / \    / \   
* r10 r80 r150 r300               r10 r80 -  r300
*
**/

void test_delRedBlackTree_remove_r150_from_tree_with_r10_r50_r80_r100_r200_r150_r300(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r150
    deleteRecord(&root,(Node*)&r150);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
}

/**
*      root                           root
*       |                              |
*       v                              v
*      r100                           r100
*     /    \                         /    \
*   r50    r200    remove r300      r50    r200
*  /  \    /  \    ----------->     / \    /  \   
* r10 r80 r150 r300               r10 r80 r150 -
*
**/

void test_delRedBlackTree_remove_r300_from_tree_with_r10_r50_r80_r100_r200_r150_r300(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r150
    deleteRecord(&root,(Node*)&r300);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,NULL,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
}

/******************************************************
    Unit tests to implement removeNextLargerSuccessor
    into function genericDelRedBlackTree
*******************************************************/

/****************************************
*  root                root
*   |                   |
*   v   remove r50      v
*  r50 ------------>   r10
*  /
* r10
*****************************************/

void test_genericDelRedBlackTree_given_r50_r10_then_remove_successor_r50_should_return_r10(void){
    Record r50 = {.memory =(void*)50 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r10);
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,NULL,'b',(Node*)&r50);
    //Delete r50
    deleteRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_PTR((Node*)&r10,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r10);
}

/****************************************
*   root                root
*    |                   |
*    v   remove r50      v
*   r50 ------------>   r100
*  /  \                  / \
* r10 r100             r10  -
*****************************************/

void test_genericDelRedBlackTree_given_r50_r10_r100_then_remove_successor_r50_should_return_r100_r10(void){
    Record r50 = {.memory =(void*)50 , .color ='b'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r100 = {.memory =(void*)100 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r100);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r100,'b',(Node*)&r50);
    //Delete r50
    deleteRecord(&root,(Node*)&r50);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,NULL,'b',(Node*)&r100);
}

/**
*      root                           root
*       |                              |
*       v                              v
*      r100                           r100
*     /    \                         /    \
*   r50    r200    remove r150      r50    r200
*  /  \    /  \    ----------->     / \    /  \   
* r10 r80 r150 r300               r10 r80 r180 r300
*           \
*          r180
*
**/

void test_genericDelRedBlackTree_given_r50_r10_r80_r100_r200_r150_r180_r300_then_remove_successor_r150(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    Record r180 = {.memory =(void*)180 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    addRecord(&root,(Node*)&r180);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r180);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r180,'b',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r150
    deleteRecord(&root,(Node*)&r150);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r180);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r180,(Node*)&r300,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
}

/**
*      root                           root
*       |                              |
*       v                              v
*      r100                           r100
*     /    \                         /    \
*   r50    r200    remove r200      r50    r300
*  /  \    /  \    ----------->     / \    /  \   
* r10 r80 r150 r300               r10 r80 r150 -
*           \                              \
*          r180                           r180
*
**/

void test_genericDelRedBlackTree_given_r50_r10_r80_r100_r200_r150_r180_r300_then_remove_successor_r200(void){
    Record r100 = {.memory =(void*)100 , .color ='b'};
    Record r50 = {.memory =(void*)50 , .color ='r'};
    Record r200 = {.memory =(void*)200 , .color ='r'};
    Record r10 = {.memory =(void*)10 , .color ='r'};
    Record r80 = {.memory =(void*)80 , .color ='r'};
    Record r150 = {.memory =(void*)150 , .color ='r'};
    Record r300 = {.memory =(void*)300 , .color ='r'};
    Record r180 = {.memory =(void*)180 , .color ='r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r10);
    addRecord(&root,(Node*)&r80);
    addRecord(&root,(Node*)&r150);
    addRecord(&root,(Node*)&r300);
    addRecord(&root,(Node*)&r180);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r180);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r180,'b',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,(Node*)&r300,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r150
    deleteRecord(&root,(Node*)&r200);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r180,'b',(Node*)&r150);
    TEST_ASSERT_EQUAL_NODE((Node*)&r150,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r300,'b',(Node*)&r100);
}