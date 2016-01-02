#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"
#include "ErrorCode.h"
#include "CException.h"

void _safeFree(void *memoryToFree,int lineNumber,char *fileName){
	int compare;
	Record *allocatedRecord; 
	Node *nodeToFree,*freeNode,foundNode;
	if(allocatedPool == NULL){
		printf("Trying to free NULL allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
		Throw(ERR_INVALID_POOL);
	}else{
		compare = find(&allocatedPool,memoryToFree);
		if(compare == 1){
			allocatedRecord->memoryAllocateAddr = memoryToFree;
			allocatedRecord->lineNumber = lineNumber;
			allocatedRecord->fileName = fileName;
			nodeToFree = createNode(allocatedRecord);
			freeNode  = removeRecord(&allocatedPool,nodeToFree);
			addRecord(&freePool,freeNode);
		}else if(compare == 0){
			printf("Trying to free address not in allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_INVALID_ADDRESS);
		}
	}
}