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
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

//AllocatedPool
#define leftPool allocatedPool->left
#define leftChildPool allocatedPool->left->left
#define leftRightChildPool allocatedPool->left->right
#define rightPool allocatedPool->right
#define rightChildPool allocatedPool->right->right
#define rightLeftChildPool allocatedPool->right->left
//FreePool
#define leftFreePool freePool->left
#define rightFreePool freePool->right
#define rightLeftChildFreePool freePool->right->left

/********************************************
All the tests here are using memory size to 
compare each record in red black tree in
allocated pool and move to free pool
********************************************/

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFreeTest(allocatedMemory400);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory400);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice_right_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFreeTest(allocatedMemory600);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory600);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice_left_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFreeTest(allocatedMemory300);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	TEST_ASSERT_EQUAL_NODE(NULL,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory300);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice_leftChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFreeTest(allocatedMemory100);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory100);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice_leftRightChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	
	safeFreeTest(allocatedMemory300);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory300);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice_rightChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFreeTest(allocatedMemory600);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory600);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_same_address_twice_rightLeftChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	
	safeFreeTest(allocatedMemory400);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory400);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_n800_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "@@@@@@@@@@" , .memory[499] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock7 ptrBlock7 = {.header[49] = "%%%%%%%%%%" , .memory[699] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock8 ptrBlock8 = {.header[49] = "%%%%%%%%%%" , .memory[799] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+700+FOOTER_SIZE)),((char*)sizeof(ptrBlock7.memory))-50);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),((char*)sizeof(ptrBlock8.memory))-50);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFreeTest(allocatedMemory800);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory800);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_n600_and_n100_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "@@@@@@@@@@" , .memory[499] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock7 ptrBlock7 = {.header[49] = "%%%%%%%%%%" , .memory[699] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock8 ptrBlock8 = {.header[49] = "%%%%%%%%%%" , .memory[799] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+700+FOOTER_SIZE)),((char*)sizeof(ptrBlock7.memory))-50);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),((char*)sizeof(ptrBlock8.memory))-50);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFreeTest(allocatedMemory600);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	safeFreeTest(allocatedMemory100);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL_NODE(leftFreePool,NULL,'b',freePool);
	
	
	Try{
		safeFreeTest(allocatedMemory100);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_n100_then_n400_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "@@@@@@@@@@" , .memory[499] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock7 ptrBlock7 = {.header[49] = "%%%%%%%%%%" , .memory[699] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock8 ptrBlock8 = {.header[49] = "%%%%%%%%%%" , .memory[799] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+700+FOOTER_SIZE)),((char*)sizeof(ptrBlock7.memory))-50);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),((char*)sizeof(ptrBlock8.memory))-50);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFreeTest(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	safeFreeTest(allocatedMemory400);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(rightChildPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightFreePool,'b',freePool);
	
	
	Try{
		safeFreeTest(allocatedMemory400);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_n100_n400_then_n800_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "@@@@@@@@@@" , .memory[499] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock7 ptrBlock7 = {.header[49] = "%%%%%%%%%%" , .memory[699] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock8 ptrBlock8 = {.header[49] = "%%%%%%%%%%" , .memory[799] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+700+FOOTER_SIZE)),((char*)sizeof(ptrBlock7.memory))-50);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),((char*)sizeof(ptrBlock8.memory))-50);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFreeTest(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	safeFreeTest(allocatedMemory400);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(rightChildPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightFreePool,'b',freePool);
	
	safeFreeTest(allocatedMemory800);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL_NODE(leftFreePool,rightFreePool,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory800);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_the_n100_n400_n800_then_n700_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "@@@@@@@@@@" , .memory[499] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock7 ptrBlock7 = {.header[49] = "%%%%%%%%%%" , .memory[699] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock8 ptrBlock8 = {.header[49] = "%%%%%%%%%%" , .memory[799] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+700+FOOTER_SIZE)),((char*)sizeof(ptrBlock7.memory))-50);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),((char*)sizeof(ptrBlock8.memory))-50);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFreeTest(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	safeFreeTest(allocatedMemory400);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(rightChildPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightFreePool,'b',freePool);
	
	safeFreeTest(allocatedMemory800);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL_NODE(leftFreePool,rightFreePool,'b',freePool);
	
	safeFreeTest(allocatedMemory700);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory600,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL(allocatedMemory800,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL(allocatedMemory700,memoryAddr(rightLeftChildFreePool));
	TEST_ASSERT_EQUAL_NODE(leftFreePool,rightFreePool,'b',freePool);
	
	Try{
		safeFreeTest(allocatedMemory700);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_free_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory;
	MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock.memory))-50);
	allocatedMemory = (char*)safeMalloc(100);
	safeFreeTest(allocatedMemory);
	
	TEST_ASSERT_NULL(allocatedPool);
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory);
    freeMemory(allocatedMemory);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_throw_error_if_free_null_allocatedPool(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory = (char*)500;
	
	Try{
		safeFreeTest(allocatedMemory);
		TEST_FAIL_MESSAGE("Should not free allocatedPool");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_POOL,e);
	}
}

void test_safeFreeTest_should_throw_error_if_free_address_not_in_the_allocatedPool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*randomAddr;
	randomAddr = (char*)350;
	ErrorCode e;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "@@@@@@@@@@" , .memory[399] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "##########" , .memory[499] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock6 ptrBlock6 = {.header[49] = "%%%%%%%%%%" , .memory[599] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),((char*)sizeof(ptrBlock6.memory))-50);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+500+FOOTER_SIZE)),((char*)sizeof(ptrBlock5.memory))-50);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	Try{
		safeFreeTest(randomAddr);
		TEST_FAIL_MESSAGE("Should not free address not in pool");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}


void test_safeFreeTest_should_throw_error_if_free_between_the_memoryAddr(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		safeFreeTest(allocatedMemory300+100);
		TEST_FAIL_MESSAGE("Should not free between address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFreeTest_should_throw_error_if_free_between_the_memoryAddr_on_left_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	Try{
		safeFreeTest(allocatedMemory100+50);
		TEST_FAIL_MESSAGE("Should not free between address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFreeTest_should_throw_error_if_free_header_address(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.memory);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.memory);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		safeFreeTest(allocatedMemory100-50);
		TEST_FAIL_MESSAGE("Should not free header address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFreeTest_should_throw_error_if_free_footer_address(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.memory);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.memory);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		safeFreeTest(allocatedMemory100+100);
		TEST_FAIL_MESSAGE("Should not free header address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFreeTest_should_free_left_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory500;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "##########" , .memory[499] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+500+FOOTER_SIZE)),((char*)sizeof(ptrBlock5.memory))-50);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	safeFreeTest(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightPool,'b',allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_free_right_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory500;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "##########" , .memory[499] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+500+FOOTER_SIZE)),((char*)sizeof(ptrBlock5.memory))-50);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	safeFreeTest(allocatedMemory500);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_free_n200_and_n100_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "%%%%%%%%%%" , .memory[299] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFreeTest(allocatedMemory200);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	safeFreeTest(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(leftFreePool,NULL,'b',freePool);
	//LeftFreePool
	TEST_ASSERT_NOT_NULL(leftFreePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftFreePool);
	
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

void test_safeFreeTest_should_free_root_only_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory400;
	MemoryBlock1 ptrBlock1 = {.header[49] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	
	safeFreeTest(allocatedMemory200);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	//LeftPool
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFreeTest_should_free_few_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "@@@@@@@@@@" , .memory[199] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "@@@@@@@@@@" , .memory[299] = "abcdef123", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "%%%%%%%%%%" , .memory[399] = "abcdef123456", .footer[49] = "&&&&&&&&&&"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "%%%%%%%%%%" , .memory[499] = "abcdef123456789", .footer[49] = "&&&&&&&&&&"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+500+FOOTER_SIZE)),((char*)sizeof(ptrBlock5.memory))-50);
	allocatedMemory500 = (char*)safeMalloc(500);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(200,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//LeftPool
	TEST_ASSERT_EQUAL(100,memorySize(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',leftPool);
	//RightPool
	TEST_ASSERT_EQUAL(400,memorySize(rightPool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(rightLeftChildPool,rightChildPool,'b',rightPool);
	TEST_ASSERT_EQUAL(300,memorySize(rightLeftChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL(500,memorySize(rightChildPool));
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightChildPool));
	
	//Remove n400 from allocatedPool
	safeFreeTest(allocatedMemory400);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//LeftPool
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',leftPool);
	//RightPool
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(rightLeftChildPool,NULL,'b',rightPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(rightLeftChildPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightLeftChildPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	//Remove n100 from allocatedPool
	safeFreeTest(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftFreePool);
	TEST_ASSERT_EQUAL_NODE(leftFreePool,NULL,'b',freePool);
	
	//Remove n200 from allocatedPool
	safeFreeTest(allocatedMemory200);
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightPool,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(rightFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftFreePool);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightFreePool);
	TEST_ASSERT_EQUAL_NODE(leftFreePool,rightFreePool,'b',freePool);
	
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
	_free_Expect(freePool);
    freeMemory(freePool);
}
