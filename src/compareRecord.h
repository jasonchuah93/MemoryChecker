#ifndef compareRecord_H
#define compareRecord_H

#include "MemoryRecord.h"
#include "Node.h"
#include "MemoryBlocks.h"

int findRecordCompare(Node **recordFromRedBlackTree,Allocation *targetMemoryAddr);
int addAndDelRecordCompare(Node **recordFromRedBlackTree,Node *compareRecord);
	
#endif // compareRecord_H
