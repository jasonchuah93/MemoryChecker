#include "unity.h"
#include "InitNode.h"
#include "Node.h"
#include "MemoryRecord.h"

Node nodeParent,nodeLeftChildren,nodeRightChilder;
Record *memoryFromRedBlackTree;
Record *memory;

void setUp(void){}

void tearDown(void){}

#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

void test_createRecord_should_take_in_information_and_return_in_record_type(void){
    Record *record ;
    char *memory = "5A5A5A";
    record = createRecord(memory,100);
    TEST_ASSERT_EQUAL_STRING("5A5A5A",record->memory);
    TEST_ASSERT_EQUAL(100,record->size);
    TEST_ASSERT_EQUAL(19,record->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",record->fileName);
}

void test_findRecordCompare_should_return_1_if_memory_is_smaller_than_memoryFromRedBlackTree(void){
	char *memory = (char*)0x123;
	Record record = {.memory=(char*)0x456};
    
	TEST_ASSERT_EQUAL(1,findRecordCompare(&record,memory));
}

void test_findRecordCompare_should_return_negative_1_if_memory_is_larger_than_memoryFromRedBlackTree(void){
	char *memory = (char*)0x1234;
	Record record ={.memory=(char*)0x789};
	
	TEST_ASSERT_EQUAL(-1,findRecordCompare(&record,memory));
}

void xtest_findRecordCompare_should_return_0_if_memory_is_equal_than_memoryFromRedBlackTree(void){
	char *memory = (char*)0x456;
	Record record ={.memory=(char*)0x456};
	
	TEST_ASSERT_EQUAL(0,findRecordCompare(&record,memory));
}

void test_addDelRecordCompare_should_return_1_if_memory_is_smaller_than_memoryFromRedBlackTree(void){
	int compare;
    memoryFromRedBlackTree =createRecord("0x123",500);
    memory = createRecord("0x489",100);
	genericResetNode(&nodeParent,memoryFromRedBlackTree);
    genericResetNode(&nodeLeftChildren,memory);
    Node *root = &nodeParent;
    compare = addDelRecordCompare((void*)&root,&nodeLeftChildren);
    
    TEST_ASSERT_EQUAL(1,compare);
}

void test_addDelRecordCompare_should_return_negative_1_if_memory_is_larger_than_memoryFromRedBlackTree(void){
	int compare;
    memoryFromRedBlackTree =createRecord("0x123456",50);
    memory = createRecord("0x4891000004441",100);
	genericResetNode(&nodeParent,memoryFromRedBlackTree);
    genericResetNode(&nodeLeftChildren,memory);
    Node *root = &nodeParent;
    compare = addDelRecordCompare((void*)&root,&nodeLeftChildren);
    
    TEST_ASSERT_EQUAL(-1,compare);
}

void test_addDelRecordCompare_should_return_0_if_memory_is_equal_than_memoryFromRedBlackTree(void){
	int compare;
    memoryFromRedBlackTree =createRecord("0x123",100);
    memory = createRecord("0x123",100);
	genericResetNode(&nodeParent,memoryFromRedBlackTree);
    genericResetNode(&nodeLeftChildren,memory);
    Node *root = &nodeParent;
    compare = addDelRecordCompare((void*)&root,&nodeLeftChildren);
    
    TEST_ASSERT_EQUAL(0,compare);
}



