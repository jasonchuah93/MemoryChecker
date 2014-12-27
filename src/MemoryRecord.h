#ifndef MemoryRecord_H
#define MemoryRecord_H

#include "Node.h"

//For friendly use without extra parameter
#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

typedef struct Record Record;

struct Record{
    //Record structure
    void *memory;
    unsigned int size;
    int lineNumber;
    char *fileName;
};

Record *_createRecord(void *memory,int size,int lineNumber,char *fileName);
Node *createNode(Record *record);

#endif // MemoryRecord_H
