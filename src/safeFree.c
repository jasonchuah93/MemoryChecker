#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"
#include "ErrorCode.h"
#include "CException.h"

void _safeFree(void *memoryToFree,int lineNumber,char *fileName){
	int allocatedPoolCompare,freePoolCompare,compare,compareHeaderStr,compareFooterStr;
	char *headerContent = HEADERCONTENT,*footerContent = FOOTERCONTENT;
	Node *freeNode,*foundNode,*headerFooterNode;
	if(allocatedPool == NULL){
		printf("Trying to free NULL allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
		Throw(ERR_INVALID_POOL);
		return;
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
					printf("Trying to free the same address twice \nin allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
					Throw(ERR_FREED_TWICE);
					return;
				}
			}
			printf("Trying to free incorrect memory address \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_INVALID_ADDRESS);
			return;
		}
	}
	//Check header and footer content
	if(freePool!=NULL){
		headerFooterNode = findRecord(&freePool,memoryToFree);
		compareHeaderStr = strcmp(memoryToFree-50,headerContent);
		compareFooterStr = strcmp(memoryToFree+memorySize(headerFooterNode),footerContent);
			if(compareHeaderStr == 0 && compareFooterStr == 0){
				return;
			}else if(compareHeaderStr != 0){
				if(compareFooterStr != 0){
					printf("Header and Footer memory had been modified in freePool \nat file: %s,line: %d\n",fileName,lineNumber);
					Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
				}else{
					printf("Header memory had been modified \nin freePool at file: %s,line: %d\n",fileName,lineNumber);
					Throw(ERR_CORRUPTED_HEADER_MEMORY);
				}
			}else if(compareFooterStr != 0){
				printf("Warning! Write into Footer memory in freePool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_FOOTER_MEMORY);
			}
		
	}
}

/*
This function is use the memory size to test the records in 
red black tree to check the node either move to left or right
*/
void _safeFreeTest(void *memoryToFree,int lineNumber,char *fileName){
	int allocatedPoolCompare,freePoolCompare,compare;
	Node *freeNode,*foundNode;
	if(allocatedPool == NULL){
		printf("Trying to free NULL allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
		Throw(ERR_INVALID_POOL);
		return;
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
					printf("Trying to free the same address twice \nat file: %s,line: %d\n",fileName,lineNumber);
					Throw(ERR_FREED_TWICE);
					return;
				}
			}
			printf("Trying to free incorrect memory address \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_INVALID_ADDRESS);
			return;
		}
	}
}