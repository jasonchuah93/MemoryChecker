#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "MemoryRecord.h"
#include "mock_MallocWrapper.h"

void setUp(void){}
void tearDown(void){}

void test_allocateMemory_should_allocate_user_input_size_and_return_pointer_which_point_to_first_allocated_memory_block(void){
    Allocation *ptr;
    MemoryBlock1 ptrBlock = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
    _malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)&ptrBlock);
    ptr = allocateMemory(100);
    
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL(&ptrBlock.header,ptr->headerAddr);
    TEST_ASSERT_EQUAL(&ptrBlock.memory,ptr->memoryAllocateAddr);
    TEST_ASSERT_EQUAL(&ptrBlock.footer,ptr->footerAddr);
    TEST_ASSERT_EQUAL_STRING("##########",ptr->headerAddr);
    TEST_ASSERT_EQUAL_STRING("abcdef",ptr->memoryAllocateAddr);
    TEST_ASSERT_EQUAL_STRING("##########",ptr->footerAddr);
    TEST_ASSERT_EQUAL(100,ptr->size);
    TEST_ASSERT_EQUAL(15,ptr->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",ptr->fileName);
    
    _free_Expect(ptr);
    freeMemory(ptr);
}

void test_createRecord_should_create_descriptor_with_allocated_size_and_memory(void){
    Allocation *ptr;
    Record *ptrRecord;
    MemoryBlock2 ptrBlock = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)&ptrBlock);
    
    ptr = allocateMemory(200);
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL(&ptrBlock.header,ptr->headerAddr);
    TEST_ASSERT_EQUAL(&ptrBlock.memory,ptr->memoryAllocateAddr);
    TEST_ASSERT_EQUAL(&ptrBlock.footer,ptr->footerAddr);
    TEST_ASSERT_EQUAL_STRING("$$$$$$$$$$",ptr->headerAddr);
    TEST_ASSERT_EQUAL_STRING("abcdef123456",ptr->memoryAllocateAddr);
    TEST_ASSERT_EQUAL_STRING("$$$$$$$$$$",ptr->footerAddr);
    TEST_ASSERT_EQUAL(200,ptr->size);
    TEST_ASSERT_EQUAL(38,ptr->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",ptr->fileName);
    
    ptrRecord = createRecord(200,ptr);
    TEST_ASSERT_NOT_NULL(ptrRecord);
    TEST_ASSERT_EQUAL(ptr->headerAddr,ptrRecord->headerAddr);
    TEST_ASSERT_EQUAL(ptr->memoryAllocateAddr,ptrRecord->memoryAllocateAddr);
    TEST_ASSERT_EQUAL(ptr->footerAddr,ptrRecord->footerAddr);
    TEST_ASSERT_EQUAL_STRING("$$$$$$$$$$",ptrRecord->headerAddr);
    TEST_ASSERT_EQUAL_STRING("abcdef123456",ptrRecord->memoryAllocateAddr);
    TEST_ASSERT_EQUAL_STRING("$$$$$$$$$$",ptrRecord->footerAddr);
    TEST_ASSERT_EQUAL(200,ptrRecord->size);
    TEST_ASSERT_EQUAL(38,ptrRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_MemoryRecord.c",ptrRecord->fileName);
    
     _free_Expect(ptr);
    freeMemory(ptr);
     _free_Expect(ptrRecord);
    freeMemory(ptrRecord);
}

