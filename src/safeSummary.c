#include <stdio.h>
#include "safeMalloc.h"
#include "safeFree.h"
#include "safeSummary.h"
#include "ErrorCode.h"
#include "CException.h"

void _safeSummary(int lineNumber,char *fileName){
	int compareHeaderStr,compareFooterStr;
	char *headerContent = HEADERCONTENT,*footerContent = FOOTERCONTENT;
	//AllocatedPool
	if(allocatedPool !=NULL){
		compareHeaderStr = strcmp(memoryAddr(allocatedPool)-50,headerContent);
		compareFooterStr = strcmp(memoryAddr(allocatedPool)+memorySize(allocatedPool),footerContent);
		if(compareHeaderStr != 0){
			if(compareFooterStr !=0){
				printf("Header and Footer memory had been modified in root of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
			}else{
				printf("Header memory had been modified in root of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_MEMORY);
			}
		}else if(compareFooterStr !=0){
			printf("Footer memory had been modified in root of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_CORRUPTED_FOOTER_MEMORY);
		}
	}else{
		printf("No record in allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
		return;
	}
	if(allocatedPool->left !=NULL){
		compareHeaderStr = strcmp(memoryAddr(allocatedPool->left)-50,headerContent);
		compareFooterStr = strcmp(memoryAddr(allocatedPool->left)+memorySize(allocatedPool->left),footerContent);
		if(compareHeaderStr != 0){
			if(compareFooterStr !=0){
				printf("Header and Footer memory had been modified in left node of \nthe allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
			}else{
				printf("Header memory had been modified in left node of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_MEMORY);
			}
		}else if(compareFooterStr !=0){
			printf("Footer memory had been modified in left node of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_CORRUPTED_FOOTER_MEMORY);
		}
	}
	if(allocatedPool->right !=NULL){
		compareHeaderStr = strcmp(memoryAddr(allocatedPool->right)-50,headerContent);
		compareFooterStr = strcmp(memoryAddr(allocatedPool->right)+memorySize(allocatedPool->right),footerContent);
		if(compareHeaderStr != 0){
			if(compareFooterStr !=0){
				printf("Header and Footer memory had been modified in right node of \nthe allocatedPool at file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
			}else{
				printf("Header memory had been modified in right node of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_MEMORY);
			}
		}else if(compareFooterStr !=0){
			printf("Footer memory had been modified in right node of the allocatedPool \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_CORRUPTED_FOOTER_MEMORY);
			
		}
	}
	//FreePool
	if(freePool !=NULL){
		compareHeaderStr = strcmp(memoryAddr(freePool)-50,headerContent);
		compareFooterStr = strcmp(memoryAddr(freePool)+memorySize(freePool),footerContent);
		if(compareHeaderStr != 0){
			if(compareFooterStr !=0){
				printf("Header and Footer memory had been modified in root of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
			}else{
				printf("Header memory had been modified in root of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_MEMORY);
			}
		}else if(compareFooterStr !=0){
			printf("Footer memory had been modified in root of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_CORRUPTED_FOOTER_MEMORY);
		}
	}else{
		printf("No record in freePool at file: %s,line: %d\n",fileName,lineNumber);
		return;
	}
	if(freePool->left !=NULL){
		compareHeaderStr = strcmp(memoryAddr(freePool->left)-50,headerContent);
		compareFooterStr = strcmp(memoryAddr(freePool->left)+memorySize(freePool->left),footerContent);
		if(compareHeaderStr != 0){
			if(compareFooterStr !=0){
				printf("Header and Footer memory had been modified in left node of \nthe freePool at file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
			}else{
				printf("Header memory had been modified in left node of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_MEMORY);
			}
		}else if(compareFooterStr !=0){
			printf("Footer memory had been modified in left node of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_CORRUPTED_FOOTER_MEMORY);
		}
	}
	if(freePool->right !=NULL){
		compareHeaderStr = strcmp(memoryAddr(freePool->right)-50,headerContent);
		compareFooterStr = strcmp(memoryAddr(freePool->right)+memorySize(freePool->right),footerContent);
		if(compareHeaderStr != 0){
			if(compareFooterStr !=0){
				printf("Header and Footer memory had been modified in right node of \nthe freePool at file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_FOOTER_MEMORY);
			}else{
				printf("Header memory had been modified in right node of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
				Throw(ERR_CORRUPTED_HEADER_MEMORY);
			}
		}else if(compareFooterStr !=0){
			printf("Footer memory had been modified in right node of the freePool \nat file: %s,line: %d\n",fileName,lineNumber);
			Throw(ERR_CORRUPTED_FOOTER_MEMORY);
			
		}
	}
}