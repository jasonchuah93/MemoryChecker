#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "memoryAllocator.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
    
	if(size == 0){
        return NULL;
    }else if(size > BUFFER_SIZE){
        printf("Out of Buffer Size at line %d from file %s\n",lineNumber,fileName);
        Throw(ERR_EXCEED_BUFFER_SIZE);
    }
	headerBlock = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	headerBlock = (void*)"5A5A5A5A5A5A5A";
    footerBlock = headerBlock+HEADER_SIZE+size;
    footerBlock = (void*)"5A5A5A5A5A5A5A";
    pointerToMemoryBlock = headerBlock+HEADER_SIZE;
    pointerToMemoryBlock = (void*)"1A1A1A1A1A";
    printf("MEMORY header pointer : %p\n",headerBlock);
    printf("Pointer : %p\n",pointerToMemoryBlock);
    printf("MEMORY footer pointer : %p\n",footerBlock);
    printf("MEMORY BLOCK content : %s\n",headerBlock);
    printf("MEMORY FOOTER content : %s\n",footerBlock);
    printf("User input content : %s\n",pointerToMemoryBlock);
    newRecord = createRecord(pointerToMemoryBlock,size);
	memoryManagerAddRecord(newRecord);
	return pointerToMemoryBlock;
}

void safeFree(void *memoryToFree){
   memoryManagerDelRecord(newRecord);
}

