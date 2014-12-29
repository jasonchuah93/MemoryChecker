#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
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
    resetAllocatedPool();
    void *allocateRecord= safeMalloc(50);
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL_PTR(getMemory(allocatedPool),allocateRecord);
    TEST_ASSERT_EQUAL_STRING(allocateRecord-15,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(allocateRecord+50,"5A5A5A5A5A5A5A");
}

void test_write_content_into_header_block(void){
    ErrorCode e;
    resetAllocatedPool();
    void *allocateRecord = safeMalloc(50);
    strcpy(allocateRecord-9,"6A6A6A6A6A");
    Try{
        checkHeaderMemoryContent(allocateRecord);
        TEST_FAIL_MESSAGE("Should throw corrupted footer memory ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
    }
}

void test_write_content_exceed_into_footer_block(void){
    ErrorCode e;
    resetAllocatedPool();
    void *allocateRecord = safeMalloc(50);
    strcpy(allocateRecord+45,"6A6A6A6A6A");
    Try{
        checkFooterMemoryContent(allocateRecord);
        TEST_FAIL_MESSAGE("Should throw corrupted footer memory ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
    }
}

void test_safeMalloc_should_add_record_into_allocated_pool(void){
    resetAllocatedPool();
    void *allocateRecord = safeMalloc(50);
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(getMemory(allocatedPool),allocateRecord);
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+50);
}

void test_safeMalloc_should_add_two_records_into_allocated_pool(void){
    resetAllocatedPool();
    
    void *allocatedRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL(getMemory(allocatedPool),allocatedRecord);
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    
    allocatedRecord = safeMalloc(150);
    TEST_ASSERT_EQUAL(getMemory(allocatedPool->right),allocatedRecord);
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(150,getSize(allocatedPool->right));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    TEST_ASSERT_NULL(allocatedPool->right->left);
    TEST_ASSERT_NULL(allocatedPool->right->right);
}

void test_safeMalloc_should_add_three_record_into_allocated_pool(void){
    resetAllocatedPool();
    void *allocatedRecord = safeMalloc(50);
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatedPool));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    
    allocatedRecord = safeMalloc(70);
    
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    
    allocatedRecord = safeMalloc(100);
    TEST_ASSERT_EQUAL(allocatedRecord,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(70,getSize(allocatedPool));
}
/*
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
*/