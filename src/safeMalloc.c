#include <stdio.h>
#include <stdlib.h>
#include "safeMalloc.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

#define BUFFER_SIZE 256

int *preMemorySize(int size){
    
    size = BUFFER_SIZE;
    return (int*)size;
}

int *postMemorySize(int size){
    size = BUFFER_SIZE;
    return (int*)size;
}

void *_safeMalloc(int size,int lineNumber, char *fileName){
	printf("Requested to allocate %d size of memory\n and called "
			"from %s at %d line number\n",size,fileName,lineNumber);
    void *memory = malloc(sizeof(size+BUFFER_SIZE));
    addRecord(memory,size,lineNumber,fileName);
    
    return memory;
}

void safeFree(void *memoryToFree){
    free(memoryToFree);
}

