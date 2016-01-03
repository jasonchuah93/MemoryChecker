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

MemoryBlock1 ptrBlock1 = {.header[49] = HEADERCONTENT , .memory[99] = "abcdef", .footer[49] = FOOTERCONTENT};
MemoryBlock2 ptrBlock2 = {.header[49] = HEADERCONTENT , .memory[199] = "abcdef", .footer[49] = FOOTERCONTENT};
MemoryBlock3 ptrBlock3 = {.header[49] = HEADERCONTENT , .memory[299] = "abcdef", .footer[49] = FOOTERCONTENT};
MemoryBlock4 ptrBlock4 = {.header[49] = HEADERCONTENT , .memory[399] = "abcdef123", .footer[49] = FOOTERCONTENT};
MemoryBlock5 ptrBlock5 = {.header[49] = HEADERCONTENT , .memory[499] = "abcdef123", .footer[49] = FOOTERCONTENT};
MemoryBlock6 ptrBlock6 = {.header[49] = HEADERCONTENT , .memory[599] = "abcdef123456", .footer[49] = FOOTERCONTENT};
MemoryBlock7 ptrBlock7 = {.header[49] = HEADERCONTENT , .memory[699] = "abcdef123456", .footer[49] = FOOTERCONTENT};
MemoryBlock8 ptrBlock8 = {.header[49] = HEADERCONTENT , .memory[799] = "abcdef123456", .footer[49] = FOOTERCONTENT};
	
