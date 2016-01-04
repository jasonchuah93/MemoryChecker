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

MemoryBlock1 ptrBlock1 = {.header[49] = HEADERCONTENT , .memory[99] = "abcdef", .footer[49] = FOOTERCONTENT};
MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef123456", .footer[49] = FOOTERCONTENT};

void test_findRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetMemory(void){
	int compare;
    char *targetMemory = (void*)100;
	
	Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.memory)};
	Record *ptrRecord = createRecord(&block);
    Node *ptrNode = createNode(ptrRecord);
    compare = findRecordCompare(&ptrNode,targetMemory);
    
    TEST_ASSERT_EQUAL(1,compare);
	
	 _free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
}

void test_findRecordCompare_should_return_negative_1_if_recordInRedBlackTree_is_smaller_than_targetMemory(void){
	int compare;
	char *targetMemory = (void*)300;
    
	Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Record *ptrRecord = createRecord(&block);
    Node *ptrNode = createNode(ptrRecord);
    
	compare = findRecordCompare(&ptrNode,targetMemory);
    
    TEST_ASSERT_EQUAL(-1,compare);
	
	_free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
}    

void test_findRecordCompare_should_return_0_if_recordInRedBlackTree_is_equal_to_targetMemory(void){
    int compare;
    char *targetMemory = (void*)100;
    
    Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Record *ptrRecord = createRecord(&block);
    Node *ptrNode = createNode(ptrRecord);
    
	compare = findRecordCompare(&ptrNode,targetMemory);
    
    TEST_ASSERT_EQUAL(0,compare);
	
	_free_Expect(ptrRecord);
    freeMemory(ptrRecord);
	 _free_Expect(ptrNode);
    freeMemory(ptrNode);
}

void test_addRecordCompare_should_return_1_if_recordInRedBlackTree_is_larger_than_targetRecord(void){
    int compare;
    Allocation *ptr1,*ptr2;
	Record *ptrRecord1,*ptrRecord2;
    Node *ptrNode1,*ptrNode2;
    
    _malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	ptr1 = allocateMemory(100);
    ptrRecord1 = createRecord(ptr1);
    ptrNode1 = createNode(ptrRecord1);
    
	_malloc_ExpectAndReturn((HEADER_SIZE+200+FOOTER_SIZE),(char*)ptrBlock2.header);
	ptr2 = allocateMemory(200);
	ptrRecord2 = createRecord(ptr2);
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
    
    Allocation block1 = {.memoryAllocateAddr = (char*)ptrBlock1.memory};
    ptrRecord1 = createRecord(&block1);
    ptrNode1 = createNode(ptrRecord1);
    
	Allocation block2 = {.memoryAllocateAddr = (char*)ptrBlock2.memory};
	ptrRecord2 = createRecord(&block2);
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
	
	MemoryBlock1 ptrBlock = {.header[49] = HEADERCONTENT , .memory[99] = "abcdef", .footer[49] = FOOTERCONTENT};
    Allocation block = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.header)};
    Record *ptrRecord = createRecord(&block);
    Node *ptrNode = createNode(ptrRecord);
    
	MemoryBlock1 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[99] = "abcdef", .footer[49] = FOOTERCONTENT};
    Allocation block2 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock2.header)};
    Record *ptrRecord2 = createRecord(&block2);
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

