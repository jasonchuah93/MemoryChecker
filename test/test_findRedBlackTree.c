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
	MemoryBlock2 ptrBlock = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
	_malloc_ExpectAndReturn((HEADER_SIZE+200+FOOTER_SIZE),(char*)ptrBlock.header);
	allocatedMemory =(char*)safeMalloc(200);
	
	compare = find(&allocatedPool,allocatedMemory);
	
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
	
	MemoryBlock1 ptrBlock1 = {.header[49] = HEADERCONTENT , .memory[99] = "abcdef", .footer[49] = FOOTERCONTENT};
	MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
	MemoryBlock3 ptrBlock3 = {.header[49] = HEADERCONTENT, .memory[299] = "abcdef", .footer[49] = FOOTERCONTENT};
	
	_malloc_ExpectAndReturn((HEADER_SIZE+200+FOOTER_SIZE),(char*)ptrBlock2.header);
	allocatedMemory200 =(char*)safeMalloc(200);
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((HEADER_SIZE+300+FOOTER_SIZE),(char*)ptrBlock3.header);
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

