#ifndef safeMalloc_H
#define safeMalloc_H

#define BUFFER_SIZE 256 

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);

#endif // safeMalloc_H
