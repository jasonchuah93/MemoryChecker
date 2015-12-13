#ifndef MemoryRecord_H
#define MemoryRecord_H

#define createRecord(size,memoryBlock) _createRecord(size,memoryBlock,__LINE__,__FILE__)
#define allocateMemory(size) _allocateMemory(size,__LINE__,__FILE__)

//Define the Memory Size for the allocator use.
#define HEADER_SIZE 	50
#define FOOTER_SIZE 	HEADER_SIZE

typedef struct Record Record;
struct Record{
    int size;
	char *headerAddr;
    char *memoryAllocateAddr;
    char *footerAddr;
    int lineNumber;
    char *fileName;
};

void *_allocateMemory(int size,int lineNumber,char *fileName);
void freeMemory(void *memoryPtr);
Record *_createRecord(int size,void *memoryBlock,int lineNumber,char *fileName);

#endif // MemoryRecord_H
