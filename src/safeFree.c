#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"

void _safeFree(void *memoryToFree,int lineNumber,char *fileName){
	Allocation *allocatedMemory; Record *allocatedRecord; Node *nodeToFree,*freeNode;
	allocatedMemory->memoryAllocateAddr = memoryToFree;
	allocatedMemory->lineNumber = lineNumber;
	allocatedMemory->fileName = fileName;
	allocatedRecord->memoryAllocateAddr = allocatedMemory->memoryAllocateAddr;
	allocatedRecord->lineNumber = allocatedMemory->lineNumber;
	allocatedRecord->fileName = allocatedMemory->fileName;
	nodeToFree->data = allocatedRecord;
	freeNode  = removeRecord(&allocatedPool,nodeToFree);
	addRecord(&freePool,freeNode);
	
}