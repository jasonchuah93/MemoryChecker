#include "unity.h"
#include <stdlib.h>
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "memoryAllocator.h"
#include "RestructureNode.h"
#include "redBlackTree.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_safeMalloc_should_return_null_if_the_size_input_is_0(void){
    void *allocatedRecord ;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(0);
    TEST_ASSERT_NULL(safeMalloc(0));
}

void test_safeMalloc_should_throw_error_if_input_size_exceed_the_BUFFER_SIZE(void){
    printf("Test 2 \n");
    ErrorCode e;
    Try
	{
        safeMalloc(2000);
		TEST_FAIL_MESSAGE("Should throw exceed buffer size ");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_EXCEED_BUFFER_SIZE,e);
	}
    printf("************************************************************\n");
}


void test_safeMalloc_verify_the_content_of_header_and_footer(void){
	void *allocatedRecord ;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(200);
    
	TEST_ASSERT_NOT_NULL(allocatePool);
	TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL_STRING(allocatedRecord-15,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(allocatedRecord+200,"5A5A5A5A5A5A5A");
}

void test_safeMalloc_add_the_record_into_allocated_pool(void){
	void *allocatedRecord;
    resetAllocatedPool();
    allocatedRecord =safeMalloc(100);
    
    TEST_ASSERT_NOT_NULL(allocatePool);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL(100,getSize(allocatePool));
    TEST_ASSERT_NULL(allocatePool->left);
    TEST_ASSERT_NULL(allocatePool->right);
}

void test_safeMalloc_add_the_2_records_into_allocated_pool_a(void){
    void *allocatedRecord;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatePool);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL(50,getSize(allocatePool));
    TEST_ASSERT_NULL(allocatePool->left);
    TEST_ASSERT_NULL(allocatePool->right);
    
    allocatedRecord = safeMalloc(150);
    //TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool->right));
    //TEST_ASSERT_EQUAL(150,getSize(allocatePool->right));
    //TEST_ASSERT_NULL(allocatePool->left);
    //TEST_ASSERT_NOT_NULL(allocatePool->right);
    //TEST_ASSERT_NULL(allocatePool->right->left);
    //TEST_ASSERT_NULL(allocatePool->right->right);
}

/*
void test_safeMalloc_add_3_records_into_allocated_pool(void){
    void *allocatedRecord;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatePool);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL(50,getSize(allocatePool));
    TEST_ASSERT_NULL(allocatePool->left);
    TEST_ASSERT_NULL(allocatePool->right);
    
    allocatedRecord = safeMalloc(150);
    
}
*/

