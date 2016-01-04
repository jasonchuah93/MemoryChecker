#ifndef MemoryRecord_H
#define MemoryRecord_H

#define HEADERCONTENT "1############################5A5A5A5A5A5A5A5A5A5A"
#define FOOTERCONTENT "1&&&&&&&&&&&&&&&&&&&&&&&&&&&&5A5A5A5A5A5A5A5A5A5A"
#define createRecord(memoryBlock) _createRecord(memoryBlock,__LINE__,__FILE__)
#define allocateMemory(size) _allocateMemory(size,__LINE__,__FILE__)

#include <stdlib.h>
#include <string.h>
#include "MallocWrapper.h"
#include "MemoryBlocks.h"

typedef struct Allocation Allocation;
struct Allocation{
    int unsigned size;
	char *headerAddr;
    char *memoryAllocateAddr;
    char *footerAddr;
    int lineNumber;
    char *fileName;
};

typedef struct Record Record;
struct Record{
    int unsigned size;
	char *headerAddr;
    char *memoryAllocateAddr;
    char *footerAddr;
    int lineNumber;
    char *fileName;
};

Allocation *_allocateMemory(int unsigned size,int lineNumber,char *fileName);
Record *_createRecord(Allocation *memoryBlock,int lineNumber,char *fileName);
void freeMemory(void *memoryPtr);

#endif // MemoryRecord_H
