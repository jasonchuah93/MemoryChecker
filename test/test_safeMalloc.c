#include "unity.h"
#include "safeMalloc.h"

void setUp(void){}

void tearDown(void){}

#define safeMalloc(size) safeMalloc(size,__LINE__,__FILE__)

void test_safeMalloc_should_state_the_size_line_and_file_of_the_number(void){
  safeMalloc(100);
}

void test_safeMalloc_should_allocate_memory(void){
	
}