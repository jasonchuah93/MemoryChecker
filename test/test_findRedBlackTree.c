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
#include "safeMalloc.h"
#include "safeFree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

/*****************************************

	1 NODE TEST

*******************************************/
/**
*    root              
*     |     find n200  
*     v     -------->  Found and return 1
*    n200              
**/
void test_findRecord_find_n200_in_root_should_return_1_if_found(void){
	initializePool();
	Node *targetNode;
	char *allocatedMemory;
	int compare ; 
	MemoryBlock2 ptrBlock = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock.memory))-50);
	allocatedMemory =(char*)safeMalloc(200);
	
	//targetNode = findRecord(&allocatedPool,allocatedMemory);
	compare = find(&allocatedPool,allocatedMemory);
	
	//TEST_ASSERT_EQUAL(targetNode,allocatedPool);
	TEST_ASSERT_EQUAL(compare,1);
	
	_free_Expect(allocatedMemory);
    freeMemory(allocatedMemory);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

/*****************************************

	2 NODE TEST

*******************************************/
/**
*    root              root
*     |     find n100   |
*     v     -------->   v
*    n200              n200	    
*    /  \              / \
*  n100  n300            n100 <---found and return 1
**/
void test_find_find_n100_in_root_should_return_1_if_found(void){
	initializePool();
	Node *targetNode;
	ErrorCode e;
	int compare ; 
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 =(char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	
	compare = find(&allocatedPool,allocatedMemory100);
	
	TEST_ASSERT_EQUAL(compare,1);
	
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

void test_findRecord_find_random_record_not_in_root_should_throw_error(void){
	initializePool();
	Node *targetNode,*targetNode2;
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*randomAddr;
	
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock2 ptrBlock2 = {.header[49] = "##########" , .memory[199] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock3 ptrBlock3 = {.header[49] = "##########" , .memory[299] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock4 ptrBlock4 = {.header[49] = "##########" , .memory[399] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	MemoryBlock5 ptrBlock5 = {.header[49] = "##########" , .memory[499] = "abcdef", .footer[49] = "$$$$$$$$$$"};
	
	randomAddr = (char*)80;
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),((char*)sizeof(ptrBlock3.memory))-50);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),((char*)sizeof(ptrBlock2.memory))-50);
	allocatedMemory200 =(char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+400+FOOTER_SIZE)),((char*)sizeof(ptrBlock4.memory))-50);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),((char*)sizeof(ptrBlock1.memory))-50);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		targetNode = findRecord(&allocatedPool,randomAddr);
		TEST_FAIL_MESSAGE("Should not free address not in pool");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	
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
	_free_Expect(freePool);
    freeMemory(freePool);
}