#include "unity.h"
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "memoryAllocator.h"
#include "redBlackTree.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

void test_safeMalloc_should_throw_error_if_size_of_memory_cross_the_internal_memory_size(void){
    CEXCEPTION_T err;
    char *memory;
    Try{
        memory = safeMalloc(1100);
        TEST_FAIL_MESSAGE("Expected ERR_EXCEED_ALLOCATED_MEMORY to be thrown.But receive none");
    }Catch(err){
        TEST_ASSERT_EQUAL(ERR_EXCEED_ALLOCATED_MEMORY,err);
    }
}

void test_safeMalloc_should_create_memory_record(void){
    int i;Record *record;
    char *memory = safeMalloc(300);
    
}

