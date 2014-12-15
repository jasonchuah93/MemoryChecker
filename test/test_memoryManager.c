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

void test_memoryManagerAddRecord_should_add_r100_into_r200_generic_red_black_tree(void){ 
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r100 = {.memory = (void*)100, .color ='r'};
    root=NULL;
    memoryManagerAddRecord(&r200);
    memoryManagerAddRecord(&r100);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,NULL,'b',(Node*)&r200);
}

/**
*   root              root
*    |    add r500     |
*    v    --------->   v
*   r200              r200
*                       \
*                       r500
*
**/     

void test_memoryManagerAddRecord_should_add_r500_into_r200_generic_red_black_tree(void){
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r500 = {.memory = (void*)500, .color ='r'};
    root=NULL;
    memoryManagerAddRecord(&r200);
    memoryManagerAddRecord(&r500);
    TEST_ASSERT_EQUAL_PTR((Node*)&r200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r500);
    TEST_ASSERT_EQUAL_NODE(NULL,(Node*)&r500,'b',(Node*)&r200);
} 

/**
*   root              root                     root
*    |    add r30      |                        |
*    v    --------->   v     rightRotate        v  
*   r200              r200   --------------->  r50
*   /  \              /  \                    /   \
*  r50 -            r50  -                  r30  r200 
*                   /
*                 r30
*
**/     

void test_memoryManagerAddRecord_should_add_r30_into_r200_r50_generic_red_black_tree(void){
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r30 = {.memory = (void*)30, .color ='r'};
    Record r50 = {.memory = (void*)50, .color ='r'};
    root=NULL;
    memoryManagerAddRecord(&r200);
    memoryManagerAddRecord(&r50);
    memoryManagerAddRecord(&r30);
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r30);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r30,(Node*)&r200,'b',(Node*)&r50);
} 

/**
*   root              root                         root
*    |    add r300     |                            |
*    v    --------->   v     rightLeftRotate        v  
*   r200              r200   --------------->      r300
*   / \                  \                        /   \
*  -  r500               r500                   r200  r500 
*                         /
*                       r300
*
**/     

void test_memoryManagerAddRecord_should_add_r300_into_r200_r500_generic_red_black_tree(void){
    Record r200 = {.memory = (void*)200, .color ='b'};
    Record r300 = {.memory = (void*)300, .color ='r'};
    Record r500 = {.memory = (void*)500, .color ='r'};
    root=NULL;
    memoryManagerAddRecord(&r200);
    memoryManagerAddRecord(&r500);
    memoryManagerAddRecord(&r300);
    TEST_ASSERT_EQUAL_PTR((Node*)&r300,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r500);
    TEST_ASSERT_EQUAL_NODE((Node*)&r200,(Node*)&r500,'b',(Node*)&r300);
} 

