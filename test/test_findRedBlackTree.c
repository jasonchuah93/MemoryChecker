#include "unity.h"
#include "Node.h"
#include "Rotation.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

/*
*      root
*       |
*       v
*      r100
*
*
*/

void test_genericFindRedBlackTree_find_r100_in_redBlackTree(void){
    Node *targetRecord;
    Record r100 = {.memory=(void*)100,.color='b'};
    Node *node100 =(Node*)&r100;
    Node *root = NULL;
    
    addRecord(&root,node100);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(node100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
    
    targetRecord = findRecord(&root,((Record*)node100)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node100,targetRecord);
}

/*
*      root
*       |
*       v
*     r100
*     /
*   r50
*/
/*
void test_genericFindRedBlackTree_find_r50_in_r100_redBlackTree(void){
    Node *targetRecord;
    Record r100 = {.memory=(void*)100,.color='b'};
    Record r50 = {.memory=(void*)50,.color='r'};
    Node *node100 =(Node*)&r100;
    Node *node50 =(Node*)&r50;
    
    Node *root = NULL;
    addRecord(&root,node100);
    addRecord(&root,node50);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(node100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node50);
    TEST_ASSERT_EQUAL_NODE(node50,NULL,'b',root);
    
    targetRecord = findRecord(&root,((Record*)node50)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node50,targetRecord);
    
    destroyRecord(&r50);
    destroyRecord(&r100);
}
*/
/*
*      root
*       |
*       v
*      r100
*          \
*         r500
*/
/*
void test_genericFindRedBlackTree_find_r500_in_r100_redBlackTree(void){
    Node *targetRecord;
    Record r100 = {.memory=(void*)100,.color='b'};
    Record r500 = {.memory=(void*)500,.color='r'};
    Node *node100 =(Node*)&r100;
    Node *node500 =(Node*)&r500;
    
    Node *root = NULL;
    addRecord(&root,node100);
    addRecord(&root,node500);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(node100,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node500);
    TEST_ASSERT_EQUAL_NODE(NULL,node500,'b',root);
    
    targetRecord = findRecord(&root,((Record*)node500)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node500,targetRecord);
    
    destroyRecord(&r100);
    destroyRecord(&r500);
}
*/
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
/*
void test_genericFindRedBlackTree_find_r300_in_r100_r300_record500_redBlackTree(void){
    Node *targetRecord;
    Record record100 = {.memory=(void*)100,.color='b'};
    Record record300 = {.memory=(void*)300,.color='r'};
    Record record500 = {.memory=(void*)500,.color='r'};
    
    Node *node100 =(Node*)&record100;
    Node *node300 =(Node*)&record300;
    Node *node500 =(Node*)&record500;
    
    Node *root = NULL;
    addRecord(&root,node100);
    addRecord(&root,node500);
    addRecord(&root,node300);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(node300,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node500);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node100);
    TEST_ASSERT_EQUAL_NODE(node100,node500,'b',root);
    
    targetRecord = findRecord(&root,((Record*)node300)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node300,targetRecord);
    
    destroyRecord(&record100);
    destroyRecord(&record300);
    destroyRecord(&record500);
}
*/
/*
/*
*      root                 root
*       |                    |
*       v                    v                   
*      r100                 r80
*       /                  /  \
*     r50   ------->     r50 r100
*       \
*       r80
*/
/*
void test_genericFindRedBlackTree_find_r100_in_r50_r80_r100_redBlackTree(void){
    Node *targetRecord;
    Record record50 = {.memory=(void*)50,.color='r'};
    Record record80 = {.memory=(void*)80,.color='r'};
    Record record100 = {.memory=(void*)100,.color='b'};
    
    Node *node50 =(Node*)&record50;
    Node *node80 =(Node*)&record80;
    Node *node100 =(Node*)&record100;
    
    Node *root = NULL;
    addRecord(&root,node100);
    addRecord(&root,node50);
    addRecord(&root,node80);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(node80,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node50);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',node100);
    TEST_ASSERT_EQUAL_NODE(node50,node100,'b',node80);
    
    targetRecord = findRecord(&root,((Record*)node100)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node100,targetRecord);
    
    
}
*/
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
/*
void test_genericFindRedBlackTree_find_r1150_in_large_redBlackTree(void){
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
    
    Node *root = NULL;
    addRecord(&root,node1000);
    addRecord(&root,node500);
    addRecord(&root,node1500);
    addRecord(&root,node250);
    addRecord(&root,node700);
    addRecord(&root,node1200);
    addRecord(&root,node1800);
    addRecord(&root,node100);
    addRecord(&root,node450);
    addRecord(&root,node630);
    addRecord(&root,node950);
    addRecord(&root,node1150);
    addRecord(&root,node1340);
    addRecord(&root,node1600);
    addRecord(&root,node2000);
    addRecord(&root,node50);
    addRecord(&root,node300);
    addRecord(&root,node680);
    addRecord(&root,node800);
    addRecord(&root,node1450);
    addRecord(&root,node1950);
    
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
    targetRecord = findRecord(&root,((Record*)node1150)->memory); 
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node1150,targetRecord);
    
    
}
*/
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
/*
void test_genericFindRedBlackTree_find_r250_in_large_redBlackTree(void){
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
    
    Node *root = NULL;
    addRecord(&root,node1000);
    addRecord(&root,node500);
    addRecord(&root,node1500);
    addRecord(&root,node250);
    addRecord(&root,node700);
    addRecord(&root,node1200);
    addRecord(&root,node1800);
    addRecord(&root,node100);
    addRecord(&root,node450);
    addRecord(&root,node630);
    addRecord(&root,node950);
    addRecord(&root,node1150);
    addRecord(&root,node1340);
    addRecord(&root,node1600);
    addRecord(&root,node2000);
    addRecord(&root,node50);
    addRecord(&root,node300);
    addRecord(&root,node680);
    addRecord(&root,node800);
    addRecord(&root,node1450);
    addRecord(&root,node1950);
    
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
    targetRecord = findRecord(&root,((Record*)node250)->memory); 
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node250,targetRecord);
    
    
}
*/
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
/*
void test_genericFindRedBlackTree_find_r1450_in_large_redBlackTree(void){
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
    
    Node *root = NULL;
    addRecord(&root,node1000);
    addRecord(&root,node500);
    addRecord(&root,node1500);
    addRecord(&root,node250);
    addRecord(&root,node700);
    addRecord(&root,node1200);
    addRecord(&root,node1800);
    addRecord(&root,node100);
    addRecord(&root,node450);
    addRecord(&root,node630);
    addRecord(&root,node950);
    addRecord(&root,node1150);
    addRecord(&root,node1340);
    addRecord(&root,node1600);
    addRecord(&root,node2000);
    addRecord(&root,node50);
    addRecord(&root,node300);
    addRecord(&root,node680);
    addRecord(&root,node800);
    addRecord(&root,node1450);
    addRecord(&root,node1950);
    
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
    targetRecord = findRecord(&root,((Record*)node1450)->memory); 
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(node1450,targetRecord);
    
    destroyRecord(&r1000);
    destroyRecord(&r500); 
    destroyRecord(&r250); 
    destroyRecord(&r100); 
    destroyRecord(&r50); 
    destroyRecord(&r450); 
    destroyRecord(&r300); 
    destroyRecord(&r700); 
    destroyRecord(&r630); 
    destroyRecord(&r680); 
    destroyRecord(&r950); 
    destroyRecord(&r800); 
    destroyRecord(&r1500); 
    destroyRecord(&r1200); 
    destroyRecord(&r1800); 
    destroyRecord(&r1150); 
    destroyRecord(&r1340); 
    destroyRecord(&r1450);
    destroyRecord(&r1600); 
    destroyRecord(&r1950); 
    destroyRecord(&r2000); 
}
*/