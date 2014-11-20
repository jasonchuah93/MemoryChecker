#include "unity.h"
#include "safeMalloc.h"
#include "LinkedList.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

void test_safeMalloc_should_allocate_the_memory_size_before_the_user_input(void){
    int i;
    safeMalloc(100);
    
    
}

void test_safeFree_should_free_all_memory(void){
   
}

