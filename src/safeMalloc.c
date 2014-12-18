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
   Record *newRecord;
	if(size == 0){
        return NULL;
    }else if(size > BUFFER_SIZE){
        printf("Out of Buffer Size at line %d from file %s\n",lineNumber,fileName);
        Throw(ERR_EXCEED_BUFFER_SIZE);
    }
	//Create header of the memory block
	/*
	int header = size+sizeof(Record);
	void *pointerHeader = malloc(header);
	Record *recordHeader = (Record*)pointerHeader;
	recordHeader->size = size;
	*/
	void *memoryBlock = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	newRecord = createRecord((Record*)memoryBlock,size);
	memoryManagerAddRecord(newRecord);
	
}

void safeFree(void *memoryToFree){
   
}

