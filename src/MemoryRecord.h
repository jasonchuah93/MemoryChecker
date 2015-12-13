#ifndef MemoryRecord_H
#define MemoryRecord_H

#define createRecord(size,memoryBlock) _createRecord(size,memoryBlock,__LINE__,__FILE__)

typedef struct Record Record;
struct Record{
    int size;
	char *headerAddr;
    char *memoryAllocateAddr;
    char *footerAddr;
    int lineNumber;
    char *fileName;
};

Record *_createRecord(int size,void *memoryBlock,int lineNumber,char *fileName);

#endif // MemoryRecord_H
