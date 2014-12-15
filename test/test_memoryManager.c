#include "unity.h"
#include "MemoryRecord.h"
#include "Node.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "RestructureNode.h"
#include "memoryManager.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

/**
*   root              root
*    |    add r200     |
*    v    --------->   v
*   NULL              r200
*
**/     

void test_memoryManagerAddRecord_should_add_r200_into_generic_red_black_tree_if_root_is_empty(void){ 
    Record r200 = {.memory = (void*)200, .color ='b'};
    Node *root ;
    root = (Node*)memoryManagerAddRecord(&r200);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
}

/**
*   root              root
*    |    add r100     |
*    v    --------->   v
*   r200              r200
*   / \               /  \
*  -   -            r100  -
*
**/     

void test_memoryManagerAddRecord_should_add_r100_into_r200_generic_red_black_tree(void){ 
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r100 = {.memory = (void*)100, .color ='r'};
    Node *root=NULL ;
    root = (Node*)memoryManagerAddRecord(&r200);
    root = (Node*)memoryManagerAddRecord(&r100);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,NULL,'b',(Node*)&r200);
}

/**
*   root              root
*    |    add r500     |
*    v    --------->   v
*   r200              r200
*   / \               /  \
*  -   -             -  r500
*
**/     


