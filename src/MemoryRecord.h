#ifndef MemoryRecord_H
#define MemoryRecord_H

#include "Node.h"

typedef struct Record Record;

struct Record{
    Node *node;
    void *memory;
    int size;
    int lineNumber;
    char *fileName;
};

Record *_createRecord(void *memory,int size,int lineNumber,char *fileName);
int findRecordCompare(void *memory,void *memoryFromRedBlackTree);
int addDelRecordCompare(void *memory,void *memoryFromRedBlackTree);

#endif // MemoryRecord_H
