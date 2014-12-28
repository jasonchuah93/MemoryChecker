#ifndef safeMalloc_H
#define safeMalloc_H

//Define the Memory Size for the allocator use.
#define BUFFER_SIZE     500
#define HEADER_SIZE 	15
#define FOOTER_SIZE 	HEADER_SIZE
//Define the function for easy purpose of use
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)
#define checkMemoryContent(record) _checkMemoryContent(record,__LINE__,__FILE__)
#define getMemory(node) (((Record*)((Node*)(node))->data)->memory)
#define getSize(node) (((Record*)((Node*)(node))->data)->size)

//Global variable
void *memoryPool;
Node *allocatePool;
Node *freePool;


//Functions
void *_safeMalloc(int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);
void resetAllocatedPool();
void _checkMemoryContent(void *record,int lineNumber, char *fileName);
void safeSummary();

#endif // safeMalloc_H
