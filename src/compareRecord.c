#include <stdio.h>
#include "Node.h"
#include "MemoryRecord.h"

int findRecordCompare(void *memoryFromRedBlackTree,void *newMemory){
	char *_newMemory=(char*)newMemory;
    Record *_memoryFromRedBlackTree=(Record*)memoryFromRedBlackTree;
    if((char*)_memoryFromRedBlackTree->memory > _newMemory)
        return 1;
    else if((char*)_memoryFromRedBlackTree->memory < _newMemory)
        return -1;
    else
        return 0;
}

int addAndDelRecordCompare(void **memoryFromRedBlackTree,void *newMemory){
	Node *nodeMemoryFromRedBlackTree = (Node*)*memoryFromRedBlackTree;
    Node *nodeNewMemory = (Node*)newMemory;
    
    Record *recordMemoryFromRedBlackTree=(Record*)(nodeMemoryFromRedBlackTree->dataPtr);
    Record *recordNewMemory=(Record*)(nodeNewMemory->dataPtr);
    
    if(recordMemoryFromRedBlackTree->size > recordNewMemory->size)
        return 1;
    else if(recordMemoryFromRedBlackTree->size < recordNewMemory->size)
        return -1;
    else
        return 0;
    
}



