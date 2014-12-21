#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

//Global variable as the root of the red black tree

void memoryManagerAddRecord(Node *allocateRoot,Record *record);
//void memoryManagerAddRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
Record *memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
