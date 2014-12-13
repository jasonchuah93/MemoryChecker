#include "unity.h"
#include "Node.h"
#include "MemoryRecord.h"

void setUp(void){}

void tearDown(void){}

void test_createRecord_should_take_in_information_and_return_in_record_type(void){
    char buffer[20];
    Record *record ;
    record = createRecord(buffer,100);
    printf("Address of Memory : %d\n",buffer);
    TEST_ASSERT_EQUAL(2686552,record->memory);
    TEST_ASSERT_EQUAL(100,record->size);
    TEST_ASSERT_EQUAL(12,record->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",record->fileName);
}


