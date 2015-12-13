#include "unity.h"
//#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "MemoryRecord.h"
#include "mock_MallocWrapper.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_createRecord_should_create_descriptor_with_allocated_size_and_memory(void){
    MemoryBlocks memblock = {.header1[20] = "####" , .memory1[80] = "abc", .footer1[30] = "$$$$$"};
	_malloc_ExpectAndReturn(24,(char*)&memblock);
	Record newRecord = createRecord(280,(char*)&memblock);
    
    TEST_ASSERT_NOT_NULL(newRecord);
    TEST_ASSERT_EQUAL(280,newRecord->size);
    TEST_ASSERT_EQUAL(&memblock,newRecord->headerAddr);
    //TEST_ASSERT_EQUAL(16,newRecord->lineNumber);
    //TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",newRecord->fileName);
	
}
/*
void test_createRecord_should_throw_error_if_size_is_zero(void){
    ErrorCode e;
    char memoryData[] = "123456789";
    Record *recordPtr = malloc(sizeof(Record));
    recordPtr->memoryAddr = &memoryData;
    Try{
        Record *newRecord = createRecord(recordPtr,0);
        TEST_FAIL_MESSAGE("Should throw error invalid size ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_INVALID_SIZE,e);
    }
}

void test_createRecord_should_throw_error_if_size_is_negative(void){
    ErrorCode e;
    char memoryData[] = "123456789";
    Record *recordPtr = malloc(sizeof(Record));
    recordPtr->memoryAddr = &memoryData;
    Try{
        Record *newRecord = createRecord(recordPtr,-10);
        TEST_FAIL_MESSAGE("Should throw error invalid size ");
    }Catch(e){
        TEST_ASSERT_EQUAL(ERR_INVALID_SIZE,e);
    }
}
*/