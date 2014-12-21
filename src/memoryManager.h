#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

void memoryManagerAddRecord(Record *record);
Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord);
Record *memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
