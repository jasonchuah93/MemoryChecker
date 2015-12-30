#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"
#include "ErrorCode.h"
#include "CException.h"

void _safeFree(void *memoryToFree,int lineNumber,char *fileName){
	int compare;
	Record *allocatedRecord; Node *nodeToFree,*freeNode;
	
	allocatedRecord->memoryAllocateAddr = memoryToFree;
	allocatedRecord->lineNumber = lineNumber;
	allocatedRecord->fileName = fileName;
	nodeToFree->data = allocatedRecord;
	if(allocatedPool !=NULL){
		if(freePool!=NULL){
			if(memoryToFree == memoryAddr(freePool)){
				printf("Trying to free the same address twice at file:%s,line:%d\n",fileName,lineNumber);
				Throw(ERR_FREED_TWICE);
			}
		}
		freeNode  = removeRecord(&allocatedPool,nodeToFree);
		addRecord(&freePool,freeNode);
	}else{ 
		printf("Trying to free NULL allocatedPool at file:%s,line:%d\n",fileName,lineNumber);
		Throw(ERR_INVALID_POOL);
	}
}