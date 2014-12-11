#ifndef MemoryRecord_H
#define MemoryRecord_H

#include "Node.h"
#include "NodePtr.h"

#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

typedef struct Record Record;

struct Record{
    //Node structure
    Node *left;
    Node *right;
    char color; // 'b' or 'r'(black or red)
    int data;
    //Record structure
    void *memory;
    int size;
    int lineNumber;
    char *fileName;
};

Record *_createRecord(char *memory,int size,int lineNumber,char *fileName);

#endif // MemoryRecord_H
