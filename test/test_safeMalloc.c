#include "unity.h"
#include "Node.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "memoryAllocator.h"
#include "mock_redBlackTree.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

void test_safeMalloc_should_throw_error_if_size_of_memory_cross_the_internal_memory_size(void){
    CEXCEPTION_T err;
    Record *info;
    char *memory;
    info->size = 100;
    Try{
        memory = safeMalloc(150);
        TEST_FAIL_MESSAGE("Expected ERR_EXCEED_ALLOCATED_MEMORY to be thrown.But receive none");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_EXCEED_ALLOCATED_MEMORY,err);
    }
}


