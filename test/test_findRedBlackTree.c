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

void test_genericFindRedBlackTree_find_nodeS_in_large_redBlackTree(void){
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
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&nodeA,NULL,NULL,'r');
    setGenericNode(&nodeB,NULL,NULL,'r');
    setGenericNode(&nodeC,NULL,NULL,'r');
    setGenericNode(&nodeD,NULL,NULL,'r');
    setGenericNode(&nodeE,NULL,NULL,'r');
    setGenericNode(&nodeF,NULL,NULL,'r');
    setGenericNode(&nodeG,NULL,NULL,'r');
    setGenericNode(&nodeH,NULL,NULL,'r');
    setGenericNode(&nodeI,NULL,NULL,'r');
    setGenericNode(&nodeJ,NULL,NULL,'r');
    setGenericNode(&nodeK,NULL,NULL,'r');
    setGenericNode(&nodeL,NULL,NULL,'r');
    setGenericNode(&nodeM,NULL,NULL,'r');
    setGenericNode(&nodeN,NULL,NULL,'r');
    setGenericNode(&nodeO,NULL,NULL,'r');
    setGenericNode(&nodeP,NULL,NULL,'r');
    setGenericNode(&nodeQ,NULL,NULL,'r');
    setGenericNode(&nodeR,NULL,NULL,'r');
    setGenericNode(&nodeS,NULL,NULL,'r');
    setGenericNode(&nodeT,NULL,NULL,'r');
    setGenericNode(&nodeU,NULL,NULL,'r');
    setGenericNode(&nodeV,NULL,NULL,'r');
    setGenericNode(&nodeW,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&nodeA);
    addRecord(&root,&nodeB);
    addRecord(&root,&nodeC);
    addRecord(&root,&nodeD);
    addRecord(&root,&nodeE);
    addRecord(&root,&nodeF);
    addRecord(&root,&nodeG);
    addRecord(&root,&nodeH);
    addRecord(&root,&nodeI);
    addRecord(&root,&nodeJ);
    addRecord(&root,&nodeK);
    addRecord(&root,&nodeL);
    addRecord(&root,&nodeM);
    addRecord(&root,&nodeN);
    addRecord(&root,&nodeO);
    addRecord(&root,&nodeP);
    addRecord(&root,&nodeQ);
    addRecord(&root,&nodeR);
    addRecord(&root,&nodeS);
    addRecord(&root,&nodeT);
    addRecord(&root,&nodeU);
    addRecord(&root,&nodeV);
    addRecord(&root,&nodeW);
    
    findRoot = findRecord(root,((Record*)&nodeS)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&nodeS,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(recordA);
    destroyRecord(recordB);
    destroyRecord(recordC);
    destroyRecord(recordD);
    destroyRecord(recordE);
    destroyRecord(recordF);
    destroyRecord(recordG);
    destroyRecord(recordH);
    destroyRecord(recordI);
    destroyRecord(recordJ);
    destroyRecord(recordK);
    destroyRecord(recordL);
    destroyRecord(recordM);
    destroyRecord(recordN);
    destroyRecord(recordO);
    destroyRecord(recordP);
    destroyRecord(recordQ);
    destroyRecord(recordR);
    destroyRecord(recordS);
    destroyRecord(recordT);
    destroyRecord(recordU);
    destroyRecord(recordV);
    destroyRecord(recordW);
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

void test_genericFindRedBlackTree_find_nodeJ_in_large_redBlackTree(void){
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
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&nodeA,NULL,NULL,'r');
    setGenericNode(&nodeB,NULL,NULL,'r');
    setGenericNode(&nodeC,NULL,NULL,'r');
    setGenericNode(&nodeD,NULL,NULL,'r');
    setGenericNode(&nodeE,NULL,NULL,'r');
    setGenericNode(&nodeF,NULL,NULL,'r');
    setGenericNode(&nodeG,NULL,NULL,'r');
    setGenericNode(&nodeH,NULL,NULL,'r');
    setGenericNode(&nodeI,NULL,NULL,'r');
    setGenericNode(&nodeJ,NULL,NULL,'r');
    setGenericNode(&nodeK,NULL,NULL,'r');
    setGenericNode(&nodeL,NULL,NULL,'r');
    setGenericNode(&nodeM,NULL,NULL,'r');
    setGenericNode(&nodeN,NULL,NULL,'r');
    setGenericNode(&nodeO,NULL,NULL,'r');
    setGenericNode(&nodeP,NULL,NULL,'r');
    setGenericNode(&nodeQ,NULL,NULL,'r');
    setGenericNode(&nodeR,NULL,NULL,'r');
    setGenericNode(&nodeS,NULL,NULL,'r');
    setGenericNode(&nodeT,NULL,NULL,'r');
    setGenericNode(&nodeU,NULL,NULL,'r');
    setGenericNode(&nodeV,NULL,NULL,'r');
    setGenericNode(&nodeW,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&nodeA);
    addRecord(&root,&nodeB);
    addRecord(&root,&nodeC);
    addRecord(&root,&nodeD);
    addRecord(&root,&nodeE);
    addRecord(&root,&nodeF);
    addRecord(&root,&nodeG);
    addRecord(&root,&nodeH);
    addRecord(&root,&nodeI);
    addRecord(&root,&nodeJ);
    addRecord(&root,&nodeK);
    addRecord(&root,&nodeL);
    addRecord(&root,&nodeM);
    addRecord(&root,&nodeN);
    addRecord(&root,&nodeO);
    addRecord(&root,&nodeP);
    addRecord(&root,&nodeQ);
    addRecord(&root,&nodeR);
    addRecord(&root,&nodeS);
    addRecord(&root,&nodeT);
    addRecord(&root,&nodeU);
    addRecord(&root,&nodeV);
    addRecord(&root,&nodeW);
    
    findRoot = findRecord(root,((Record*)&nodeJ)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&nodeJ,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(recordA);
    destroyRecord(recordB);
    destroyRecord(recordC);
    destroyRecord(recordD);
    destroyRecord(recordE);
    destroyRecord(recordF);
    destroyRecord(recordG);
    destroyRecord(recordH);
    destroyRecord(recordI);
    destroyRecord(recordJ);
    destroyRecord(recordK);
    destroyRecord(recordL);
    destroyRecord(recordM);
    destroyRecord(recordN);
    destroyRecord(recordO);
    destroyRecord(recordP);
    destroyRecord(recordQ);
    destroyRecord(recordR);
    destroyRecord(recordS);
    destroyRecord(recordT);
    destroyRecord(recordU);
    destroyRecord(recordV);
    destroyRecord(recordW);
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

void test_genericFindRedBlackTree_find_nodeU_in_large_redBlackTree(void){
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
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&nodeA,NULL,NULL,'r');
    setGenericNode(&nodeB,NULL,NULL,'r');
    setGenericNode(&nodeC,NULL,NULL,'r');
    setGenericNode(&nodeD,NULL,NULL,'r');
    setGenericNode(&nodeE,NULL,NULL,'r');
    setGenericNode(&nodeF,NULL,NULL,'r');
    setGenericNode(&nodeG,NULL,NULL,'r');
    setGenericNode(&nodeH,NULL,NULL,'r');
    setGenericNode(&nodeI,NULL,NULL,'r');
    setGenericNode(&nodeJ,NULL,NULL,'r');
    setGenericNode(&nodeK,NULL,NULL,'r');
    setGenericNode(&nodeL,NULL,NULL,'r');
    setGenericNode(&nodeM,NULL,NULL,'r');
    setGenericNode(&nodeN,NULL,NULL,'r');
    setGenericNode(&nodeO,NULL,NULL,'r');
    setGenericNode(&nodeP,NULL,NULL,'r');
    setGenericNode(&nodeQ,NULL,NULL,'r');
    setGenericNode(&nodeR,NULL,NULL,'r');
    setGenericNode(&nodeS,NULL,NULL,'r');
    setGenericNode(&nodeT,NULL,NULL,'r');
    setGenericNode(&nodeU,NULL,NULL,'r');
    setGenericNode(&nodeV,NULL,NULL,'r');
    setGenericNode(&nodeW,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&nodeA);
    addRecord(&root,&nodeB);
    addRecord(&root,&nodeC);
    addRecord(&root,&nodeD);
    addRecord(&root,&nodeE);
    addRecord(&root,&nodeF);
    addRecord(&root,&nodeG);
    addRecord(&root,&nodeH);
    addRecord(&root,&nodeI);
    addRecord(&root,&nodeJ);
    addRecord(&root,&nodeK);
    addRecord(&root,&nodeL);
    addRecord(&root,&nodeM);
    addRecord(&root,&nodeN);
    addRecord(&root,&nodeO);
    addRecord(&root,&nodeP);
    addRecord(&root,&nodeQ);
    addRecord(&root,&nodeR);
    addRecord(&root,&nodeS);
    addRecord(&root,&nodeT);
    addRecord(&root,&nodeU);
    addRecord(&root,&nodeV);
    addRecord(&root,&nodeW);
    
    findRoot = findRecord(root,((Record*)&nodeU)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&nodeU,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(recordA);
    destroyRecord(recordB);
    destroyRecord(recordC);
    destroyRecord(recordD);
    destroyRecord(recordE);
    destroyRecord(recordF);
    destroyRecord(recordG);
    destroyRecord(recordH);
    destroyRecord(recordI);
    destroyRecord(recordJ);
    destroyRecord(recordK);
    destroyRecord(recordL);
    destroyRecord(recordM);
    destroyRecord(recordN);
    destroyRecord(recordO);
    destroyRecord(recordP);
    destroyRecord(recordQ);
    destroyRecord(recordR);
    destroyRecord(recordS);
    destroyRecord(recordT);
    destroyRecord(recordU);
    destroyRecord(recordV);
    destroyRecord(recordW);
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

void test_genericFindRedBlackTree_find_nodeA_in_large_redBlackTree(void){
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
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&nodeA,NULL,NULL,'r');
    setGenericNode(&nodeB,NULL,NULL,'r');
    setGenericNode(&nodeC,NULL,NULL,'r');
    setGenericNode(&nodeD,NULL,NULL,'r');
    setGenericNode(&nodeE,NULL,NULL,'r');
    setGenericNode(&nodeF,NULL,NULL,'r');
    setGenericNode(&nodeG,NULL,NULL,'r');
    setGenericNode(&nodeH,NULL,NULL,'r');
    setGenericNode(&nodeI,NULL,NULL,'r');
    setGenericNode(&nodeJ,NULL,NULL,'r');
    setGenericNode(&nodeK,NULL,NULL,'r');
    setGenericNode(&nodeL,NULL,NULL,'r');
    setGenericNode(&nodeM,NULL,NULL,'r');
    setGenericNode(&nodeN,NULL,NULL,'r');
    setGenericNode(&nodeO,NULL,NULL,'r');
    setGenericNode(&nodeP,NULL,NULL,'r');
    setGenericNode(&nodeQ,NULL,NULL,'r');
    setGenericNode(&nodeR,NULL,NULL,'r');
    setGenericNode(&nodeS,NULL,NULL,'r');
    setGenericNode(&nodeT,NULL,NULL,'r');
    setGenericNode(&nodeU,NULL,NULL,'r');
    setGenericNode(&nodeV,NULL,NULL,'r');
    setGenericNode(&nodeW,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&nodeA);
    addRecord(&root,&nodeB);
    addRecord(&root,&nodeC);
    addRecord(&root,&nodeD);
    addRecord(&root,&nodeE);
    addRecord(&root,&nodeF);
    addRecord(&root,&nodeG);
    addRecord(&root,&nodeH);
    addRecord(&root,&nodeI);
    addRecord(&root,&nodeJ);
    addRecord(&root,&nodeK);
    addRecord(&root,&nodeL);
    addRecord(&root,&nodeM);
    addRecord(&root,&nodeN);
    addRecord(&root,&nodeO);
    addRecord(&root,&nodeP);
    addRecord(&root,&nodeQ);
    addRecord(&root,&nodeR);
    addRecord(&root,&nodeS);
    addRecord(&root,&nodeT);
    addRecord(&root,&nodeU);
    addRecord(&root,&nodeV);
    addRecord(&root,&nodeW);
    
    findRoot = findRecord(root,((Record*)&nodeA)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&nodeA,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(recordA);
    destroyRecord(recordB);
    destroyRecord(recordC);
    destroyRecord(recordD);
    destroyRecord(recordE);
    destroyRecord(recordF);
    destroyRecord(recordG);
    destroyRecord(recordH);
    destroyRecord(recordI);
    destroyRecord(recordJ);
    destroyRecord(recordK);
    destroyRecord(recordL);
    destroyRecord(recordM);
    destroyRecord(recordN);
    destroyRecord(recordO);
    destroyRecord(recordP);
    destroyRecord(recordQ);
    destroyRecord(recordR);
    destroyRecord(recordS);
    destroyRecord(recordT);
    destroyRecord(recordU);
    destroyRecord(recordV);
    destroyRecord(recordW);
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

void test_genericFindRedBlackTree_find_nodeW_in_large_redBlackTree(void){
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
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&nodeA,NULL,NULL,'r');
    setGenericNode(&nodeB,NULL,NULL,'r');
    setGenericNode(&nodeC,NULL,NULL,'r');
    setGenericNode(&nodeD,NULL,NULL,'r');
    setGenericNode(&nodeE,NULL,NULL,'r');
    setGenericNode(&nodeF,NULL,NULL,'r');
    setGenericNode(&nodeG,NULL,NULL,'r');
    setGenericNode(&nodeH,NULL,NULL,'r');
    setGenericNode(&nodeI,NULL,NULL,'r');
    setGenericNode(&nodeJ,NULL,NULL,'r');
    setGenericNode(&nodeK,NULL,NULL,'r');
    setGenericNode(&nodeL,NULL,NULL,'r');
    setGenericNode(&nodeM,NULL,NULL,'r');
    setGenericNode(&nodeN,NULL,NULL,'r');
    setGenericNode(&nodeO,NULL,NULL,'r');
    setGenericNode(&nodeP,NULL,NULL,'r');
    setGenericNode(&nodeQ,NULL,NULL,'r');
    setGenericNode(&nodeR,NULL,NULL,'r');
    setGenericNode(&nodeS,NULL,NULL,'r');
    setGenericNode(&nodeT,NULL,NULL,'r');
    setGenericNode(&nodeU,NULL,NULL,'r');
    setGenericNode(&nodeV,NULL,NULL,'r');
    setGenericNode(&nodeW,NULL,NULL,'r');
    
    Node *root = NULL; 
    addRecord(&root,&mainNode);
    addRecord(&root,&nodeA);
    addRecord(&root,&nodeB);
    addRecord(&root,&nodeC);
    addRecord(&root,&nodeD);
    addRecord(&root,&nodeE);
    addRecord(&root,&nodeF);
    addRecord(&root,&nodeG);
    addRecord(&root,&nodeH);
    addRecord(&root,&nodeI);
    addRecord(&root,&nodeJ);
    addRecord(&root,&nodeK);
    addRecord(&root,&nodeL);
    addRecord(&root,&nodeM);
    addRecord(&root,&nodeN);
    addRecord(&root,&nodeO);
    addRecord(&root,&nodeP);
    addRecord(&root,&nodeQ);
    addRecord(&root,&nodeR);
    addRecord(&root,&nodeS);
    addRecord(&root,&nodeT);
    addRecord(&root,&nodeU);
    addRecord(&root,&nodeV);
    addRecord(&root,&nodeW);
    
    findRoot = findRecord(root,((Record*)&nodeW)->memory); 
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&nodeW,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(recordA);
    destroyRecord(recordB);
    destroyRecord(recordC);
    destroyRecord(recordD);
    destroyRecord(recordE);
    destroyRecord(recordF);
    destroyRecord(recordG);
    destroyRecord(recordH);
    destroyRecord(recordI);
    destroyRecord(recordJ);
    destroyRecord(recordK);
    destroyRecord(recordL);
    destroyRecord(recordM);
    destroyRecord(recordN);
    destroyRecord(recordO);
    destroyRecord(recordP);
    destroyRecord(recordQ);
    destroyRecord(recordR);
    destroyRecord(recordS);
    destroyRecord(recordT);
    destroyRecord(recordU);
    destroyRecord(recordV);
    destroyRecord(recordW);
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
