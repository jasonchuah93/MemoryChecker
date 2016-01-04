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

void test_safeMalloc_should_allocate_size_15(void){
	char *allocated15;
	allocated15 = safeMalloc(15);
	
	printf("header content : %s",allocated15-50);
	TEST_ASSERT_EQUAL(allocated15,memoryAddr(allocatedPool));
	TEST_ASSERT_EQUAL(15,memorySize(allocatedPool));
}
