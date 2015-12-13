#ifndef safeMalloc_H
#define safeMalloc_H

//Define the function for easy purpose of use
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)
#define checkHeaderMemoryContent(record) _checkHeaderMemoryContent(record,__LINE__,__FILE__)
#define checkFooterMemoryContent(record) _checkFooterMemoryContent(record,__LINE__,__FILE__)
#define getMemory(node) (((Record*)node)->memoryAddr)
#define getSize(node) (((Record*)node)->size)
//Functions
void *_safeMalloc(int size,int lineNumber, char *fileName);
void safeFree(void *memoryToFree);
void resetAllocatedPool();
void _checkHeaderMemoryContent(void *record,int lineNumber, char *fileName);
void _checkFooterMemoryContent(void *record,int lineNumber, char *fileName);
void saveSummary();


#endif // safeMalloc_H
