#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node mainNode,subLeftNode,subRightNode,subLeftNodeChild,subRightNodeChild;

void setUp(void){}

void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*	root		        root
*	 |    add record	 |
*	 v    ----------->   v
*	NULL               record
**/

void test_genericAddRedBlackTree_add_record_into_redBlackTree(void){
    Record *record = createRecord("5555AAAA",100);
    resetGenericNode(&mainNode,record);
    Node *rootPtr = NULL;
    
    addMemory(&rootPtr,&mainNode);
    TEST_ASSERT_NOT_NULL(rootPtr);
    TEST_ASSERT_NOT_NULL(rootPtr->dataPtr);
    TEST_ASSERT_NULL(rootPtr->right);
    TEST_ASSERT_NULL(rootPtr->left);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',rootPtr);
    
    Record *readRecord =(Record*)rootPtr->dataPtr;
    TEST_ASSERT_EQUAL_STRING("5555AAAA",readRecord->memory);
    TEST_ASSERT_EQUAL(100,readRecord->size);
    TEST_ASSERT_EQUAL(33,readRecord->lineNumber);
    TEST_ASSERT_EQUAL_STRING("test/test_redBlackTree.c",readRecord->fileName);
}




