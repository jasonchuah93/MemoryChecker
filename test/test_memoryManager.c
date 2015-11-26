#include "unity.h"
#include <stdlib.h>
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

void test_memoryManagerAddRecord_should_add_records_into_generic_red_black_tree_if_root_is_empty(void){ 
    char *record = malloc(10);
    char *record2 = malloc(50);
    char *record3 = malloc(100);
    Record *testRecord = createRecord(record,10);
    Record *testRecord2 = createRecord(record2,50);
    Record *testRecord3 = createRecord(record3,100);
    allocatedPool = NULL;
    memoryManagerAllocateRecord(testRecord);
    memoryManagerAllocateRecord(testRecord2);
    memoryManagerAllocateRecord(testRecord3);
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(allocatedPool,testRecord);
    TEST_ASSERT_EQUAL_NODE((Node*)testRecord3,(Node*)testRecord2,'b',(Node*)testRecord);
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
    Record r200 = {.memoryAddr = (void*)200, .color ='b'};
    Record r100 = {.memoryAddr = (void*)100, .color ='r'};
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r200);
    memoryManagerAllocateRecord(&r100);
    TEST_ASSERT_EQUAL_PTR(allocatedPool,(Node*)&r200);
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
    Record r200 = {.memoryAddr = (void*)200, .color ='b'};
    Record r500 = {.memoryAddr = (void*)500, .color ='r'};
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r200);
    memoryManagerAllocateRecord(&r500);
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
    Record r200 = {.memoryAddr = (void*)200, .color ='b'};
    Record r30 = {.memoryAddr = (void*)30, .color ='r'};
    Record r50 = {.memoryAddr = (void*)50, .color ='r'};
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r200);
    memoryManagerAllocateRecord(&r50);
    memoryManagerAllocateRecord(&r30);
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,allocatedPool);
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
    Record r200 = {.memoryAddr = (void*)200, .color ='b'};
    Record r300 = {.memoryAddr = (void*)300, .color ='r'};
    Record r500 = {.memoryAddr = (void*)500, .color ='r'};
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r200);
    memoryManagerAllocateRecord(&r500);
    memoryManagerAllocateRecord(&r300);
    TEST_ASSERT_EQUAL_PTR((Node*)&r300,allocatedPool);
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
    Record r200 = {.memoryAddr = (void*)200, .color ='b'};
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r200);
    Try{
        memoryManagerAllocateRecord(&r200);
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
    char *targetMemory = (void*)100;
    Node *targetRecord;
    Record r100 = {.memoryAddr=(void*)100,.color='b'};
    
    allocatedPool =NULL;
    memoryManagerAllocateRecord(&r100);
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r100);
    
    targetRecord = (Node*)memoryManagerFindRecord(allocatedPool,targetMemory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL((Node*)&r100,targetRecord);
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
    char *targetMemory = (void*)300;
    Record *targetRecord;
    Record r100 = {.memoryAddr=(void*)100,.color='b'};
    Record r300 = {.memoryAddr=(void*)300,.color='r'};
    Record r500 = {.memoryAddr=(void*)500,.color='r'};
    
    allocatedPool =NULL;
    memoryManagerAllocateRecord(&r100);
    memoryManagerAllocateRecord(&r500);
    memoryManagerAllocateRecord(&r300);
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR((Node*)&r300,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r500);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r100,(Node*)&r500,'b',(Node*)&r300);
    
    targetRecord = memoryManagerFindRecord(allocatedPool,targetMemory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(&r300,targetRecord);
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
    char *targetMemory = (void*)1450;
    Node *targetRecord;
    Record r1000 = {.memoryAddr=(void*)1000,.color='b'};
    Record r500 = {.memoryAddr=(void*)500,.color='r'};
    Record r250 = {.memoryAddr=(void*)250,.color='r'};
    Record r100 = {.memoryAddr=(void*)100,.color='r'};
    Record r50 = {.memoryAddr=(void*)50,.color='r'};
    Record r450 = {.memoryAddr=(void*)450,.color='r'};
    Record r300 = {.memoryAddr=(void*)300,.color='r'};
    Record r700 = {.memoryAddr=(void*)700,.color='r'};
    Record r630 = {.memoryAddr=(void*)630,.color='r'};
    Record r680 = {.memoryAddr=(void*)680,.color='r'};
    Record r950 = {.memoryAddr=(void*)950,.color='r'};
    Record r800 = {.memoryAddr=(void*)800,.color='r'};
    Record r1500 = {.memoryAddr=(void*)1500,.color='r'};
    Record r1200 = {.memoryAddr=(void*)1200,.color='r'};
    Record r1800 = {.memoryAddr=(void*)1800,.color='r'};
    Record r1150 = {.memoryAddr=(void*)1150,.color='r'};
    Record r1340 = {.memoryAddr=(void*)1340,.color='r'};
    Record r1450 = {.memoryAddr=(void*)1450,.color='r'};
    Record r1600 = {.memoryAddr=(void*)1600,.color='r'};
    Record r1950 = {.memoryAddr=(void*)1950,.color='r'};
    Record r2000 = {.memoryAddr=(void*)2000,.color='r'};
    
    allocatedPool =NULL;
    memoryManagerAllocateRecord(&r1000);
    memoryManagerAllocateRecord(&r500);
    memoryManagerAllocateRecord(&r1500);
    memoryManagerAllocateRecord(&r250);
    memoryManagerAllocateRecord(&r700);
    memoryManagerAllocateRecord(&r1200);
    memoryManagerAllocateRecord(&r1800);
    memoryManagerAllocateRecord(&r100);
    memoryManagerAllocateRecord(&r450);
    memoryManagerAllocateRecord(&r630);
    memoryManagerAllocateRecord(&r950);
    memoryManagerAllocateRecord(&r1150);
    memoryManagerAllocateRecord(&r1340);
    memoryManagerAllocateRecord(&r1600);
    memoryManagerAllocateRecord(&r2000);
    memoryManagerAllocateRecord(&r50);
    memoryManagerAllocateRecord(&r300);
    memoryManagerAllocateRecord(&r680);
    memoryManagerAllocateRecord(&r800);
    memoryManagerAllocateRecord(&r1450);
    memoryManagerAllocateRecord(&r1950);
    
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
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(node1000,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(node500,node1500,'b',allocatedPool);
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
    targetRecord = (Node*)memoryManagerFindRecord(allocatedPool,targetMemory); 
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node1450,targetRecord);
}

/**
*	root               root
*	 |    remove r10    |
*	 v    ---------->   v
*	r10                NULL
**/

void test_memoryManagerDelRecord_remove_r10_from_redBlackTree(void){
    Record r10 = {.memoryAddr =(void*)10 , .color ='b'};
    allocatedPool =NULL;
    memoryManagerAllocateRecord(&r10);
    memoryManagerDelRecord(&r10);
    TEST_ASSERT_EQUAL_PTR(NULL,allocatedPool);
    
}

/**
*	root		        
*	 |    remove r20	  
*	 v    ----------->  Throw ERR_NODE_UNAVAILABLE 
*	r100             
**/

void test_memoryManagerDelRecord_remove_r20_from_tree_with_r100_should_throw_error(void){
    CEXCEPTION_T err;
    Record r100 = {.memoryAddr =(void*)100 , .color ='b'};
    Record r20 = {.memoryAddr =(void*)20 , .color ='r'};
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r100);
    Try{
        memoryManagerDelRecord(&r20);
        TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown.But receive none");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_NODE_UNAVAILABLE,err);
    }
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

void test_memoryManagerDelRecord_remove_r250_r100_from_tree_with_r100_r250(void){
    Record r100 = {.memoryAddr =(void*)100 , .color ='b'};
    Record r50 = {.memoryAddr =(void*)50 , .color ='r'};
    Record r250 = {.memoryAddr =(void*)250 , .color ='r'};
    
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r100);
    memoryManagerAllocateRecord(&r50);
    memoryManagerAllocateRecord(&r250);
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r250);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r250,'b',(Node*)&r100);
    //Delete r250
    memoryManagerDelRecord(&r250);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,NULL,'b',(Node*)&r100);
    //Delete 100
    memoryManagerDelRecord(&r100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r50);
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

void test_memoryManagerDelRecord_remove_r200_r100_r50_from_tree_with_r10_r50_r80_r100_r200(void){
    Record r100 = {.memoryAddr =(void*)100 , .color ='b'};
    Record r10 = {.memoryAddr =(void*)10 , .color ='r'};
    Record r50 = {.memoryAddr =(void*)50 , .color ='r'};
    Record r80 = {.memoryAddr =(void*)80 , .color ='r'};
    Record r200 = {.memoryAddr =(void*)200 , .color ='r'};
    
    allocatedPool = NULL;
    memoryManagerAllocateRecord(&r100);
    memoryManagerAllocateRecord(&r50);
    memoryManagerAllocateRecord(&r200);
    memoryManagerAllocateRecord(&r10);
    memoryManagerAllocateRecord(&r80);
    
    TEST_ASSERT_EQUAL_PTR((Node*)&r100,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r200);
    TEST_ASSERT_EQUAL_NODE((Node*)&r50,(Node*)&r200,'b',(Node*)&r100);
    //Delete r200
    memoryManagerDelRecord(&r200);
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE((Node*)&r80,NULL,'b',(Node*)&r100);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r100,'b',(Node*)&r50);
    //Delete r100
    memoryManagerDelRecord(&r100);
    TEST_ASSERT_EQUAL_PTR((Node*)&r50,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&r80);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,(Node*)&r80,'b',(Node*)&r50);
    //Delete r50
    memoryManagerDelRecord(&r50);
    TEST_ASSERT_EQUAL_PTR((Node*)&r80,allocatedPool);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',(Node*)&r10);
    TEST_ASSERT_EQUAL_NODE((Node*)&r10,NULL,'b',(Node*)&r80);
}
