#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"
#include "ErrorCode.h"
#include "CException.h"

void _safeFree(void *memoryToFree,int lineNumber,char *fileName){
	Record *allocatedRecord; Node *nodeToFree,*freeNode;
	allocatedRecord->memoryAllocateAddr = memoryToFree;
	allocatedRecord->lineNumber = lineNumber;
	allocatedRecord->fileName = fileName;
	nodeToFree->data = allocatedRecord;
	if(allocatedPool !=NULL){
		freeNode  = removeRecord(&allocatedPool,nodeToFree);
		addRecord(&freePool,freeNode);
	}else{ 
		printf("Trying to free NULL allocatedPool at file:%s,line:%d\n",fileName,lineNumber);
		Throw(ERR_INVALID_POOL);
	}
	
}