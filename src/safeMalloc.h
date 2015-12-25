#ifndef safeMalloc_H
#define safeMalloc_H

#include <stdlib.h>
#include <string.h>
#include "MallocWrapper.h"
#include "MemoryBlocks.h"
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"

#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

Node *allocatedPool,*freePool;

//Functions
void initializePool();
void *_safeMalloc(int unsigned size,int lineNumber, char *fileName);

//void resetAllocatedPool();
//void _checkHeaderMemoryContent(void *record,int lineNumber, char *fileName);
//void _checkFooterMemoryContent(void *record,int lineNumber, char *fileName);
//void saveSummary();


#endif // safeMalloc_H
