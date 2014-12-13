#include "unity.h"
#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

char buffer[20],buffer2[100]; int compare=0;

void setUp(void){}

void tearDown(void){}

void test_findRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetMemory(void){
	Record *record = createRecord(buffer2,200);
    char *targetMemory = buffer;
    
    compare = findRecordCompare((Node*)record,targetMemory);
    TEST_ASSERT_EQUAL(1,compare);
}

void test_findRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetMemory(void){
	Record *record = createRecord(buffer,200);
    char *targetMemory = buffer2;
    
    compare = findRecordCompare((Node*)record,targetMemory);
    TEST_ASSERT_EQUAL(-1,compare);
}    

void test_findRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetMemory(void){
    Record *record = createRecord(buffer,200);
    char *targetMemory = buffer;
    
    compare = findRecordCompare((Node*)record,targetMemory);
    TEST_ASSERT_EQUAL(0,compare);
}


void test_addAndDelRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetRecord(void){
    Record *recordFromRedBlackTree = createRecord(buffer2,300);
    Record *targetRecord = createRecord(buffer,200);
    
    compare = addAndDelRecordCompare((Node*)recordFromRedBlackTree,targetRecord);
    TEST_ASSERT_EQUAL(1,compare);
}

void test_addAndDelRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetRecord(void){
    Record *recordFromRedBlackTree = createRecord(buffer,300);
    Record *targetRecord = createRecord(buffer2,200);
    
    compare = addAndDelRecordCompare((Node*)recordFromRedBlackTree,targetRecord);
    TEST_ASSERT_EQUAL(-1,compare);
}

void test_addAndDelRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetRecord(void){
    Record *recordFromRedBlackTree = createRecord(buffer,300);
    Record *targetRecord = createRecord(buffer,200);
    
    compare = addAndDelRecordCompare((Node*)recordFromRedBlackTree,targetRecord);
    TEST_ASSERT_EQUAL(0,compare);
}
