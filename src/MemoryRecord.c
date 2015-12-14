#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MemoryRecord.h"

/**
    This function will allocateMemory when user input size
    Return information in Record type when the function end.
	Input : size		the size allocated by user
			lineNumber	the lineNumber allocated memory block
			fileName	the file location of allocated memory block
**/
Allocation *_allocateMemory(int unsigned size,int lineNumber,char *fileName){
    char *headerPtr,*sizePtr,*footerPtr;
    if(size == 0)
        return NULL;
    else{
        //Allocate a memoryblock and return the first pointer 
        headerPtr = _malloc(sizeof(HEADER_SIZE+size+FOOTER_SIZE));
        sizePtr = headerPtr+HEADER_SIZE;
        footerPtr = sizePtr+size;
        Allocation *allocate = (Allocation*)malloc(sizeof(Allocation));
        allocate->size = size;
        allocate->headerAddr = headerPtr;
        allocate->memoryAllocateAddr = sizePtr;
        allocate->footerAddr = footerPtr;
        allocate->lineNumber = lineNumber;
        allocate->fileName = fileName;
        return allocate;
    }
}

/**
    This function will create descriptor with the input parameter.
    Return information in Record when the function end.
	Input : memoryBlock	the memory block allocated by user
			size		the size allocated by user
			lineNumber	the lineNumber allocated memory block
			fileName	the file location of allocated memory block
**/
Record *_createRecord(int unsigned size,void *memoryBlock,int lineNumber,char *fileName){
    Record *descriptor = (Record*)malloc(sizeof(Record));
    descriptor->size = size;
	descriptor->headerAddr = ((Allocation*)memoryBlock)->headerAddr;
	descriptor->memoryAllocateAddr = ((Allocation*)memoryBlock)->memoryAllocateAddr;
    descriptor->footerAddr = ((Allocation*)memoryBlock)->footerAddr;
    descriptor->lineNumber = ((Allocation*)memoryBlock)->lineNumber;
    descriptor->fileName = ((Allocation*)memoryBlock)->fileName;
   
	return descriptor;
}


void freeMemory(void *memoryPtr){
    _free(memoryPtr);
}    
