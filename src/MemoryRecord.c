#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryRecord.h"
#include "MallocWrapper.h"
#include "ErrorCode.h"
#include "CException.h"

/**
    This function will create descriptor with the input parameter.
    Return information in Record when the function end.
	Input : memoryBlock	the memory block allocated by user
			size		the size allocated by user
			lineNumber	the lineNumber allocated memory block
			fileName	the file location of allocated memory block
**/
Record *_createRecord(int size,void *memoryBlock,int lineNumber,char *fileName){
    if(size <= 0){
        printf("Invalid negative size at line %d from file %s\n",lineNumber,fileName);
        Throw(ERR_INVALID_NEGATIVE_SIZE);
    }
	Record *descriptor = (Record*)_malloc(sizeof(Record));
    descriptor->size = size;
	descriptor->headerAddr = ((Record*)memoryBlock)->headerAddr;
	descriptor->memoryAllocateAddr = ((Record*)memoryBlock)->memoryAllocateAddr;
    descriptor->footerAddr = ((Record*)memoryBlock)->footerAddr;
    descriptor->lineNumber = lineNumber;
    descriptor->fileName = fileName;
   
	return descriptor;
}

