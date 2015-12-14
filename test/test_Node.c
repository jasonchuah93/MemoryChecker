#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "MemoryRecord.h"
#include "mock_MallocWrapper.h"
#include "CustomAssertions.h"
#include "Node.h"

void setUp(void){}
void tearDown(void){}

void test_createNode_should_store_record_descriptor_inside_the_node(void){
    Allocation *ptr;
    Record *ptrRecord;
    Node *ptrNode;
    MemoryBlock2 ptrBlock = {.header[49] = "$$$$$$$$$$" , .memory[199] = "abcdef123456", .footer[49] = "$$$$$$$$$$"};
	_malloc_ExpectAndReturn((sizeof(HEADER_SIZE+200+FOOTER_SIZE)),(char*)&ptrBlock);
    
    ptr = allocateMemory(200);
    ptrRecord = createRecord(200,ptr);
    ptrNode = createNode(ptrRecord);
    TEST_ASSERT_NOT_NULL(ptrNode);
    TEST_ASSERT_EQUAL(ptrRecord,ptrNode->data);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',ptrNode);
    
     _free_Expect(ptr);
    freeMemory(ptr);
     _free_Expect(ptrRecord);
    freeMemory(ptrRecord);
     _free_Expect(ptrNode);
    freeMemory(ptrNode);
}