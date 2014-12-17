#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

//Global variable which will be use for the functions below
Node *root;

void memoryManagerAddRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
Record *memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
