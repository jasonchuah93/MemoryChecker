#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "mock_MallocWrapper.h"
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"
#include "safeMalloc.h"
#include "safeFree.h"

void setUp(void){}
void tearDown(void){}

#define leftPool allocatedPool->left
#define leftChildPool allocatedPool->left->left
#define leftRightChildPool allocatedPool->left->right
#define rightPool allocatedPool->right
#define rightChildPool allocatedPool->right->right
#define rightLeftChildPool allocatedPool->right->left

void test_safeFree_should_free_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory;
	MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)sizeof(ptrBlock.header));
	allocatedMemory = (char*)safeMalloc(100);
	safeFree(allocatedMemory);
	
	TEST_ASSERT_NULL(allocatedPool);
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(100,memorySize(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory);
    freeMemory(allocatedMemory);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_left_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)sizeof(ptrBlock2.memory));
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)sizeof(ptrBlock1.memory));
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFree(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(100,memorySize(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_right_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)sizeof(ptrBlock1.memory));
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)sizeof(ptrBlock2.memory));
	allocatedMemory200 = (char*)safeMalloc(200);
	
	safeFree(allocatedMemory200);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(100,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(200,memorySize(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_n100_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "%%%%%%%%%%" , .memory[299] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)sizeof(ptrBlock2.memory));
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)sizeof(ptrBlock1.memory));
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),(char*)sizeof(ptrBlock3.memory));
	allocatedMemory300 = (char*)safeMalloc(300);
	
	safeFree(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(100,memorySize(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_n300_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "%%%%%%%%%%" , .memory[299] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)sizeof(ptrBlock2.memory));
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)sizeof(ptrBlock1.memory));
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),(char*)sizeof(ptrBlock3.memory));
	allocatedMemory300 = (char*)safeMalloc(300);
	
	safeFree(allocatedMemory300);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(300,memorySize(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}