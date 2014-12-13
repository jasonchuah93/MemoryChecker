#include "unity.h"
#include "MemoryRecord.h"
#include "Node.h"
#include "InitNode.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node mainNode,subNode;

void setUp(void){}

void tearDown(void){}

void test_memoryManagerAddRecord_should_add_record_into_generic_red_black_tree_if_root_is_empty(void){
    Record *mainRecord = createRecord("5A5A5A",100);
    resetGenericNode(&mainNode,mainRecord);
    setNode(&mainNode,NULL,NULL,'b');
    Node *root = NULL;
    
    root = memoryManagerAddRecord((Record*)&mainNode);
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_NULL(root->left);
    TEST_ASSERT_NULL(root->right);
    TEST_ASSERT_EQUAL_PTR(root,&mainNode);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&mainNode);
    
    Record *readRecord = (Record*)root->dataPtr;
    TEST_ASSERT_EQUAL_STRING("5A5A5A",readRecord->memory);
    TEST_ASSERT_EQUAL(100,readRecord->size);
}

void test_memoryManagerAddRecord_should_add_record_into_sub_node_if_root_is_not_empty(void){
    Record *mainRecord = createRecord("5A5A5A",100);
    resetGenericNode(&mainNode,mainRecord);
    setNode(&mainNode,NULL,NULL,'b');
    Record *subRecord = createRecord("5A5A",50);
    resetGenericNode(&subNode,subRecord);
    setNode(&subNode,NULL,NULL,'r');
    Node *root = &mainNode;
    
    root = memoryManagerAddRecord((Record*)&subNode);
    //TEST_ASSERT_NOT_NULL(root);
    //TEST_ASSERT_EQUAL_PTR(root,&mainNode);
    //TEST_ASSERT_EQUAL_PTR(root->left,&subNode);
}


