#ifndef safeMalloc_H
#define safeMalloc_H

//Define the Memory Size for the allocator use.
#define BUFFER_SIZE     500
#define HEADER_SIZE 	15
#define FOOTER_SIZE 	HEADER_SIZE
//Define the function for easy purpose of use
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)
//Global variable

Record *allocateRecord;
void *memoryPool;
void *headerBlock;
void *footerBlock;


//Functions
void memoryInitialization();
void *_safeMalloc(unsigned int size,int lineNumber, char *fileName);
void *testMalloc(int size);

#endif // safeMalloc_H
