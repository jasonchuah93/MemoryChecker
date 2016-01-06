#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "MallocWrapper.h"
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


void test_safeMalloc_should_allocate_size_15_and_move_into_allocatedPool(void){
	initializePool();
	
	char *allocated15;
	allocated15 = (char*)safeMalloc(15);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(15,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL_STRING(HEADERCONTENT,allocated15-50);
	TEST_ASSERT_EQUAL_STRING(FOOTERCONTENT,allocated15+15);

}

void test_safeMalloc_should_allocate_size_15_and_safeFree_to_freePool(void){
	initializePool();
	char *allocated15;
	
	allocated15 = (char*)safeMalloc(15);
	safeFree(allocated15);
	
	TEST_ASSERT_NULL(allocatedPool);
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(freePool));
	TEST_ASSERT_EQUAL(15,memorySize(freePool));
	TEST_ASSERT_EQUAL_STRING(HEADERCONTENT,allocated15-50);
	TEST_ASSERT_EQUAL_STRING(FOOTERCONTENT,allocated15+15);
	
	freeMemory(allocated15);
}
/*
void test_safeMalloc_should_allocate_size_15_and_safeSummary_to_check_for_error(void){
	initializePool();
	char *allocated15;
	allocated15 = (char*)safeMalloc(15);
	
	safeSummary();
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(15,memorySize(allocatedPool));
	TEST_ASSERT_EQUAL_STRING(HEADERCONTENT,allocated15-50);
	TEST_ASSERT_EQUAL_STRING(FOOTERCONTENT,allocated15+15);
}

void test_safeMalloc_should_allocate_size_15_safeFree_to_freePool_and_safeSummary_to_check_for_error(void){
	initializePool();
	char *allocated15;
	allocated15 = (char*)safeMalloc(15);
	safeFree(allocated15);
	safeSummary();
	
	freeMemory(allocated15);
}

void test_safeFree_should_throw_error_if_header_content_modified(void){
	initializePool();
	ErrorCode e;
	char * allocated15 = (char*)safeMalloc(15);
	strcpy(allocated15-50,"modifiedTheHeaderPatter");
	Try{
		safeFree(allocated15);
		TEST_FAIL_MESSAGE("Header content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	freeMemory(allocated15);
}

void test_safeFree_should_throw_error_if_footer_content_modified(void){
	initializePool();
	ErrorCode e;
	char * allocated50 = (char*)safeMalloc(50);
	strcpy(allocated50+50,"modifiedTheHeaderPatternInFooter");
	Try{
		safeFree(allocated50);
		TEST_FAIL_MESSAGE("Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated50);
}

void test_safeFree_should_throw_error_if_header_footer_content_modified(void){
	initializePool();
	ErrorCode e;
	char * allocated50 = (char*)safeMalloc(50);
	strcpy(allocated50-50,"modifiedTheHeaderPatternInHeader");
	strcpy(allocated50+50,"modifiedTheHeaderPatternInFooter");
	Try{
		safeFree(allocated50);
		TEST_FAIL_MESSAGE("Header and Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated50);
}

void test_safeFree_should_throw_error_if_nodes_in_tree_header_footer_content_modified(void){
	initializePool();
	ErrorCode e;
	
	char * allocated10 = (char*)safeMalloc(10);
	char * allocated20 = (char*)safeMalloc(20);
	char * allocated30 = (char*)safeMalloc(30);
	char * allocated40 = (char*)safeMalloc(40);
	char * allocated50 = (char*)safeMalloc(50);
	
	strcpy(allocated50-50,"modifiedTheHeaderPatternInHeader");
	strcpy(allocated50+50,"modifiedTheHeaderPatternInFooter");
	Try{
		safeFree(allocated50);
		TEST_FAIL_MESSAGE("Header and Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated10);
	freeMemory(allocated20);
	freeMemory(allocated30);
	freeMemory(allocated40);
	freeMemory(allocated50);
}

void test_safeFree_should_throw_error_if_nodes_in_tree_header_footer_content_modified_2(void){
	initializePool();
	ErrorCode e;
	
	char * allocated10 = (char*)safeMalloc(10);
	char * allocated20 = (char*)safeMalloc(20);
	char * allocated30 = (char*)safeMalloc(30);
	char * allocated40 = (char*)safeMalloc(40);
	char * allocated50 = (char*)safeMalloc(50);
	
	strcpy(allocated10-50,"modifiedTheHeaderPatternInHeader");
	strcpy(allocated20+20,"modifiedTheHeaderPatternInFooter");
	strcpy(allocated30-50,"modifiedTheHeaderPatternInHeader");
	strcpy(allocated30+30,"modifiedTheHeaderPatternInFooter");
	
	Try{
		safeFree(allocated10);
		TEST_FAIL_MESSAGE("Header content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	Try{
		safeFree(allocated20);
		TEST_FAIL_MESSAGE("Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	Try{
		safeFree(allocated30);
		TEST_FAIL_MESSAGE("Header and Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated10);
	freeMemory(allocated20);
	freeMemory(allocated30);
	freeMemory(allocated40);
	freeMemory(allocated50);
}

void test_safeFree_then_safeSummary_should_throw_error_if_nodes_in_tree_header_footer_content_modified_2(void){
	initializePool();
	ErrorCode e;
	
	char * allocated10 = (char*)safeMalloc(10);
	char * allocated20 = (char*)safeMalloc(20);
	char * allocated30 = (char*)safeMalloc(30);
	char * allocated40 = (char*)safeMalloc(40);
	char * allocated50 = (char*)safeMalloc(50);
	
	strcpy(allocated10-50,"modifiedTheHeaderPatternInHeader");
	strcpy(allocated20+20,"modifiedTheHeaderPatternInFooter");
	strcpy(allocated30-50,"modifiedTheHeaderPatternInHeader");
	strcpy(allocated30+30,"modifiedTheHeaderPatternInFooter");
	
	Try{
		safeFree(allocated10);
		TEST_FAIL_MESSAGE("Header content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	Try{
		safeFree(allocated20);
		TEST_FAIL_MESSAGE("Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	Try{
		safeFree(allocated30);
		TEST_FAIL_MESSAGE("Header and Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated10);
	freeMemory(allocated20);
	freeMemory(allocated30);
	freeMemory(allocated40);
	freeMemory(allocated50);
}

void test_safeMalloc_write_into_footer_block_safeFree_should_throw_error(void){
	initializePool();
	ErrorCode e;
	char *allocated15 = (char*)safeMalloc(15);
	strcpy(allocated15,"now writing into footer block");
	
	Try{
		safeFree(allocated15);
		TEST_FAIL_MESSAGE("Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated15);
}

void test_safeMalloc_write_into_footer_block_safeSummary_should_throw_error(void){
	initializePool();
	ErrorCode e;
	char *allocated15 = (char*)safeMalloc(15);
	strcpy(allocated15,"now writing into footer block");
	
	Try{
		safeSummary();
		TEST_FAIL_MESSAGE("Footer content modified");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	freeMemory(allocated15);
}
*/