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

#define safeMallocTest(size) _safeMallocTest(size,__LINE__,__FILE__)
#define safeMalloc(size) _safeMalloc(size,__LINE__,__FILE__)

Node *allocatedPool,*freePool;

//Functions
void initializePool();
void *_safeMallocTest(int unsigned size,int lineNumber, char *fileName);
void *_safeMalloc(int unsigned size,int lineNumber, char *fileName);

#endif // safeMalloc_H
