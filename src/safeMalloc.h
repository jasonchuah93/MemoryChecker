#ifndef safeMalloc_H
#define safeMalloc_H

//Define the Memory Size for the allocator use.
#define BUFFER_SIZE 1024
//Define the function for easy purpose of use
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);

#endif // safeMalloc_H
