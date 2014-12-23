#include "unity.h"
#include "Node.h"
#include "MemoryRecord.h"

void setUp(void){}

void tearDown(void){}

void test_createRecord_should_take_in_information_and_return_in_record_type(void){
    char *memory = "123456789";
    Record *newRecord = createRecord(memory,288);
    TEST_ASSERT_NOT_NULL(newRecord);
    TEST_ASSERT_EQUAL(newRecord->size,288);
    TEST_ASSERT_EQUAL(newRecord->memory,"123456789");
    TEST_ASSERT_EQUAL(newRecord->lineNumber,11);
    TEST_ASSERT_EQUAL_STRING(newRecord->fileName,"test/test_MemoryRecord.c");
}


