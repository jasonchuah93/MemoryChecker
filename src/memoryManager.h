#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

//Global variable as the root of the red black tree
Node *root;

void memoryManagerAddRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
Record *memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
