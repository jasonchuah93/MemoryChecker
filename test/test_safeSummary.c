#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "mock_MallocWrapper.h"
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"
#include "safeMalloc.h"
#include "safeFree.h"
#include "safeSummary.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

MemoryBlock1 ptrBlock1 = {.header[49] = HEADERCONTENT , .memory[99] = "abcdefghijklmnop", .footer[49] = FOOTERCONTENT};
//MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
MemoryBlock3 ptrBlock3 = {.header[49] = HEADERCONTENT , .memory[299] = "abcdef", .footer[49] = FOOTERCONTENT};
MemoryBlock4 ptrBlock4 = {.header[49] = HEADERCONTENT , .memory[399] = "abcdef123", .footer[49] = FOOTERCONTENT};
MemoryBlock5 ptrBlock5 = {.header[49] = HEADERCONTENT , .memory[499] = "abcdef123", .footer[49] = FOOTERCONTENT};
MemoryBlock6 ptrBlock6 = {.header[49] = HEADERCONTENT , .memory[599] = "abcdef123456", .footer[49] = FOOTERCONTENT};
MemoryBlock7 ptrBlock7 = {.header[49] = HEADERCONTENT , .memory[699] = "abcdef123456", .footer[49] = FOOTERCONTENT};
MemoryBlock8 ptrBlock8 = {.header[49] = HEADERCONTENT , .memory[799] = "abcdef123456", .footer[49] = FOOTERCONTENT};
	
void test_safeSummary_will_check_header_content_of_the_root_in_allocated_pool(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100;
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	safeSummary();
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_header_content_of_the_root_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300;
	MemoryBlock3 ptrBlock = {.header[49] = "&*&(*&*&(*&(*&(" , .memory[99] = "abcdefghijklmnop", .footer[49] = FOOTERCONTENT};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_footer_content_of_the_root_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory500;
	MemoryBlock5 ptrBlock = {.header[49] = HEADERCONTENT , .memory[99] = "abcdefghijklmnop", .footer[49] = "$%^$%^$%^$%^$%^%^"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+500+FOOTER_SIZE)),(char*)ptrBlock.header);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_header_and_footer_content_of_the_root_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory800;
	MemoryBlock8 ptrBlock = {.header[49] = "&*&(*&*&(*&(*&(" , .memory[99] = "abcdefghijklmnop", .footer[49] = "$%^$%^$%^$%^$%^%^"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Header and Footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_header_content_of_the_right_node_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory200,*allocatedMemory600,*allocatedMemory800;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "&*&(*&*&(*&(*&(" , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_footer_content_of_the_right_node_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory200,*allocatedMemory600,*allocatedMemory800;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = "$%^$%^$%^$%^$%^%^"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_header_and_footer_content_of_the_right_node_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory200,*allocatedMemory600,*allocatedMemory800;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = "&*&(*&*&(*&(*&(" , .memory[199] = "abcdef", .footer[49] = "$%^$%^$%^$%^$%^%^"};
	
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Header and footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_header_content_of_the_left_node_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory200,*allocatedMemory600,*allocatedMemory800;
	
    MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
    MemoryBlock6 ptrBlock6 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
    MemoryBlock8 ptrBlock8 = {.header[49] = "&*&(*&*&(*&(*&(" , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
	
    _malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
    Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
    _free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_footer_content_of_the_left_node_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory200,*allocatedMemory600,*allocatedMemory800;
	
    MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
    MemoryBlock6 ptrBlock6 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
    MemoryBlock8 ptrBlock8 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = "$%^$%^$%^$%^$%^%^"};
	
    _malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
    Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
    _free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeSummary_will_throw_error_if_header_and_footer_content_of_the_left_node_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory200,*allocatedMemory600,*allocatedMemory800;
	
	MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
    MemoryBlock6 ptrBlock6 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
    MemoryBlock8 ptrBlock8 = {.header[49] =  "&*&(*&*&(*&(*&("  , .memory[199] = "abcdef", .footer[49] = "$%^$%^$%^$%^$%^%^"};
	
    _malloc_ExpectAndReturn((sizeof(HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Header and footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}