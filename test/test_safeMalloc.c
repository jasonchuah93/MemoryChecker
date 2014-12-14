#include "unity.h"
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "memoryAllocator.h"
#include "RestructureNode.h"
#include "redBlackTree.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

void test_safeMalloc_should_throw_error_if_size_of_memory_cross_the_internal_memory_size(void){
    
}

void test_safeMalloc_should_contain_information_of_the_size_input(void){
   
   
}

