#ifndef memoryManager_H
#define memoryManager_H

#include "MemoryRecord.h"

void memoryManagerAddRecord(Record *record);
void memoryManagerFindRecord(Record *record);
Record *memoryManagerDelRecord(Record *record);

#endif // memoryManager_H
