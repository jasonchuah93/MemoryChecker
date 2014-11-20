#ifndef MemoryRecord_H
#define MemoryRecord_H

typedef struct Record Record;

struct Record{
    void *memory;
    int size;
    int lineNumber;
    char *fileName;
};

void *addRecord(void *memory,int size,int lineNumber,char *fileName);
Record *delRecord(void *memory,int size,int lineNumber,char *fileName);
Record *findRecord(void *memory,int size,int lineNumber,char *fileName);

#endif // MemoryRecord_H
