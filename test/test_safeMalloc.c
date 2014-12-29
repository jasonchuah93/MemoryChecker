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
    
    void *allocateRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(getMemory(allocatedPool),allocateRecord);
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+50);
    
    allocateRecord = safeMalloc(150);
    TEST_ASSERT_EQUAL_PTR(getMemory(allocatedPool->right),allocateRecord);
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(150,getSize(allocatedPool->right));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    TEST_ASSERT_NULL(allocatedPool->right->left);
    TEST_ASSERT_NULL(allocatedPool->right->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+150);
}

void test_safeMalloc_should_add_three_records_into_allocated_pool(void){
    resetAllocatedPool();
    void *allocateRecord = safeMalloc(50);
    
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(allocatedPool));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+50);
    
    allocateRecord = safeMalloc(70);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(70,getSize(allocatedPool->right));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+70);
    
    allocateRecord = safeMalloc(100);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool->left));
    TEST_ASSERT_EQUAL(70,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(100,getSize(allocatedPool->right));
    TEST_ASSERT_NOT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+100);
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


void test_safeFree_should_remove_record_from_allocated_pool_and_put_into_free_pool(void){
    resetAllocatedPool();
    
    void *allocateRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(allocatedPool));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+50);
    
    safeFree(allocateRecord);
    TEST_ASSERT_NOT_NULL(freePool);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(freePool));
    TEST_ASSERT_EQUAL(50,getSize(freePool));
    TEST_ASSERT_NULL(freePool->left);
    TEST_ASSERT_NULL(freePool->right);
    //To verify that allocatedPool is empty, all records been free
    //to freePool
    TEST_ASSERT_NULL(allocatedPool);
}

void test_safeFree_should_remove_two_record_from_allocated_pool_and_put_into_free_pool(void){
    resetAllocatedPool();
    
    void *allocateRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(allocatedPool));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+50);
    
    void *allocateRecord2 = safeMalloc(70);
    TEST_ASSERT_EQUAL_PTR(allocateRecord2,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(70,getSize(allocatedPool->right));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord2-15);
    checkFooterMemoryContent(allocateRecord2+70);
    
    safeFree(allocateRecord2);
    TEST_ASSERT_NOT_NULL(freePool);
    TEST_ASSERT_NULL(freePool->left);
    TEST_ASSERT_NULL(freePool->right);
    TEST_ASSERT_EQUAL(70,getSize(freePool));
    TEST_ASSERT_EQUAL(allocateRecord2,getMemory(freePool));
    
    safeFree(allocateRecord);
    TEST_ASSERT_NOT_NULL(freePool->left);
    TEST_ASSERT_NULL(freePool->right);
    TEST_ASSERT_EQUAL(50,getSize(freePool->left));
    TEST_ASSERT_EQUAL(allocateRecord,getMemory(freePool->left));
    
    //To verify that allocatedPool is empty, all records been free
    //to freePool
    TEST_ASSERT_NULL(allocatedPool);
}

void test_safeFree_should_remove_three_record_from_allocated_pool_and_put_into_free_pool(void){
    resetAllocatedPool();
    
    void *allocateRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(allocatedPool);
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(allocatedPool));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord-15);
    checkFooterMemoryContent(allocateRecord+50);
    
    void *allocateRecord2 = safeMalloc(70);
    TEST_ASSERT_EQUAL_PTR(allocateRecord2,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(70,getSize(allocatedPool->right));
    TEST_ASSERT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord2-15);
    checkFooterMemoryContent(allocateRecord2+70);
    
    void *allocateRecord3 = safeMalloc(100);
    TEST_ASSERT_EQUAL_PTR(allocateRecord3,getMemory(allocatedPool->right));
    TEST_ASSERT_EQUAL(50,getSize(allocatedPool->left));
    TEST_ASSERT_EQUAL(70,getSize(allocatedPool));
    TEST_ASSERT_EQUAL(100,getSize(allocatedPool->right));
    TEST_ASSERT_NOT_NULL(allocatedPool->left);
    TEST_ASSERT_NOT_NULL(allocatedPool->right);
    checkHeaderMemoryContent(allocateRecord3-15);
    checkFooterMemoryContent(allocateRecord3+100);
    
    safeFree(allocateRecord);
    TEST_ASSERT_NOT_NULL(freePool);
    TEST_ASSERT_NULL(freePool->left);
    TEST_ASSERT_NULL(freePool->right);
    TEST_ASSERT_EQUAL(50,getSize(freePool));
    TEST_ASSERT_EQUAL_PTR(allocateRecord,getMemory(freePool));
    
    safeFree(allocateRecord2);
    TEST_ASSERT_NULL(freePool->right);
    TEST_ASSERT_NOT_NULL(freePool->left);
    TEST_ASSERT_EQUAL(70,getSize(freePool));
    TEST_ASSERT_EQUAL(50,getSize(freePool->left));
   
}
