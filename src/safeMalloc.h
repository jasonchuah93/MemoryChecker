#ifndef safeMalloc_H
#define safeMalloc_H

#include"MemoryRecord.h"

int *preMemorySize(int size);
int *postMemorySize(int size);
void *_safeMalloc(int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);

#endif // safeMalloc_H
