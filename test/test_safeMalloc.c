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
    safeMalloc(0);
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
    targetPointer = safeMalloc(200);
    printf("Unit Test\n");
    printf("content : %s \n",headerBlock);
    TEST_ASSERT_EQUAL_STRING(headerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(footerBlock,"5A5A5A5A5A5A5A");
    
    safeFree(targetPointer);
}

void test_safeMalloc_add_the_memory_Block_into_Record(void){
    targetPointer = safeMalloc(100);
    TEST_ASSERT_EQUAL_STRING(headerBlock,"5A5A5A5A5A5A5A");
    TEST_ASSERT_EQUAL_STRING(footerBlock,"5A5A5A5A5A5A5A");
    
    //printf("Unit Test 2\n");
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL(targetPointer,((Record*)root)->memory);
    TEST_ASSERT_EQUAL(100,((Record*)root)->size);
    TEST_ASSERT_NULL(((Record*)root)->left);
    TEST_ASSERT_NULL(((Record*)root)->right);
}

