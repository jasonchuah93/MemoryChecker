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

/**
*   root              root
*    |    add r200     |
*    v    --------->   v
*  r200             throw error
*
**/     

void test_memoryManagerAddRecord_should_throw_error_if_add_same_record_with_root_into_generic_red_black_tree(void){ 
    ErrorCode e;
    Record r200 = {.memory = (void*)200, .color ='b'};
    root = NULL;
    memoryManagerAddRecord(&r200);
    Try{
        memoryManagerAddRecord(&r200);
        TEST_FAIL_MESSAGE("Should throw equivalent error ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_EQUIVALENT_RECORD,e);
    }
}

/*
*      root
*       |
*       v
*      r100
*
*
*/

void test_memoryManagerFindRecord_find_r100_in_redBlackTree(void){
    Node *targetRecord;
    Record r100 = {.memory=(void*)100,.color='b'};
    Node *node100 =(Node*)&r100;
    root = NULL;
    
    memoryManagerAddRecord(&r100);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r100);
    
    targetRecord = (Node*)memoryManagerFindRecord(root,((Record*)node100)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node100,targetRecord);
}

/*
*      root                 root
*       |                    |
*       v                    v                   
*      r100                 r300
*         \                 /  \
*         r500   ----->   r100 r500
*         /
*       r300
*/

void test_memoryManagerFindRecord_find_r300_in_r100_r300_record500_redBlackTree(void){
    Node *targetRecord;
    Record r100 = {.memory=(void*)100,.color='b'};
    Record r300 = {.memory=(void*)300,.color='r'};
    Record r500 = {.memory=(void*)500,.color='r'};
    
    Node *node100 =(Node*)&r100;
    Node *node300 =(Node*)&r300;
    Node *node500 =(Node*)&r500;
    
    root = NULL;
    memoryManagerAddRecord(&r100);
    memoryManagerAddRecord(&r500);
    memoryManagerAddRecord(&r300);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR((Node*)&r300,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r500);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,(Node*)&r500,'b',(Node*)&r300);
    
    targetRecord = (Node*)memoryManagerFindRecord(root,((Record*)node300)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node300,targetRecord);
}

/**
*                              root
*                               |
*                             r1000
*                     /                    \
*                   r500                    r1500   
*               /         \             /          \  
*             r250        r700       r1200        r1800
*           /      \     /    \      /   \       /    \
*        r100     r450 r630   r950 r1150 r1340 r1600  r2000
*         /        /     \     /           \           /
*       r50      r300   r680  r800         r1450     r1950
*                        
*
**/

void test_memoryManagerFindRecord_find_r1450_in_large_redBlackTree(void){
    Node *targetRecord;
    Record r1000 = {.memory=(void*)1000,.color='b'};
    Record r500 = {.memory=(void*)500,.color='r'};
    Record r250 = {.memory=(void*)250,.color='r'};
    Record r100 = {.memory=(void*)100,.color='r'};
    Record r50 = {.memory=(void*)50,.color='r'};
    Record r450 = {.memory=(void*)450,.color='r'};
    Record r300 = {.memory=(void*)300,.color='r'};
    Record r700 = {.memory=(void*)700,.color='r'};
    Record r630 = {.memory=(void*)630,.color='r'};
    Record r680 = {.memory=(void*)680,.color='r'};
    Record r950 = {.memory=(void*)950,.color='r'};
    Record r800 = {.memory=(void*)800,.color='r'};
    Record r1500 = {.memory=(void*)1500,.color='r'};
    Record r1200 = {.memory=(void*)1200,.color='r'};
    Record r1800 = {.memory=(void*)1800,.color='r'};
    Record r1150 = {.memory=(void*)1150,.color='r'};
    Record r1340 = {.memory=(void*)1340,.color='r'};
    Record r1450 = {.memory=(void*)1450,.color='r'};
    Record r1600 = {.memory=(void*)1600,.color='r'};
    Record r1950 = {.memory=(void*)1950,.color='r'};
    Record r2000 = {.memory=(void*)2000,.color='r'};
    
    root = NULL;
    memoryManagerAddRecord(&r1000);
    memoryManagerAddRecord(&r500);
    memoryManagerAddRecord(&r1500);
    memoryManagerAddRecord(&r250);
    memoryManagerAddRecord(&r700);
    memoryManagerAddRecord(&r1200);
    memoryManagerAddRecord(&r1800);
    memoryManagerAddRecord(&r100);
    memoryManagerAddRecord(&r450);
    memoryManagerAddRecord(&r630);
    memoryManagerAddRecord(&r950);
    memoryManagerAddRecord(&r1150);
    memoryManagerAddRecord(&r1340);
    memoryManagerAddRecord(&r1600);
    memoryManagerAddRecord(&r2000);
    memoryManagerAddRecord(&r50);
    memoryManagerAddRecord(&r300);
    memoryManagerAddRecord(&r680);
    memoryManagerAddRecord(&r800);
    memoryManagerAddRecord(&r1450);
    memoryManagerAddRecord(&r1950);
    
    Node *node1000 =(Node*)&r1000; 
    Node *node500 =(Node*)&r500; 
    Node *node250 =(Node*)&r250; 
    Node *node100 =(Node*)&r100; 
    Node *node50 =(Node*)&r50; 
    Node *node450 =(Node*)&r450; 
    Node *node300 =(Node*)&r300; 
    Node *node700 =(Node*)&r700;
    Node *node630 =(Node*)&r630; 
    Node *node680 =(Node*)&r680; 
    Node *node950 =(Node*)&r950;
    Node *node800 =(Node*)&r800; 
    Node *node1500 =(Node*)&r1500; 
    Node *node1200 =(Node*)&r1200; 
    Node *node1800 =(Node*)&r1800; 
    Node *node1150 =(Node*)&r1150; 
    Node *node1340 =(Node*)&r1340; 
    Node *node1450 =(Node*)&r1450;
    Node *node1600 =(Node*)&r1600;
    Node *node1950 =(Node*)&r1950;
    Node *node2000 =(Node*)&r2000; 
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(node1000,root);
    TEST_ASSERT_EQUAL_NODE(node500,node1500,'b',root);
    TEST_ASSERT_EQUAL_NODE(node250,node700,'r',node500);
    TEST_ASSERT_EQUAL_NODE(node1200,node1800,'b',node1500);
    TEST_ASSERT_EQUAL_NODE(node100,node450,'b',node250);
    TEST_ASSERT_EQUAL_NODE(node630,node950,'b',node700);
    TEST_ASSERT_EQUAL_NODE(node1150,node1340,'r',node1200);
    TEST_ASSERT_EQUAL_NODE(node1600,node2000,'r',node1800);
    TEST_ASSERT_EQUAL_NODE(node50,NULL,'b',node100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node50);
    TEST_ASSERT_EQUAL_NODE(node300,NULL,'b',node450);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node300);
    TEST_ASSERT_EQUAL_NODE(NULL,node680,'b',node630);
    TEST_ASSERT_EQUAL_NODE(node800,NULL,'b',node950);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',node1150);
    TEST_ASSERT_EQUAL_NODE(NULL,node1450,'b',node1340);
    TEST_ASSERT_EQUAL_NODE(node1950,NULL,'b',node2000);
    
    //Find targetRecord
    targetRecord = (Node*)memoryManagerFindRecord(root,((Record*)node1450)->memory); 
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node1450,targetRecord);
}


