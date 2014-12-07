#include "unity.h"
#include "InitNode.h"
#include "Node.h"
#include "MemoryRecord.h"
#include "compareRecord.h"

Node node1,node2;

void setUp(void){}

void tearDown(void){}

void test_findRecordCompare_should_return_1_if_memoryInRedBlackTree_is_larger_than_newMemory(void){
	Record sizeOfMemoryFromRedBlackTree = {.memory=(char*)0x45610};
    char *sizeOfNewMemory = (char*)0x1234;
    
    TEST_ASSERT_EQUAL(1,findRecordCompare(&sizeOfMemoryFromRedBlackTree,sizeOfNewMemory));
}

void test_findRecordCompare_should_return_negative_1_if_newMemory_is_larger_than_memoryFromRedBlackTree(void){
	Record sizeOfMemoryFromRedBlackTree ={.memory=(char*)0x789};
    char *sizeOfNewMemory = (char*)0x1234;
	
    TEST_ASSERT_EQUAL(-1,findRecordCompare(&sizeOfMemoryFromRedBlackTree,sizeOfNewMemory));
}

void test_findRecordCompare_should_return_0_if_newMemory_is_equal_than_memoryFromRedBlackTree(void){
	Record sizeOfMemoryFromRedBlackTree ={.memory=(char*)0x456};
    char *sizeOfNewMemory = (char*)0x456;
	
	TEST_ASSERT_EQUAL(0,findRecordCompare(&sizeOfMemoryFromRedBlackTree,sizeOfNewMemory));
}


void test_addAndDelRecordCompare_should_return_1_if_memoryInRedBlackTree_is_larger_than_newMemory(void){
    Record sizeOfMemoryFromRedBlackTree ={.size=600};
    Record sizeOfNewMemory = {.size=456};
	resetGenericNode(&node1,&sizeOfMemoryFromRedBlackTree);
    resetGenericNode(&node2,&sizeOfNewMemory);
    
    Node *mainNode = &node1;
    TEST_ASSERT_EQUAL(1,addAndDelRecordCompare((void*)&mainNode,&node2));
}

void test_addAndDelRecordCompare_should_return_negative_1_if_memoryInRedBlackTree_is_smaller_than_newMemory(void){
    Record sizeOfMemoryFromRedBlackTree ={.size=60};
    Record sizeOfNewMemory = {.size=456};
	resetGenericNode(&node1,&sizeOfMemoryFromRedBlackTree);
    resetGenericNode(&node2,&sizeOfNewMemory);
    
    Node *mainNode = &node1;
    TEST_ASSERT_EQUAL(-1,addAndDelRecordCompare((void*)&mainNode,&node2));
}

void test_addAndDelRecordCompare_should_return_0_if_memoryInRedBlackTree_is_equal_than_newMemory(void){
    Record sizeOfMemoryFromRedBlackTree ={.size=456};
    Record sizeOfNewMemory = {.size=456};
	
    resetGenericNode(&node1,&sizeOfMemoryFromRedBlackTree);
    resetGenericNode(&node2,&sizeOfNewMemory);
    
    Node *mainNode = &node1;
    TEST_ASSERT_EQUAL(0,addAndDelRecordCompare((void*)&mainNode,&node2));
}
