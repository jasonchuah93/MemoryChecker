#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

//Global variable as the root of the red black tree
Node *allocatedPool;
Node *freedPool;

void memoryManagerAllocateRecord(Record *record);
void memoryManagerFreeRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
void memoryManagerDelRecord(Record *record);
void resetAllocatedPool();

#endif // memoryManager_H
