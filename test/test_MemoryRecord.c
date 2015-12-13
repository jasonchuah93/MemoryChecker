#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "MemoryBlocks.h"
#include "MemoryRecord.h"
#include "mock_MallocWrapper.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_createRecord_should_create_descriptor_with_allocated_size_and_memory(void){
    MemoryBlocks ptrBlock = {.header1[49] = "#####" , .memory1[99] = "abcdef", .footer1[49] = "#####"};
	
    _malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)&ptrBlock);
    void *allocateMemBlock = allocateMemory(100);
    Record *newRecord = createRecord(100,allocateMemBlock);
   
    TEST_ASSERT_NOT_NULL(newRecord);
    TEST_ASSERT_EQUAL(100,newRecord->size);
    TEST_ASSERT_EQUAL(&ptrBlock.header1,newRecord->headerAddr);
    TEST_ASSERT_EQUAL(&ptrBlock.memory1,newRecord->memoryAllocateAddr);
    TEST_ASSERT_EQUAL(&ptrBlock.footer1,newRecord->footerAddr);
    TEST_ASSERT_EQUAL(18,newRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",newRecord->fileName);
	
    _free_Expect(allocateMemBlock);
    freeMemory(allocateMemBlock);
    _free_Expect((void*)newRecord);
    freeMemory((void*)newRecord);
}

