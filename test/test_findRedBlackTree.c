#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node mainNode,leftNode,rightNode,leftNodeChild,rightNodeChild;
Node nodeA,nodeB,nodeC,nodeD,nodeE,nodeF,nodeG,nodeH,nodeI,nodeJ,nodeK;  
Node nodeL,nodeM,nodeN,nodeO,nodeP,nodeQ,nodeR,nodeS,nodeT,nodeU,nodeV,nodeW;
void setUp(void){}

void tearDown(void){}

void test_genericFindRedBlackTree_find_mainNode_in_redBlackTree(void){
    char buffer[20];
    Node *findRoot=NULL;
    Record *record = createRecord(buffer,20);
    
    resetGenericNode(&mainNode,record);
    setGenericNode(&mainNode,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    findRoot = findRecord(root,((Record*)&mainNode)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&mainNode,findRoot);
    
    destroyRecord(record);
}

void test_genericFindRedBlackTree_find_leftNode_in_redBlackTree(void){
    char buffer[20],buffer2[30];
    Node *findRoot=NULL;
    Record *leftRecord = createRecord(buffer,20);
    Record *mainRecord = createRecord(buffer2,30);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    
    Node *root = NULL;
    addRecord(&root,&mainNode);
    addRecord(&root,&leftNode);
    findRoot = findRecord(root,((Record*)&leftNode)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&leftNode,findRoot);
    
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
}

void test_genericFindRedBlackTree_find_rightNode_in_redBlackTree(void){
    char buffer[20],buffer2[30];
    Node *findRoot=NULL;
    Record *mainRecord = createRecord(buffer,20);
    Record *rightRecord = createRecord(buffer2,30);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&rightNode,rightRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&rightNode,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&rightNode);
    findRoot = findRecord(root,((Record*)&rightNode)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&rightNode,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(rightRecord);
}

void test_genericFindRedBlackTree_find_leftNodeChild_in_leftNode_and_mainNode_redBlackTree(void){
    char buffer[20],buffer2[30],buffer3[40];
    Node *findRoot=NULL,*findRoot1 =NULL;
    Record *leftRecordChild = createRecord(buffer,20);
    Record *leftRecord = createRecord(buffer2,30);
    Record *mainRecord = createRecord(buffer3,40);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&leftNodeChild,leftRecordChild);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&leftNodeChild,NULL,NULL,'r');
    
    Node *root = NULL;
    addRecord(&root,&mainNode);
    addRecord(&root,&leftNode);
    addRecord(&root,&leftNodeChild);
    //Find leftNode
    findRoot1 = findRecord(root,((Record*)&leftNode)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot1);
    TEST_ASSERT_EQUAL(&leftNode,findRoot1);
    //Find leftNodeChild
    findRoot = findRecord(root,((Record*)&leftNodeChild)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&leftNodeChild,findRoot);
    
    destroyRecord(leftRecordChild);
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
}

void test_genericFindRedBlackTree_find_rightNodeChild_in_leftNode_and_mainNode_redBlackTree(void){
    char buffer[20],buffer2[30],buffer3[40];
    Node *findRoot=NULL;
    Record *leftRecord = createRecord(buffer,20);
    Record *rightRecordChild = createRecord(buffer2,30);
    Record *mainRecord = createRecord(buffer3,40);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&rightNodeChild,rightRecordChild);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&rightNodeChild,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&leftNode);
    addRecord(&root,&rightNodeChild);
    
    findRoot = findRecord(root,((Record*)&rightNodeChild)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&rightNodeChild,findRoot);
    
    destroyRecord(leftRecord);
    destroyRecord(rightRecordChild);
    destroyRecord(mainRecord);
}

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
void test_genericFindRedBlackTree_find_targetNode_in_large_redBlackTree(void){
    Node *findRoot=NULL;
    char buffer[20],buffer2[30],buffer3[40],buffer4[50],buffer5[60],buffer6[70];
    char buffer7[80],buffer8[90],buffer9[100],buffer10[110],buffer11[120],buffer12[130];
    char buffer13[140],buffer14[150],buffer15[160],buffer16[170],buffer17[180],buffer18[190];
    char buffer19[200],buffer20[210],buffer21[220],buffer22[230],buffer23[240],buffer24[250];
    Record *mainRecord = createRecord(buffer,20);
    Record *recordA = createRecord(buffer2,30);
    Record *recordB = createRecord(buffer3,40);
    Record *recordC = createRecord(buffer4,50);
    Record *recordD = createRecord(buffer5,60);
    Record *recordE = createRecord(buffer6,70);
    Record *recordF = createRecord(buffer7,80);
    Record *recordG = createRecord(buffer8,90);
    Record *recordH = createRecord(buffer9,100);
    Record *recordI = createRecord(buffer10,110);
    Record *recordJ = createRecord(buffer11,120);
    Record *recordK = createRecord(buffer12,130);
    Record *recordL = createRecord(buffer13,140);
    Record *recordM = createRecord(buffer14,150);
    Record *recordN = createRecord(buffer15,160);
    Record *recordO = createRecord(buffer16,170);
    Record *recordP = createRecord(buffer17,180);
    Record *recordQ = createRecord(buffer18,190);
    Record *recordR = createRecord(buffer19,200);
    Record *recordS = createRecord(buffer20,210);
    Record *recordT = createRecord(buffer21,220);
    Record *recordU = createRecord(buffer22,230);
    Record *recordV = createRecord(buffer23,240);
    Record *recordW = createRecord(buffer24,250);
    
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&nodeA,recordA);
    resetGenericNode(&nodeB,recordB);
    resetGenericNode(&nodeC,recordC);
    resetGenericNode(&nodeD,recordD);
    resetGenericNode(&nodeE,recordE);
    resetGenericNode(&nodeF,recordF);
    resetGenericNode(&nodeG,recordG);
    resetGenericNode(&nodeH,recordH);
    resetGenericNode(&nodeI,recordI);
    resetGenericNode(&nodeJ,recordJ);
    resetGenericNode(&nodeK,recordK);
    resetGenericNode(&nodeL,recordL);
    resetGenericNode(&nodeM,recordM);
    resetGenericNode(&nodeN,recordN);
    resetGenericNode(&nodeO,recordO);
    resetGenericNode(&nodeP,recordP);
    resetGenericNode(&nodeQ,recordQ);
    resetGenericNode(&nodeR,recordR);
    resetGenericNode(&nodeS,recordS);
    resetGenericNode(&nodeT,recordT);
    resetGenericNode(&nodeU,recordU);
    resetGenericNode(&nodeV,recordV);
    resetGenericNode(&nodeW,recordW);
    
    
    
    
    
    
    
    
    
    
    
    
}

