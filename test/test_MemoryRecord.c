#include "unity.h"
#include "InitNode.h"
#include "Node.h"
#include "MemoryRecord.h"

void setUp(void){}

void tearDown(void){}

void test_createRecord_should_take_in_information_and_return_in_record_type(void){
    Record *record ;
    char *memory = "5A5A5A";
    record = createRecord(memory,100);
    TEST_ASSERT_EQUAL_STRING("5A5A5A",record->memory);
    TEST_ASSERT_EQUAL(100,record->size);
    TEST_ASSERT_EQUAL(13,record->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",record->fileName);
}


