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

#endif // MemoryRecord_H
