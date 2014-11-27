#ifndef MemoryRecord_H
#define MemoryRecord_H

#include "Node.h"

#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

typedef struct Record Record;

struct Record{
    Node *node;
    void *memory;
    int size;
    int lineNumber;
    char *fileName;
};

Record *_createRecord(char *memory,int size,int lineNumber,char *fileName);
int findRecordCompare(void *memory,void *memoryFromRedBlackTree);
int addDelRecordCompare(void *memory,void *memoryFromRedBlackTree);

#endif // MemoryRecord_H
