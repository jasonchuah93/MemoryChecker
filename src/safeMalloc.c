#include <stdio.h>
#include <stdlib.h>
#include "safeMalloc.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

#define BUFFER_SIZE 256 

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
	int i ;
    char *firstPtr,*lastPtr,*userPtr;
    
    //printf("Requested to allocate %d size of memory\n and called "
			//"from %s at %d line number\n",size,fileName,lineNumber);
    void *memory = malloc(sizeof(620));
    *((char*)memory)='5';
    for(i=0;i<256;i++){
        if(*((char*)memory)=='5')
            *((char*)memory) = 'A';
        else
            *((char*)memory) = '5';
    }
    
    return memory;
}

void safeFree(void *memoryToFree){
    free(memoryToFree);
}

