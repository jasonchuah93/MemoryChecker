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

void test_safeMalloc_should_allocate_memory_and_return_in_record(void){
	void *testData;
	Record *testRecord;
	//Allocate size
	testRecord = createRecord("5A5A5A5A",100);
	testData=safeMalloc(50);
	TEST_ASSERT_EQUAL(root,testData);
	//Check whether record is created after malloc
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NULL(root->left);
	TEST_ASSERT_NULL(root->right);
	destroyRecord(testRecord);
}

