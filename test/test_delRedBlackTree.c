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

void test_genericDelRedBlackTree_remove_r1_from_redBlackTree(void){
    Record r10 = {.memory =(void*)10 , .color ='b'};
    Node *root =NULL;
    addRecord(&root,(Node*)&r10);
    deleteRecord(&root,(Node*)&r10);
    TEST_ASSERT_EQUAL_PTR(NULL,root);
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
*      root	         root
*	|    remove r50   |
*	v    -------->    v
*     r100              r100 
*     /                 / \ 
*    r50                -  -
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
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,NULL,'b',(Node*)&r100);
}


