#ifndef safeMalloc_H
#define safeMalloc_H

//Define the Memory Size for the allocator use.
#define BUFFER_SIZE 1024
#define HEADER_MEMORY 	"5A5A5A5A5A"
#define HEADER_SIZE 	sizeof(HEADER_MEMORY)
#define FOOTER_MEMORY 	HEADER_MEMORY
#define FOOTER_SIZE 	sizeof(FOOTER_MEMORY)
//Define the function for easy purpose of use
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)
//Global variable
void *memoryPool;
Node *allocatedPool;

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);

#endif // safeMalloc_H
