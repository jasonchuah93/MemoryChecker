#include "unity.h"
#include "MemoryRecord.h"
#include "Node.h"
#include "InitNode.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"

Node mainNode;

void setUp(void){}

void tearDown(void){}


void test_memoryManagerAddRecord_should_throw_error_if_the_record_is_empty(void){
    CEXCEPTION_T err;
    Try{
        memoryManagerAddRecord(NULL);
        TEST_FAIL_MESSAGE("Should throw ERR_EMPTY_RECORD");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_EMPTY_RECORD,err);
    }
    
    
}

void test_memoryManagerAddRecord_should_throw_error_if_the_root_is_not_empty(void){
    CEXCEPTION_T err;
    Record *record1 = createRecord("5A5A5A5A",100);
    setGenericNode(&mainNode,record1);
    Node *rootPtr = &mainNode;
    Record *record2 = createRecord("5A5A5A5A5A",110);
    Try{
        rootPtr=memoryManagerAddRecord(record2);
        TEST_FAIL_MESSAGE("Should throw ERR_RECORD_EXISTED");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_RECORD_EXISTED,err);
    }    
}
/*
void test_memoryManagerAddRecord_should_add_record_into_generic_red_black_tree_if_node_is_empty(void){
    Node *root=NULL; 
    Record *record = createRecord("5A5A5A",100);
    memoryManagerAddRecord(root,record);
    
    //TEST_ASSERT_NOT_NULL(root);
    Record *addRecord = (Record*)&rootPtr->dataPtr;
    //TEST_ASSERT_EQUAL_STRING("5A5A5A",addRecord->memory);
    //TEST_ASSERT_EQUAL(100,addRecord->size);
}
*/
