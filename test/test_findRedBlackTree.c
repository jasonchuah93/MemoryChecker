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
void test_genericFindRedBlackTree_find_mainNode_in_redBlackTree(void){
    Node *findRoot=NULL;
    Node *root = NULL; 
    Record record = {.memory=(void*)100,.color='b'};
    addRecord(&root,(Node*)&record);
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_PTR((Node*)&record,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',(Node*)&record);
    
    //findRoot = findRecord(root,(Node*)&record); 
    //TEST_ASSERT_NOT_NULL(findRoot);
    //TEST_ASSERT_EQUAL(&mainNode,findRoot);
    
    destroyRecord(&record);
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