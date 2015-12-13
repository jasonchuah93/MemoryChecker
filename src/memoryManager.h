#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

void *initializeMemoryPool(int memorySize);
void memoryManagerAllocateRecord(Record *record);
void memoryManagerFreeRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
void memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
