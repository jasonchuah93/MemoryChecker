#include "unity.h"
#include "Node.h"
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
*	root		  root
*	 |    add r200     |
*	 v    --------->   v
*	NULL              r200
**/

void test_genericAddRedBlackTree_add_r200_into_redBlackTree(void){
    Record r200 = {.memory = (void*)200};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
    
    destroyRecord(&r200);
}

/*****************************************

	2 NODE tests

*******************************************/
/**
*    root		       root
*     |    	add r100	|
*     v    	-------->      	v
*    r200                     r200	    
*    / \                      / \
*   -   -                   r100  -   
**/

void test_genericAddRedBlackTree_add_r100_into_r200_redBlackTree(void){
    Record r100 = {.memory =(void*)100 ,.color = 'r'};  
    Record r200 = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r100);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,NULL,'b',root);
    
    destroyRecord(&r100);
    destroyRecord(&r200);
}

/**
*	     root		        root
*	      |    add r500	         |
*	      v    -------->             v
*	     r200                      r200       
*     	    /	\                     /   \
*          -     -                   -   r500
**/

void test_genericAddRedBlackTree_add_r500_into_r200_redBlackTree(void){
    Record r200 = {.memory =(void*)200 ,.color = 'b'};  
    Record r500 = {.memory =(void*)500 ,.color = 'r'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r500);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r500);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r500,'b',root);
    
    destroyRecord(&r200);
    destroyRecord(&r500);
}

/*****************************************

	3 NODE tests

*******************************************/
/**
*	 root		   root
*	  |    add r300	    |
*	  v    -------->    v
*	r200               r200        
*       /  \               /  \
*     r100  -           r100  r300
**/

void test_genericAddRedBlackTree_add_r300_into_r100_r200_redBlackTree(void){
    Record r100 = {.memory =(void*)100 ,.color = 'r'};  
    Record r200 = {.memory =(void*)200 ,.color = 'b'};
    Record r300 = {.memory =(void*)300 ,.color = 'r'};  
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r300);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,(Node*)&r300,'b',root);
    
    destroyRecord(&r100);
    destroyRecord(&r200);
    destroyRecord(&r300);
    
}

/**
*	  root		     root
*	   |     add r100     |
*	   v     --------->   v
*	 r200               r200    
*       /    \              / \
*      -    r300         r100 r300  
**/

void test_genericAddRedBlackTree_add_r100_into_r200_r300_redBlackTree(void){
    Record r100 = {.memory =(void*)100 ,.color = 'r'};  
    Record r200 = {.memory =(void*)200 ,.color = 'b'};
    Record r300 = {.memory =(void*)300 ,.color = 'r'};  
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r300);
    addRecord(&root,(Node*)&r100);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,(Node*)&r300,'b',root);
    
    destroyRecord(&r100);
    destroyRecord(&r200);
    destroyRecord(&r300);
}

/**
*	 root		    root                       root
*	  |    add r400	     |                          |
*	  v    -------->     v      leftRotate          v  
*	 r200              r200                        r300
*       /  \              /   \    ------------->     /   \
*    -    r300           -    r300                  r200  r400 
*                               \                     
*                              r400                
*
**/

void test_genericAddRedBlackTree_add_r400_into_r200_r300_redBlackTree_and_leftRotate(void){
    Record r200 = {.memory =(void*)200 ,.color = 'b'};
    Record r300 = {.memory =(void*)300 ,.color = 'r'};  
    Record r400 = {.memory =(void*)400 ,.color = 'r'};  
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r300);
    addRecord(&root,(Node*)&r400);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r300,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r400);
    TEST_ASSERT_EQUAL_NODE((Node*)&r200,(Node*)&r400,'b',root);
    
    destroyRecord(&r200);
    destroyRecord(&r300);
    destroyRecord(&r400);
}

/**
*	root		    root                      root
*	  |    add r50	     |                         |
*	  v    -------->     v     rightRotate         v  
*     r200                  r200   at r100            r100
*       /   \              /    \  ------------->     /  \
*     r100   -           r100    -                  r50  r200 
*                        /
*                      r50
*
**/


void test_genericAddRedBlackTree_add_r50_into_r100_r200_redBlackTree_and_rightRotate(void){
    Record r50 = {.memory =(void*)50 ,.color = 'r'};  
    Record r100 = {.memory =(void*)100 ,.color = 'r'};  
    Record r200 = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r50);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    
    destroyRecord(&r50);
    destroyRecord(&r100);
    destroyRecord(&r200);
}

/**
*     root		   root                          root
*       |    add r200	    |                            |
*	v    --------->     v       leftRightRotate      v  
*     r300                 r300     at r100             r200
*     /  \                 /  \   --------------->      /  \
*   r100  -             r100   -                     r100  r300
*                           \
*                          r200
*
**/

void test_genericAddRedBlackTree_add_rightNodeChild_into_2_nodes_redBlackTree_and_leftRightRotate(void){
    Record r200 = {.memory =(void*)200 ,.color = 'r'};  
    Record r100 = {.memory =(void*)100 ,.color = 'r'};  
    Record r300 = {.memory =(void*)300 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r300);
    addRecord(&root,(Node*)&r100);
    addRecord(&root,(Node*)&r200);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,(Node*)&r300,'b',(Node*)&r200);
    
    destroyRecord(&r200);    
    destroyRecord(&r100);
    destroyRecord(&r300);
}

/**
*	root		 root                            root
*	 |    add r250	  |                               |
*	 v   --------->   v      rightLeftRotate          v  
*      r200             r200                            r250
*     /    \            /  \    ------------->          /   \
*   -     r300         -   r300                       r200  r300
*                           /
*                          r250             
*
**/


void test_genericAddRedBlackTree_add_r250_int_r200_r300_redBlackTree_and_rightLeftRotate(void){
    Record r250 = {.memory =(void*)250 ,.color = 'r'};  
    Record r300 = {.memory =(void*)300 ,.color = 'r'};  
    Record r200 = {.memory =(void*)200 ,.color = 'b'};
    
    Node *root = NULL;
    addRecord(&root,(Node*)&r200);
    addRecord(&root,(Node*)&r300);
    addRecord(&root,(Node*)&r250);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r250,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r300);
    TEST_ASSERT_EQUAL_NODE((Node*)&r200,(Node*)&r300,'b',(Node*)&r250);
    
    destroyRecord(&r250);
    destroyRecord(&r300);    
    destroyRecord(&r200);
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


