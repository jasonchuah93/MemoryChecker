#ifndef safeMalloc_H
#define safeMalloc_H

#define BUFFER_SIZE 512 
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)
void *_safeMalloc(unsigned int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);

#endif // safeMalloc_H
