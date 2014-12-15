#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

Record *memoryManagerAddRecord(Record *record);
void memoryManagerFindRecord(Node *root,void *targetRecord);
Record *memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
