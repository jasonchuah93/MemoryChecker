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
    root = NULL;
    memoryManagerAddRecord(&r200);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
}

/**
*   root              root
*    |    add r100     |
*    v    --------->   v
*   r200              r200
*                     /
*                   r100
*
**/     

void test_memoryManagerAddRecord_should_add_r100_into_r200_generic_red_black_tree_if_root(void){ 
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r100 = {.memory = (void*)100, .color ='r'};
    root=NULL;
    memoryManagerAddRecord(&r200);
    memoryManagerAddRecord(&r100);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,NULL,'b',(Node*)&r200);
}

void test_memoryManagerAddRecord_should_add_r500_into_r200_generic_red_black_tree_if_root(void){
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r500 = {.memory = (void*)500, .color ='r'};
    root=NULL;
    memoryManagerAddRecord(&r200);
    memoryManagerAddRecord(&r500);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r500,'b',(Node*)&r200);
} 