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

void test_safeMalloc_should_return_null_if_the_size_is_0(void){
    void *allocatedRecord ;
    Node *root =NULL;
    memoryInitialization();
    allocatedRecord=safeMalloc(0);
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
    void *allocatedRecord ;
    allocatedRecord = safeMalloc(200);
    
    TEST_ASSERT_EQUAL_STRING(headerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(footerBlock,"5A5A5A5A5A5A5A");
    testFree(allocatedRecord);
}

void test_safeMalloc_add_the_record_into_allocated_pool(void){
    void *allocatedRecord ;
    Node *root =NULL;
    allocatedRecord = safeMalloc(100);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL(allocatedRecord,((Record*)root)->memory);
    TEST_ASSERT_EQUAL_STRING(headerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(footerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL(100,((Record*)root)->size);
    TEST_ASSERT_NULL(((Record*)root)->left);
    TEST_ASSERT_NULL(((Record*)root)->right);
    testFree(allocatedRecord);
}

void test_safeMalloc_add_2_records_into_allocated_pool(void){
    void *allocatedRecord ;
    Node *root =NULL;
    allocatedRecord = safeMalloc(80);
    
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL(allocatedRecord,((Record*)root)->memory);
    TEST_ASSERT_EQUAL_STRING(headerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(footerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL(80,((Record*)root)->size);
    TEST_ASSERT_NULL(((Record*)root)->left);
    TEST_ASSERT_NULL(((Record*)root)->right);
    
    allocatedRecord = safeMalloc(50);
    TEST_ASSERT_NOT_NULL(((Record*)root)->left);
    TEST_ASSERT_NULL(((Record*)root)->right);
    TEST_ASSERT_EQUAL(allocatedRecord,((Record*)root->left)->memory);
    TEST_ASSERT_EQUAL(50,((Record*)root->left)->size);
    TEST_ASSERT_NULL(((Record*)root)->left->left);
    TEST_ASSERT_NULL(((Record*)root)->left->right);
    testFree(allocatedRecord); 
}    

void test_safeMalloc_add_3_records_into_allocated_pool(void){
    void *allocatedRecord ;
    Node *root =NULL;
    allocatedRecord = safeMalloc(200);
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL(allocatedRecord,((Record*)root)->memory);
    TEST_ASSERT_EQUAL(200,((Record*)root)->size);
    TEST_ASSERT_NULL(((Record*)root)->left);
    TEST_ASSERT_NULL(((Record*)root)->right);
    
    allocatedRecord = safeMalloc(150);
    TEST_ASSERT_NOT_NULL(((Record*)root)->left);
    TEST_ASSERT_NULL(((Record*)root)->right);
    TEST_ASSERT_EQUAL(allocatedRecord,((Record*)root->left)->memory);
    TEST_ASSERT_EQUAL(150,((Record*)root->left)->size);
    TEST_ASSERT_NULL(((Record*)root)->left->left);
    TEST_ASSERT_NULL(((Record*)root)->left->right);
    
    allocatedRecord = safeMalloc(300);
    TEST_ASSERT_NOT_NULL(((Record*)root)->left);
    TEST_ASSERT_NOT_NULL(((Record*)root)->right);
    TEST_ASSERT_EQUAL(allocatedRecord,((Record*)root->right)->memory);
    TEST_ASSERT_EQUAL(300,((Record*)root->right)->size);
    TEST_ASSERT_NULL(((Record*)root)->right->left);
    TEST_ASSERT_NULL(((Record*)root)->right->right);
    
    testFree(allocatedRecord); 
    printf("allocatedRecord : %d \n",((Record*)root->left)->size);
}

void test_safeFree_should_throw_error_if_HEADER_MEMORY_been_modify(void){
    void *allocatedRecord ;
    ErrorCode e;
    Node *root = NULL;
    printf("TEST 7\n");
    allocatedRecord = safeMalloc(10);
    headerBlock =(void*) "1A1A1A1A";
    Try{
        testFree(allocatedRecord);
        TEST_FAIL_MESSAGE("Memory modified ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_MEMORY_WRONG,e);
    }
}

