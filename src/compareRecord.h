#ifndef compareRecord_H
#define compareRecord_H

#include "MemoryRecord.h"
#include "Node.h"
#include "MemoryBlocks.h"

#define memorySize(node) (((Record*)((Node*)(node))->data)->size)
#define memoryAddr(node) (((Record*)((Node*)(node))->data)->memoryAllocateAddr)

int findAndRemoveRecordCompare(Node **recordFromRedBlackTree,char *targetMemoryAddr);
int addRecordCompare(Node **recordFromRedBlackTree,Node *compareRecord);
	
#endif // compareRecord_H
