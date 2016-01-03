#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"
#include "ErrorCode.h"
#include "CException.h"

void _safeFree(void *memoryToFree,int lineNumber,char *fileName){
	int allocatedPoolCompare,freePoolCompare,compare;
	Node *freeNode,*foundNode,*leftPool;
	
	if(allocatedPool == NULL){
		printf("Trying to free NULL allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
		Throw(ERR_INVALID_POOL);
		//return;
	}else{
		allocatedPoolCompare = find(&allocatedPool,memoryToFree);
		if(allocatedPoolCompare == 1){
			foundNode = findRecord(&allocatedPool,memoryToFree);
			freeNode  = removeRecord(&allocatedPool,foundNode);
			addRecord(&freePool,freeNode);
		}else if(allocatedPoolCompare == 0){
			if(freePool!=NULL){
				freePoolCompare = find(&freePool,memoryToFree);
				if(freePoolCompare == 1){
					printf("Trying to free the same address twice at file: %s,line: %d\n",fileName,lineNumber);
					Throw(ERR_FREED_TWICE);
					return;
				}
			}
			printf("Trying to free incorrect memory address at file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_INVALID_ADDRESS);
			//return;
		}
		
	}
}