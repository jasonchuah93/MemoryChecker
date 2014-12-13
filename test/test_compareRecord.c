#include "unity.h"
#include "InitNode.h"
#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

Node node1,node2;

void setUp(void){}

void tearDown(void){}

void test_findRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetMemory(void){
	char buffer[20]; char buffer2[10];
    int compare=0;
    Record *record = createRecord(buffer,200);
    char *targetMemory = buffer2;
    
    compare = findRecordCompare((Node*)record,targetMemory);
    TEST_ASSERT_EQUAL(1,compare);
}

void test_findRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetMemory(void){
	char buffer[20]; char buffer2[10];
    int compare=0;
    Record *record = createRecord(buffer2,200);
    char *targetMemory = buffer;
    
    compare = findRecordCompare((Node*)record,targetMemory);
    TEST_ASSERT_EQUAL(-1,compare);
}    

void test_findRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetMemory(void){
	char buffer[20];
    int compare=0;
    Record *record = createRecord(buffer,200);
    char *targetMemory = buffer;
    
    compare = findRecordCompare((Node*)record,targetMemory);
    TEST_ASSERT_EQUAL(0,compare);
}


void test_addAndDelRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetRecord(void){
    char buffer[20]; char buffer2[10];
    int compare=0;
    Record *recordFromRedBlackTree = createRecord(buffer,300);
    Record *targetRecord = createRecord(buffer2,200);
    
    compare = addAndDelRecordCompare((Node*)recordFromRedBlackTree,targetRecord);
    TEST_ASSERT_EQUAL(1,compare);
}

void test_addAndDelRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetRecord(void){
    char buffer[20]; char buffer2[10];
    int compare=0;
    Record *recordFromRedBlackTree = createRecord(buffer2,300);
    Record *targetRecord = createRecord(buffer,200);
    
    compare = addAndDelRecordCompare((Node*)recordFromRedBlackTree,targetRecord);
    TEST_ASSERT_EQUAL(-1,compare);
}

void test_addAndDelRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetRecord(void){
    char buffer[20];
    int compare=0;
    Record *recordFromRedBlackTree = createRecord(buffer,300);
    Record *targetRecord = createRecord(buffer,200);
    
    compare = addAndDelRecordCompare((Node*)recordFromRedBlackTree,targetRecord);
    TEST_ASSERT_EQUAL(0,compare);
}
