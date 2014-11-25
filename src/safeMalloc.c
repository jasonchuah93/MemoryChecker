#include <stdio.h>
#include <stdlib.h>
#include "safeMalloc.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

#define BUFFER_SIZE 256 

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
    printf("Requested to allocate %d size of memory\n and called "
			"from %s at %d line number\n",size,fileName,lineNumber);
    
}

void safeFree(void *memoryToFree){
    free(memoryToFree);
}

