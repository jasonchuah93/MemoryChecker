#ifndef safeFree_H
#define safeFree_H

#define HEADERCONTENT "##############################"
#define FOOTERCONTENT "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"
#define safeFree(memoryToFree) _safeFree(memoryToFree,__LINE__,__FILE__)
#define safeFreeTest(memoryToFree) _safeFreeTest(memoryToFree,__LINE__,__FILE__)

void _safeFree(void *memoryToFree,int lineNumber,char *fileName);
void _safeFreeTest(void *memoryToFree,int lineNumber,char *fileName);
#endif // safeFree_H