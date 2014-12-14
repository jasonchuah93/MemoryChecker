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
    
    Node *root = &mainNode; 
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
    
    Node *root = &mainNode; 
    addRecord(&root,&rightNode);
    findRoot = findRecord(root,((Record*)&rightNode)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&rightNode,findRoot);
    
    destroyRecord(mainRecord);
    destroyRecord(rightRecord);
}

void test_genericFindRedBlackTree_find_leftNodeChild_in_leftNode_and_mainNode_redBlackTree(void){
    char buffer[20],buffer2[30],buffer3[40];
    Node *findRoot=NULL;
    Record *leftRecordChild = createRecord(buffer,20);
    Record *leftRecord = createRecord(buffer2,30);
    Record *mainRecord = createRecord(buffer3,40);
    resetGenericNode(&mainNode,mainRecord);
    resetGenericNode(&leftNode,leftRecord);
    resetGenericNode(&leftNodeChild,leftRecordChild);
    setGenericNode(&mainNode,&leftNode,NULL,'b');
    setGenericNode(&leftNode,NULL,NULL,'r');
    setGenericNode(&leftNodeChild,NULL,NULL,'r');
    
    Node *root = &mainNode; 
    addRecord(&root,&leftNodeChild);
    findRoot = findRecord(root,((Record*)&leftNodeChild)->memory); 
    
    TEST_ASSERT_NOT_NULL(findRoot);
    TEST_ASSERT_EQUAL(&leftNodeChild,findRoot);
    
    destroyRecord(leftRecordChild);
    destroyRecord(leftRecord);
    destroyRecord(mainRecord);
}


