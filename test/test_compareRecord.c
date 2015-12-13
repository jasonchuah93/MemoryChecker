#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "MemoryBlocks.h"
#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

void setUp(void){}
void tearDown(void){}

void test_findRecordCompare_should_return_1_if_address_of_recordInRedBlackTree_is_larger_than_address_of_targetMemory(void){
	Record record = {.memoryAddr = (void*)100};
    Node *node = (Node*)&record;
    char *targetMemory = (void*)50;
    compare = findRecordCompare(&node,targetMemory);
    TEST_ASSERT_EQUAL(1,compare);
}
/*
void test_findRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetMemory(void){
	Record record = {.memoryAddr= (void*)100};
    Node *node = (Node*)&record;
    char *targetMemory = (void*)150;
    compare = findRecordCompare(&node,targetMemory);
    TEST_ASSERT_EQUAL(-1,compare);
}    

void test_findRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetMemory(void){
    Record record = {.memoryAddr= (void*)100};
    Node *node = (Node*)&record;
    char *targetMemory = (void*)100;
    compare = findRecordCompare(&node,targetMemory);
    TEST_ASSERT_EQUAL(0,compare);
}

void test_addAndDelRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetRecord(void){
    Record recordFromRedBlackTree = {.memoryAddr= (void*)300};
    Record targetRecord = {.memoryAddr = (void*)200};
    Node *node = (Node*)&recordFromRedBlackTree;
    compare = addAndDelRecordCompare(&node,&targetRecord);
    TEST_ASSERT_EQUAL(1,compare);
}

void test_addAndDelRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetRecord(void){
    Record recordFromRedBlackTree = {.memoryAddr= (void*)100};
    Record targetRecord = {.memoryAddr = (void*)200};
    Node *node = (Node*)&recordFromRedBlackTree;
    compare = addAndDelRecordCompare(&node,&targetRecord);
    TEST_ASSERT_EQUAL(-1,compare);
}

void test_addAndDelRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetRecord(void){
    Record recordFromRedBlackTree = {.memoryAddr= (void*)200};
    Record targetRecord = {.memoryAddr = (void*)200};
    Node *node = (Node*)&recordFromRedBlackTree;
    compare = addAndDelRecordCompare(&node,&targetRecord);
    TEST_ASSERT_EQUAL(0,compare);
}
*/