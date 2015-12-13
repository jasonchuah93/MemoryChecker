#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "MemoryRecord.h"
#include "MallocWrapper.h"
#include "ErrorCode.h"
#include "CException.h"

/**
    This function will allocateMemory when user input size
    Return information in Record type when the function end.
	Input : size		the size allocated by user
			lineNumber	the lineNumber allocated memory block
			fileName	the file location of allocated memory block
**/
void *_allocateMemory(int size,int lineNumber,char *fileName){
    if(size <= 0){
        return NULL;
    }
	//Alloc a memoryblock
    char *memoryBlockPtr = _malloc(sizeof(HEADER_SIZE+size+FOOTER_SIZE));
    //Put the memoryBlock to their pointer
    Record *recordPtr = malloc(sizeof(Record));
    recordPtr->headerAddr = memoryBlockPtr;
    recordPtr->memoryAllocateAddr = memoryBlockPtr+HEADER_SIZE;
    recordPtr->footerAddr = memoryBlockPtr+HEADER_SIZE+size;
    recordPtr->lineNumber = lineNumber;
    recordPtr->fileName = fileName;
    return recordPtr;
}

void freeMemory(void *memoryPtr){
    _free(memoryPtr);
}    

/**
    This function will create descriptor with the input parameter.
    Return information in Record when the function end.
	Input : memoryBlock	the memory block allocated by user
			size		the size allocated by user
			lineNumber	the lineNumber allocated memory block
			fileName	the file location of allocated memory block
**/
Record *_createRecord(int size,void *memoryBlock,int lineNumber,char *fileName){
    Record *descriptor = (Record*)malloc(sizeof(Record));
    descriptor->size = size;
	descriptor->headerAddr = ((Record*)memoryBlock)->headerAddr;
	descriptor->memoryAllocateAddr = ((Record*)memoryBlock)->memoryAllocateAddr;
    descriptor->footerAddr = ((Record*)memoryBlock)->footerAddr;
    descriptor->lineNumber = ((Record*)memoryBlock)->lineNumber;
    descriptor->fileName = ((Record*)memoryBlock)->fileName;
   
	return descriptor;
}


