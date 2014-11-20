#include "unity.h"
#include "safeMalloc.h"
#include "LinkedList.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

void test_preMemory_size_is_equal_as_defined_BUFFER_SIZE(void){
    int memorySize = 256;
    TEST_ASSERT_EQUAL(memorySize,postMemorySize(256));
}

void test_postMemory_size_is_equal_as_defined_BUFFER_SIZE(void){
    int memorySize = 256;
    TEST_ASSERT_EQUAL(memorySize,postMemorySize(256));
}

void test_safeMalloc_should_allocate_corrrect_memory_size(void){
    
}

void test_safeFree_should_free_all_memory(void){
   
}

void test_safeFree_allocate_100_memory(void){
    
}