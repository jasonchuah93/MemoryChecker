#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "MallocWrapper.h"
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"
#include "safeMalloc.h"
#include "safeFree.h"
#include "safeSummary.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_safeMalloc_should_allocate_size_15_and_move_into_allocatedPool(void){
	initializePool();
	//MemoryBlock15 ptrBlock = {.memory[14] = "abcdef"};
	char *allocated15;
	allocated15 = (char*)safeMalloc(15);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(15,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL_STRING(HEADERCONTENT,allocated15-50);
	TEST_ASSERT_EQUAL_STRING(FOOTERCONTENT,allocated15+15);
	
	freeMemory(allocated15);
}
/*
void test_safeMalloc_should_allocate_size_15_and_safeFree_to_freePool(void){
	initializePool();
	char *allocated15;
	MemoryBlock15 ptrBlock = {.header[49] = HEADERCONTENT , .memory[9] = "abcdef", .footer[49] = FOOTERCONTENT};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+15+FOOTER_SIZE)),(char*)ptrBlock.header);
	allocated15 = (char*)safeMalloc(15);
	
	safeFree(allocated15);
	
	TEST_ASSERT_NULL(allocatedPool);
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(15,memorySize(freePool));
	TEST_ASSERT_EQUAL_STRING(HEADERCONTENT,allocated15-50);
	TEST_ASSERT_EQUAL_STRING(FOOTERCONTENT,allocated15+15);
}

void test_safeMalloc_should_allocate_size_15_and_safeSummary_to_check_for_error(void){
	initializePool();
	char *allocated15;
	MemoryBlock15 ptrBlock = {.header[49] = HEADERCONTENT , .memory[9] = "abcdef", .footer[49] = FOOTERCONTENT};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+15+FOOTER_SIZE)),(char*)ptrBlock.header);
	allocated15 = (char*)safeMalloc(15);
	
	safeSummary();
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(15,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL_STRING(HEADERCONTENT,allocated15-50);
	TEST_ASSERT_EQUAL_STRING(FOOTERCONTENT,allocated15+15);
}

void test_safeMalloc_should_allocate_size_15_safeFree_to_freePool_and_safeSummary_to_check_for_error(void){
	initializePool();
	char *allocated15;
	MemoryBlock15 ptrBlock = {.header[49] = HEADERCONTENT , .memory[9] = "abcdef", .footer[49] = FOOTERCONTENT};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+15+FOOTER_SIZE)),(char*)ptrBlock.header);
	allocated15 = (char*)safeMalloc(15);
	
	safeFree(allocated15);
	safeSummary();
}
*/