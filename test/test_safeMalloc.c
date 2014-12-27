#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "mock_memoryAllocator.h"
#include "RestructureNode.h"
#include "redBlackTree.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_safeMalloc_should_return_null_if_the_size_input_is_0(void){
    void *allocatedRecord=NULL;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(0);
    TEST_ASSERT_NULL(safeMalloc(0));
}

void test_safeMalloc_should_throw_error_if_input_size_exceed_the_BUFFER_SIZE(void){
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
	void *allocatedRecord=NULL;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(200);
    
	TEST_ASSERT_NOT_NULL(allocatePool);
	TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL_STRING(allocatedRecord-15,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(allocatedRecord+200,"5A5A5A5A5A5A5A");
}



void test_write_content_into_header_block(void){
    ErrorCode e;
    void *allocatedRecord=NULL;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(50);
    strcpy(allocatedRecord-15,"6A6A6A6A6A");
    Try{
        checkMemoryContent(allocatedRecord);
        TEST_FAIL_MESSAGE("Should throw wrong header memory ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_MEMORY_WRONG,e);
    }
}

void test_write_content_exceed_into_footer_block(void){
    ErrorCode e;
    void *allocatedRecord=NULL;
    resetAllocatedPool();
    allocatedRecord = safeMalloc(50);
    strcpy(allocatedRecord+50,"6A6A6A6A6A");
    Try{
        checkMemoryContent(allocatedRecord);
        TEST_FAIL_MESSAGE("Should throw wrong header memory ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_MEMORY_WRONG,e);
    }
}

void test_safeFree_should_throw_error_if_free_null_pointer(void){   
    ErrorCode e;
    void *allocatedRecord = NULL;
    Try{
        safeFree(allocatedRecord);
        TEST_FAIL_MESSAGE("Should throw free NULL pointer ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_FREE_NULL_PTR,e);
    }
}

void test_safeFree_should_remove_record_from_allocate_pool_and_put_into_free_pool(void){
    void *allocatedRecord = NULL;
}

void test_safeMalloc_add_the_record_into_allocated_pool(void){
	void *allocatedRecord=NULL;
    resetAllocatedPool();
    allocatedRecord =safeMalloc(100);
    
    TEST_ASSERT_NOT_NULL(allocatePool);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL(100,getSize(allocatePool));
    TEST_ASSERT_NULL(allocatePool->left);
    TEST_ASSERT_NULL(allocatePool->right);
}

/*
void test_safeMalloc_add_the_2_records_into_allocated_pool_a(void){
    void *allocatedRecord=NULL;
    resetAllocatedPool();
    printf("test 2 record \n");
    allocatedRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatePool);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool));
    TEST_ASSERT_EQUAL(50,getSize(allocatePool));
    TEST_ASSERT_NULL(allocatePool->left);
    TEST_ASSERT_NULL(allocatePool->right);
    
    allocatedRecord =safeMalloc(150);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatePool->right));
    TEST_ASSERT_EQUAL(150,getSize(allocatePool->right));
    TEST_ASSERT_NULL(allocatePool->left);
    TEST_ASSERT_NOT_NULL(allocatePool->right);
    TEST_ASSERT_NULL(allocatePool->right->left);
    TEST_ASSERT_NULL(allocatePool->right->right);
}
*/