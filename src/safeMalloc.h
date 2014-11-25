#ifndef safeMalloc_H
#define safeMalloc_H

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);

#endif // safeMalloc_H
