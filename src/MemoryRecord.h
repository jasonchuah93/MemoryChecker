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
int findRecordCompare(void *memoryFromRedBlackTree,void *memory);
int addDelRecordCompare(void **memoryFromRedBlackTree,void *memory);
Record *allocatedRecords(Record *record);
Record *freedRecords(Record *record);

#endif // MemoryRecord_H
