#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_createRecord_should_take_in_information_and_return_in_record_type(void){
    char memoryData[] = "123456789";
    Record *recordPtr = malloc(sizeof(Record));
    recordPtr->memoryAddr = &memoryData;
    Record *newRecord = createRecord(recordPtr,288);
    
    TEST_ASSERT_NOT_NULL(newRecord);
    TEST_ASSERT_EQUAL(288,newRecord->size);
    TEST_ASSERT_EQUAL(&memoryData,newRecord->memoryAddr);
    TEST_ASSERT_EQUAL(16,newRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",newRecord->fileName);
}

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
