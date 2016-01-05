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
#include "ErrorCode.h"
#include "CException.h"

void setUp(void){}
void tearDown(void){}

//AllocatedPool
#define leftPool allocatedPool->left
#define leftChildPool allocatedPool->left->left
#define leftRightChildPool allocatedPool->left->right
#define rightPool allocatedPool->right
#define rightChildPool allocatedPool->right->right
#define rightLeftChildPool allocatedPool->right->left
//FreePool
#define leftFreePool freePool->left
#define rightFreePool freePool->right
#define rightLeftChildFreePool freePool->right->left

MemoryBlock1 ptrBlock1;
MemoryBlock2 ptrBlock2;
MemoryBlock3 ptrBlock3;
MemoryBlock4 ptrBlock4; 
MemoryBlock5 ptrBlock5;
MemoryBlock6 ptrBlock6;
MemoryBlock7 ptrBlock7;
MemoryBlock8 ptrBlock8;
	
void test_safeFree_should_throw_error_if_header_memory_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100;
	MemoryBlock1 ptrBlock1; 
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	strcpy((char*)&ptrBlock1.header,"@@@@@@@@@@@@@@");
	Try{
		safeFree(allocatedMemory100);
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFree_should_throw_error_if_header_memory_of_the_left_node_in_freePool_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	MemoryBlock1 ptrBlock1;
	
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	strcpy((char*)&ptrBlock1.header,"@@@@@@@@@@@@@@");
	_malloc_ExpectAndReturn((HEADER_SIZE+300+FOOTER_SIZE),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	
	safeFree(allocatedMemory300);
	Try{
		safeFree(allocatedMemory100);
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_detect_header_content_had_been_modified_in_free_pool(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn((HEADER_SIZE+300+FOOTER_SIZE),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((HEADER_SIZE+400+FOOTER_SIZE),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	strcpy((char*)&ptrBlock4.header,"@@@@@@@@@@@@@@");
	_malloc_ExpectAndReturn((HEADER_SIZE+600+FOOTER_SIZE),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	strcpy((char*)&ptrBlock6.header,"@@@@@@@@@@@@@@");
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	strcpy((char*)&ptrBlock1.header,"@@@@@@@@@@@@@@");
	
	Try{
		safeFree(allocatedMemory600);
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	Try{
		safeFree(allocatedMemory400);
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	safeFree(allocatedMemory300);
	
	Try{
		safeFree(allocatedMemory100);
		TEST_FAIL_MESSAGE("Header memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_detect_header_and_footer_content_had_been_modified_in_free_pool(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn((HEADER_SIZE+300+FOOTER_SIZE),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	strcpy((char*)&ptrBlock3.header,"@@@@@@@@@@@@@@");
	strcpy((char*)&ptrBlock3.footer,"@@@@@@@@@@@@@@123234345");
	
	_malloc_ExpectAndReturn((HEADER_SIZE+400+FOOTER_SIZE),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	strcpy((char*)&ptrBlock4.header,"@@@@@@@@@@@@@@");
	strcpy((char*)&ptrBlock4.footer,"@@@@@@@@@@@@@@123234345");
	
	_malloc_ExpectAndReturn((HEADER_SIZE+600+FOOTER_SIZE),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	strcpy((char*)&ptrBlock6.header,"@@@@@@@@@@@@@@");
	strcpy((char*)&ptrBlock6.footer,"@@@@@@@@@@@@@@123234345");
	
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	strcpy((char*)&ptrBlock1.header,"@@@@@@@@@@@@@@");
	strcpy((char*)&ptrBlock1.footer,"@@@@@@@@@@@@@@123234345");
	Try{
		safeFree(allocatedMemory600);
		TEST_FAIL_MESSAGE("Header and footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	Try{
		safeFree(allocatedMemory400);
		TEST_FAIL_MESSAGE("Header and footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	Try{
		safeFree(allocatedMemory300);
		TEST_FAIL_MESSAGE("Header and footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	Try{
		safeFree(allocatedMemory100);
		TEST_FAIL_MESSAGE("Header and footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_HEADER_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_footer_memory_been_modified(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((HEADER_SIZE+300+FOOTER_SIZE),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((HEADER_SIZE+400+FOOTER_SIZE),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((HEADER_SIZE+600+FOOTER_SIZE),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	strcpy((char*)&ptrBlock6.footer,"@@@@@@@@@@@@@@123234345");
	
	safeFree(allocatedMemory300);
	safeFree(allocatedMemory400);
	safeFree(allocatedMemory100);
	
	Try{
		safeFree(allocatedMemory600);
		TEST_FAIL_MESSAGE("Footer memory edited");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_CORRUPTED_FOOTER_MEMORY,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFree(allocatedMemory400);
	Try{
		safeFree(allocatedMemory400);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice_right_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFree(allocatedMemory600);
	
	Try{
		safeFree(allocatedMemory600);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice_left_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	
	safeFree(allocatedMemory300);
	
	Try{
		safeFree(allocatedMemory300);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice_leftChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFree(allocatedMemory100);
	
	Try{
		safeFree(allocatedMemory100);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice_leftRightChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFree(allocatedMemory300);
	
	Try{
		safeFree(allocatedMemory300);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice_rightChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFree(allocatedMemory600);
	
	Try{
		safeFree(allocatedMemory600);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_same_address_twice_rightLeftChild_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300,*allocatedMemory400,*allocatedMemory600;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFree(allocatedMemory400);
	
	Try{
		safeFree(allocatedMemory400);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_n800_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+700+FOOTER_SIZE)),(char*)ptrBlock7.header);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn(((HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFree(allocatedMemory800);
	
	Try{
		safeFree(allocatedMemory800);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_n600_and_n100_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+700+FOOTER_SIZE)),(char*)ptrBlock7.header);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn(((HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFree(allocatedMemory600);
	safeFree(allocatedMemory100);
	
	Try{
		safeFree(allocatedMemory100);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_n100_then_n400_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+700+FOOTER_SIZE)),(char*)ptrBlock7.header);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn(((HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFree(allocatedMemory100);
	safeFree(allocatedMemory400);
	
	Try{
		safeFree(allocatedMemory400);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_n100_n400_then_n800_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+700+FOOTER_SIZE)),(char*)ptrBlock7.header);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn(((HEADER_SIZE+800+FOOTER_SIZE)),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFree(allocatedMemory100);
	safeFree(allocatedMemory400);
	safeFree(allocatedMemory800);
	
	Try{
		safeFree(allocatedMemory800);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_the_n100_n400_n800_then_n700_address_twice(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*allocatedMemory700,*allocatedMemory800;
	
	_malloc_ExpectAndReturn((HEADER_SIZE+300+FOOTER_SIZE),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn((HEADER_SIZE+600+FOOTER_SIZE),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn((HEADER_SIZE+100+FOOTER_SIZE),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn((HEADER_SIZE+200+FOOTER_SIZE),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn((HEADER_SIZE+400+FOOTER_SIZE),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn((HEADER_SIZE+700+FOOTER_SIZE),(char*)ptrBlock7.header);
	allocatedMemory700 = (char*)safeMalloc(700);
	_malloc_ExpectAndReturn((HEADER_SIZE+800+FOOTER_SIZE),(char*)ptrBlock8.header);
	allocatedMemory800 = (char*)safeMalloc(800);
	
	safeFree(allocatedMemory100);
	safeFree(allocatedMemory800);
	safeFree(allocatedMemory700);
	safeFree(allocatedMemory600);
	
	Try{
		safeFree(allocatedMemory700);
		TEST_FAIL_MESSAGE("Should not free same address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_FREED_TWICE,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedMemory700);
    freeMemory(allocatedMemory700);
	_free_Expect(allocatedMemory800);
    freeMemory(allocatedMemory800);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory = (char*)safeMalloc(100);
	safeFree(allocatedMemory);
	
	TEST_ASSERT_NULL(allocatedPool);
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory);
    freeMemory(allocatedMemory);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_throw_error_if_free_null_allocatedPool(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory = (char*)500;
	
	Try{
		safeFree(allocatedMemory);
		TEST_FAIL_MESSAGE("Should not free allocatedPool");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_POOL,e);
	}
}
/*
void test_safeFree_should_throw_error_if_free_address_not_in_the_allocatedPool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory400,*allocatedMemory500,*allocatedMemory600,*randomAddr;
	randomAddr = (char*)350;
	ErrorCode e;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+600+FOOTER_SIZE)),(char*)ptrBlock6.header);
	allocatedMemory600 = (char*)safeMalloc(600);
	_malloc_ExpectAndReturn(((HEADER_SIZE+500+FOOTER_SIZE)),(char*)ptrBlock5.header);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	Try{
		safeFree(randomAddr);
		TEST_FAIL_MESSAGE("Should not free address not in pool");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedMemory600);
    freeMemory(allocatedMemory600);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFree_should_throw_error_if_free_between_the_memoryAddr(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		safeFree(allocatedMemory300+100);
		TEST_FAIL_MESSAGE("Should not free between address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFree_should_throw_error_if_free_between_the_memoryAddr_on_left_node(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	Try{
		safeFree(allocatedMemory100+50);
		TEST_FAIL_MESSAGE("Should not free between address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFree_should_throw_error_if_free_header_address(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		safeFree(allocatedMemory100-50);
		TEST_FAIL_MESSAGE("Should not free header address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFree_should_throw_error_if_free_footer_address(void){
	initializePool();
	ErrorCode e;
	char *allocatedMemory100,*allocatedMemory300;
	MemoryBlock1 ptrBlock1 = {.header[29] = "@@@@@@@@@@" , .memory[99] = "abcdef123", .footer[29] = "&&&&&&&&&&"};
	MemoryBlock3 ptrBlock3 = {.header[29] = "##########" , .memory[299] = "abcdef", .footer[29] = "$$$$$$$$$$"};
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	Try{
		safeFree(allocatedMemory100+100);
		TEST_FAIL_MESSAGE("Should not free footer address");
	}Catch(e){
		TEST_ASSERT_EQUAL(ERR_INVALID_ADDRESS,e);
	}
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
}

void test_safeFree_should_free_left_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory500;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+500+FOOTER_SIZE)),(char*)ptrBlock5.header);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	safeFree(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,rightPool,'b',allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(rightPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',rightPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_right_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory500;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+500+FOOTER_SIZE)),(char*)ptrBlock5.header);
	allocatedMemory500 = (char*)safeMalloc(500);
	
	safeFree(allocatedMemory500);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory500,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_n200_and_n100_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	
	safeFree(allocatedMemory200);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	safeFree(allocatedMemory100);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory300,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',allocatedPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(leftFreePool,NULL,'b',freePool);
	//LeftFreePool
	TEST_ASSERT_NOT_NULL(leftFreePool);
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftFreePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftFreePool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_root_only_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory400;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	
	safeFree(allocatedMemory200);
	//AllocatedPool
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(allocatedMemory400,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL_NODE(leftPool,NULL,'b',allocatedPool);
	//LeftPool
	TEST_ASSERT_EQUAL(allocatedMemory100,memoryAddr(leftPool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',leftPool);
	//FreePool
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(allocatedMemory200,memoryAddr(freePool));
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',freePool);
	
	//Free memory and pool 
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}

void test_safeFree_should_free_few_record_from_allocatedPool_to_freePool(void){
	initializePool();
	char *allocatedMemory100,*allocatedMemory200,*allocatedMemory300,*allocatedMemory400,*allocatedMemory500;
	
	_malloc_ExpectAndReturn(((HEADER_SIZE+100+FOOTER_SIZE)),(char*)ptrBlock1.header);
	allocatedMemory100 = (char*)safeMalloc(100);
	_malloc_ExpectAndReturn(((HEADER_SIZE+200+FOOTER_SIZE)),(char*)ptrBlock2.header);
	allocatedMemory200 = (char*)safeMalloc(200);
	_malloc_ExpectAndReturn(((HEADER_SIZE+400+FOOTER_SIZE)),(char*)ptrBlock4.header);
	allocatedMemory400 = (char*)safeMalloc(400);
	_malloc_ExpectAndReturn(((HEADER_SIZE+500+FOOTER_SIZE)),(char*)ptrBlock5.header);
	allocatedMemory500 = (char*)safeMalloc(500);
	_malloc_ExpectAndReturn(((HEADER_SIZE+300+FOOTER_SIZE)),(char*)ptrBlock3.header);
	allocatedMemory300 = (char*)safeMalloc(300);
	
	safeFree(allocatedMemory400);
	safeFree(allocatedMemory100);
	safeFree(allocatedMemory200);
	
	_free_Expect(allocatedMemory100);
    freeMemory(allocatedMemory100);
	_free_Expect(allocatedMemory200);
    freeMemory(allocatedMemory200);
	_free_Expect(allocatedMemory300);
    freeMemory(allocatedMemory300);
	_free_Expect(allocatedMemory400);
    freeMemory(allocatedMemory400);
	_free_Expect(allocatedMemory500);
    freeMemory(allocatedMemory500);
	_free_Expect(allocatedPool);
    freeMemory(allocatedPool);
	_free_Expect(freePool);
    freeMemory(freePool);
}
*/