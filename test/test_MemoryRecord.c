#include "unity.h"
#include "Node.h"
#include "MemoryRecord.h"

void setUp(void){}

void tearDown(void){}

#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

void test_createRecord_should_take_in_information_and_return_in_record_type(void){
    Record *record ;
    char *memory = "5A5A5A";
    record = createRecord(memory,100);
    TEST_ASSERT_EQUAL_STRING("5A5A5A",record->memory);
    TEST_ASSERT_EQUAL(100,record->size);
    TEST_ASSERT_EQUAL(14,record->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",record->fileName);
}

void test_findRecordCompare_should_return_1_if_memory_is_larger_than_memoryFromRedBlackTree(void){
	char *memory = (char*)0x456;
	Record record ={.memory=(char*)0x123};
	
	TEST_ASSERT_EQUAL(1,findRecordCompare(memory,&record));
}

void test_findRecordCompare_should_return_negative_1_if_memory_is_smaller_than_memoryFromRedBlackTree(void){
	char *memory = (char*)0x123;
	Record record ={.memory=(char*)0x789};
	
	TEST_ASSERT_EQUAL(-1,findRecordCompare(memory,&record));
}

void test_findRecordCompare_should_return_0_if_memory_is_equal_than_memoryFromRedBlackTree(void){
	char *memory = (char*)0x456;
	Record record ={.memory=(char*)0x456};
	
	TEST_ASSERT_EQUAL(0,findRecordCompare(memory,&record));
}

void test_addDelRecordCompare_should_return_1_if_memory_is_larger_than_memoryFromRedBlackTree(void){
	Record *memory = (Record*)0x456;
	Record record ={.memory=(Record*)0x123};
	
	TEST_ASSERT_EQUAL(1,findRecordCompare(memory,&record));
}


void test_addDelRecordCompare_should_return_negative_1_if_memory_is_smaller_than_memoryFromRedBlackTree(void){
	Record *memory = (Record*)0x123;
	Record record ={.memory=(Record*)0x789};
	
	TEST_ASSERT_EQUAL(-1,findRecordCompare(memory,&record));
}

void test_addDelRecordCompare_should_return_0_if_memory_is_equal_than_memoryFromRedBlackTree(void){
	Record *memory = (Record*)0x456;
	Record record ={.memory=(Record*)0x456};
	
	TEST_ASSERT_EQUAL(0,findRecordCompare(memory,&record));
}


