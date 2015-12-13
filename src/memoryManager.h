#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

//Define memory size
#define DEFAULT_MEMORY_SIZE 300

//Define 3 types of pool
//General memory pool which has the fixed block size 
//for allocation 
void *memoryPool;
//This pool use to store allocated memory that 
//allocate from general memory pool
Node *allocatedPool;
//This pool use to store the freed memory that free from 
//allocatedPool
Node *freePool;

void *initializeMemoryPool(int memorySize);
void memoryManagerAllocateRecord(Record *record);
void memoryManagerFreeRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
void memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
