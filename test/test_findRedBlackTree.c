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
    TEST_ASSERT_EQUAL(&mainNode,findRoot);
}

void test_genericFindRedBlackTree_find_leftNode_in_redBlackTree(void){
    char buffer[20],buffer2[30];
    Node *findRoot=NULL;
    Record *leftRecord = createRecord(buffer,30);
    Record *mainRecord = createRecord(buffer,20);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    setGenericNode(&mainNode,NULL,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    
    Node *root = &mainNode; 
    addRecord(&root,&leftNode);
    findRoot = findRecord(root,((Record*)&leftNode)->memory); 
    TEST_ASSERT_EQUAL(&leftNode,findRoot);
}
