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

void setUp(void){}
void tearDown(void){}

#define leftPool allocatedPool->left
#define leftChildPool allocatedPool->left->left
#define leftRightChildPool allocatedPool->left->right
#define rightPool allocatedPool->right
#define rightChildPool allocatedPool->right->right
#define rightLeftChildPool allocatedPool->right->left


void test_safeMallocTest_allocate_size_100_should_create_record_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory;
	MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock.memory))-50);
	allocatedMemory =(char*)safeMallocTest(100);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(50,allocatedMemory-50);
	TEST_ASSERT_EQUAL(100,allocatedMemory);
	TEST_ASSERT_EQUAL(200,allocatedMemory+100);
	TEST_ASSERT_EQUAL(100,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',allocatedPool);
	
	_free_Expect(allocatedMemory);
    freeMemory(allocatedMemory);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_100_and_200_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(100,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(200,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(NULL,rightPool,'b',allocatedPool);
	
	//printf("root address : %d \n",memoryAddr(allocatedPool));
	//printf("right address : %d \n",memoryAddr(rightPool));
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_200_and_100_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_200_and_100_and_300_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "%%%%%%%%%%" , .memory[299] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(300,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_200_and_300_and_100_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "%%%%%%%%%%" , .memory[299] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(300,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_200_and_300_and_400_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory200,*allocatedMemory300,*allocatedMemory400;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "@@@@@@@@@@" , .memory[299] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMallocTest(400);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(300,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(200,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(400,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_400_and_300_and_200_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory200,*allocatedMemory300,*allocatedMemory400;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "@@@@@@@@@@" , .memory[299] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMallocTest(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(300,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(200,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(400,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_300_and_100_and_200_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "%%%%%%%%%%" , .memory[299] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(300,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_100_and_400_and_200_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory400;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMallocTest(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(400,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_400_and_200_and_300_and_100_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "@@@@@@@@@@" , .memory[299] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMallocTest(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(300,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(200,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(400,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftChildPool));
	
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftChildPool);
	TEST_ASSERT_EQUAL_NODE(allocatedPool->left->left,NULL,'b',leftPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeMallocTest_allocate_size_500_400_and_200_and_300_and_100_should_create_descriptor_and_add_into_allocated_pool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "@@@@@@@@@@" , .memory[299] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "%%%%%%%%%%" , .memory[499] = "abcdef123456789", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+500+FOOTER_SIZE)),((char*)sizeof(ptrBlock5.memory))-50);
	allocatedMemory500 = (char*)safeMallocTest(500);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMallocTest(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMallocTest(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMallocTest(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMallocTest(100);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(400,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(300,memorySize(rightLeftChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL(500,memorySize(rightChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightChildPool));
	
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightChildPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightLeftChildPool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(rightLeftChildPool,rightChildPool,'b',rightPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

