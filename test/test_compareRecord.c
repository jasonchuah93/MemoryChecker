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

void test_findAndRemoveRecordCompare_should_return_1_if_address_of_recordInRedBlackTree_is_larger_than_address_of_targetMemory(void){
	int compare;
    char *targetMemory = (void*)100;
	MemoryBlock2 ptrBlock = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock.memory)};
	Record *ptrRecord = createRecord(200,&block);
    Node *ptrNode = createNode(ptrRecord);
    compare = findAndRemoveRecordCompare(&ptrNode,targetMemory);
    
    TEST_ASSERT_EQUAL(1,compare);
	
	 _free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
}

void test_findAndRemoveRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetMemory(void){
	int compare;
	char *targetMemory = (void*)300;
    MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
	Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock.memory)};
    Record *ptrRecord = createRecord(100,&block);
    Node *ptrNode = createNode(ptrRecord);
    
	compare = findAndRemoveRecordCompare(&ptrNode,targetMemory);
    
    TEST_ASSERT_EQUAL(-1,compare);
	
	_free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
}    

void test_findAndRemoveRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetMemory(void){
    int compare;
    char *targetMemory = (void*)100;
    MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock.memory)};
    Record *ptrRecord = createRecord(100,&block);
    Node *ptrNode = createNode(ptrRecord);
    
	compare = findAndRemoveRecordCompare(&ptrNode,targetMemory);
    
    TEST_ASSERT_EQUAL(0,compare);
	
	_free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
}

void test_addRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetRecord(void){
    int compare;
    Record *ptrRecord1,*ptrRecord2;
    Node *ptrNode1,*ptrNode2;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    MemoryBlock2 ptrBlock2 = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    ptrRecord1 = createRecord(100,&block1);
    ptrNode1 = createNode(ptrRecord1);
    
	Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
	ptrRecord2 = createRecord(200,&block2);
    ptrNode2 = createNode(ptrRecord2);
    
	compare = addRecordCompare(&ptrNode2,ptrNode1);
    
    TEST_ASSERT_EQUAL(1,compare);
	
	_free_Expect(ptrRecord1);
    freeMemory(ptrRecord1);
	 _free_Expect(ptrNode1);
    freeMemory(ptrNode1);
	_free_Expect(ptrRecord2);
    freeMemory(ptrRecord2);
	 _free_Expect(ptrNode2);
    freeMemory(ptrNode2);
}

void test_addRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetRecord(void){
	int compare;
    Record *ptrRecord1,*ptrRecord2;
    Node *ptrNode1,*ptrNode2;
    MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    MemoryBlock2 ptrBlock2 = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	
    Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    ptrRecord1 = createRecord(100,&block1);
    ptrNode1 = createNode(ptrRecord1);
    
	Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
	ptrRecord2 = createRecord(200,&block2);
    ptrNode2 = createNode(ptrRecord2);
    
	compare = addRecordCompare(&ptrNode1,ptrNode2);
    
    TEST_ASSERT_EQUAL(-1,compare);
	
	_free_Expect(ptrRecord1);
    freeMemory(ptrRecord1);
	 _free_Expect(ptrNode1);
    freeMemory(ptrNode1);
	_free_Expect(ptrRecord2);
    freeMemory(ptrRecord2);
	 _free_Expect(ptrNode2);
    freeMemory(ptrNode2);
}

void test_addRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetRecord(void){
    int compare;
	
	MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock.memory)};
    Record *ptrRecord = createRecord(100,&block);
    Node *ptrNode = createNode(ptrRecord);
    
	MemoryBlock1 ptrBlock2 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
    Record *ptrRecord2 = createRecord(100,&block2);
    Node *ptrNode2 = createNode(ptrRecord2);
    
	compare = addRecordCompare(&ptrNode,ptrNode2);
    
    TEST_ASSERT_EQUAL(0,compare);
	
	_free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
	_free_Expect(ptrRecord2);
    freeMemory(ptrRecord2);
	 _free_Expect(ptrNode2);
    freeMemory(ptrNode2);
}
