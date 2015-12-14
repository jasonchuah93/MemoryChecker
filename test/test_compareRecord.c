#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "MemoryRecord.h"
#include "mock_MallocWrapper.h"
#include "Node.h"
#include "CustomAssertions.h"
#include "compareRecord.h"

void setUp(void){}
void tearDown(void){}

void test_findRecordCompare_should_return_1_if_address_of_recordInRedBlackTree_is_larger_than_address_of_targetMemory(void){
	int compare;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    MemoryBlock2 ptrBlock2 = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
    
    ptrRecord = createRecord(200,&block2);
    ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,&block1);
    
    TEST_ASSERT_EQUAL(1,compare);
}

void test_findRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetMemory(void){
	int compare;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    MemoryBlock2 ptrBlock2 = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
    
    ptrRecord = createRecord(100,&block1);
    ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,&block2);
    
    TEST_ASSERT_EQUAL(-1,compare);
}    

void test_findRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetMemory(void){
    int compare;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    
    ptrRecord = createRecord(100,&block1);
    ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,&block1);
    
    TEST_ASSERT_EQUAL(0,compare);
}

void test_addAndDelRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetRecord(void){
    int compare;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    MemoryBlock2 ptrBlock2 = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
    
    ptrRecord = createRecord(200,&block2);
    ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,&block1);
    
    TEST_ASSERT_EQUAL(1,compare);
}

void test_addAndDelRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetRecord(void){
    int compare;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    MemoryBlock2 ptrBlock2 = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
    
    ptrRecord = createRecord(100,&block1);
    ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,&block2);
    
    TEST_ASSERT_EQUAL(-1,compare);
}

void test_addAndDelRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetRecord(void){
    int compare;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    
    ptrRecord = createRecord(100,&block1);
    ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,&block1);
    
    TEST_ASSERT_EQUAL(0,compare);
}
