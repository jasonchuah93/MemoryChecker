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

/*
*      root
*       |
*       v
*     mainNode
*
*
*/

void test_genericFindRedBlackTree_find_mainNode_in_redBlackTree(void){
    Node *targetRecord=NULL;
    Record record = {.memory=(void*)100,.color='b'};
    Node *nodeRecord =(Node*)&record;
    Node *root = NULL;
    
    addRecord(&root,nodeRecord);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(nodeRecord,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
    
    targetRecord = findRecord(&root,((Record*)nodeRecord)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(nodeRecord,targetRecord);
    
    destroyRecord(&record);
}

/*
*      root
*       |
*       v
*     mainNode
*       /
*   leftNode
*/

void test_genericFindRedBlackTree_find_leftNode_in_redBlackTree(void){
    Node *targetRecord=NULL;
    Record mainRecord = {.memory=(void*)100,.color='b'};
    Record leftRecord = {.memory=(void*)50,.color='r'};
    Node *mainNode =(Node*)&mainRecord;
    Node *leftNode =(Node*)&leftRecord;
    
    Node *root = NULL;
    addRecord(&root,mainNode);
    addRecord(&root,leftNode);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(mainNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftNode);
    TEST_ASSERT_EQUAL_NODE(leftNode,NULL,'b',root);
    
    targetRecord = findRecord(&root,((Record*)leftNode)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(leftNode,targetRecord);
    
    destroyRecord(&leftRecord);
    destroyRecord(&mainRecord);
}

/*
*      root
*       |
*       v
*     mainNode
*           \
*           rightNode
*/

void test_genericFindRedBlackTree_find_rightNode_in_redBlackTree(void){
    Node *targetRecord=NULL;
    Record mainRecord = {.memory=(void*)100,.color='b'};
    Record rightRecord = {.memory=(void*)500,.color='r'};
    Node *mainNode =(Node*)&mainRecord;
    Node *rightNode =(Node*)&rightRecord;
    
    Node *root = NULL;
    addRecord(&root,mainNode);
    addRecord(&root,rightNode);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR(mainNode,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightNode);
    TEST_ASSERT_EQUAL_NODE(NULL,rightNode,'b',root);
    
    targetRecord = findRecord(&root,((Record*)rightNode)->memory); 
    
    TEST_ASSERT_NOT_NULL(targetRecord);
    TEST_ASSERT_EQUAL(rightNode,targetRecord);
    
    destroyRecord(&rightRecord);
    destroyRecord(&mainRecord);
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

void test_genericFindRedBlackTree_find_r300_in_r100_r300_record500_redBlackTree(void){
    Node *targetRecord=NULL;
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

void test_genericFindRedBlackTree_find_r100_in_r50_r80_r100_redBlackTree(void){
    Node *targetRecord=NULL;
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
    
    destroyRecord(&record50);
    destroyRecord(&record80);
    destroyRecord(&record100);
}

/*
void test_genericFindRedBlackTree_find_leftNodeChild_in_rightNode_and_mainNode_redBlackTree(void){
    char buffer[20],buffer2[30],buffer3[40];
    Node *findRoot=NULL;
    Record *mainRecord = createRecord(buffer,20);
    Record *leftRecordChild = createRecord(buffer2,30);
    Record *rightRecord = createRecord(buffer3,40);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&rightNode,rightRecord);
    resetGenericNode(&leftNodeChild,leftRecordChild);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&rightNode,NULL,NULL,'r');
    setGenericNode(&leftNodeChild,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&rightNode);
    addRecord(&root,&leftNodeChild);
    findRoot = findRecord(root,((Record*)&leftNodeChild)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&leftNodeChild,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(leftRecordChild);
    destroyRecord(rightRecord);
}

void test_genericFindRedBlackTree_find_rightNodeChild_in_rightNode_and_mainNode_redBlackTree(void){
    char buffer[20],buffer2[30],buffer3[40];
    Node *findRoot=NULL;
    Record *mainRecord = createRecord(buffer,20);
    Record *rightRecord = createRecord(buffer2,30);
    Record *rightRecordChild = createRecord(buffer3,40);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&rightNode,rightRecord);
    resetGenericNode(&rightNodeChild,rightRecordChild);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&rightNode,NULL,NULL,'r');
    setGenericNode(&rightNodeChild,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&rightNode);
    addRecord(&root,&rightNodeChild);
    findRoot = findRecord(root,((Record*)&rightNodeChild)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&rightNodeChild,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(rightRecord);
    destroyRecord(rightRecordChild);
}
*/

/**
*                               root
*                                |
*                             mainNode
*                     /                     \
*                   nodeA                  nodeB   
*               /         \             /           \ 
*            nodeC        nodeD       nodeE        nodeF
*           /      \     /    \      /   \       /      \
*        nodeG    nodeH nodeI nodeJ nodeK nodeL nodeM nodeN
*         /         /     \     /           \           /
*       nodeO     nodeP  nodeQ nodeR       nodeS      nodeT
*                         /      \            /
*                       nodeU    nodeV     nodeW
*
**/
/*
void test_genericFindRedBlackTree_find_nodeP_in_large_redBlackTree(void){
    Node *findRoot=NULL;
    Record mainRecord = {.memory=(void*)500};
    Record recordA = {.memory=(void*)250};
    Record recordB = {.memory=(void*)750};
    Record recordC = {.memory=(void*)200};
    Record recordD = {.memory=(void*)0};
    Record recordE = {.memory=(void*)330};
    Record recordF = {.memory=(void*)350};
    Record recordG = {.memory=(void*)100};
    Record recordH = {.memory=(void*)230};
    Record recordI = {.memory=(void*)260};
    Record recordJ = {.memory=(void*)350};
    Record recordK = {.memory=(void*)200};
    Record recordL = {.memory=(void*)350};
    Record recordM = {.memory=(void*)200};
    Record recordN = {.memory=(void*)350};
    Record recordO = {.memory=(void*)50};
    Record recordP = {.memory=(void*)210};
    Record recordQ = {.memory=(void*)290};
    Record recordR = {.memory=(void*)350};
    Record recordS = {.memory=(void*)200};
    Record recordT = {.memory=(void*)350};
    Record recordU = {.memory=(void*)260};
    Record recordV = {.memory=(void*)350};
    Record recordW = {.memory=(void*)200};
    
    Node *root = NULL; 
    addRecord(&root,(Node*)&mainRecord);
    addRecord(&root,(Node*)&recordA);
    addRecord(&root,(Node*)&recordB);
    addRecord(&root,(Node*)&recordC);
    addRecord(&root,(Node*)&recordD);
    addRecord(&root,(Node*)&recordE);
    addRecord(&root,(Node*)&recordF);
    addRecord(&root,(Node*)&recordG);
    addRecord(&root,(Node*)&recordH);
    addRecord(&root,(Node*)&recordI);
    addRecord(&root,(Node*)&recordJ);
    addRecord(&root,(Node*)&recordK);
    addRecord(&root,(Node*)&recordL);
    addRecord(&root,(Node*)&recordM);
    addRecord(&root,(Node*)&recordN);
    addRecord(&root,(Node*)&recordO);
    addRecord(&root,(Node*)&recordP);
    addRecord(&root,(Node*)&recordQ);
    addRecord(&root,(Node*)&recordR);
    addRecord(&root,(Node*)&recordS);
    addRecord(&root,(Node*)&recordT);
    addRecord(&root,(Node*)&recordU);
    addRecord(&root,(Node*)&recordV);
    addRecord(&root,(Node*)&recordW);
    
     
    
    TEST_ASSERT_EQUAL_PTR(&mainRecord,root);
    TEST_ASSERT_EQUAL_NODE((Node*)&recordA,(Node*)&recordB,'b',(Node*)&mainRecord);
    
}
*/