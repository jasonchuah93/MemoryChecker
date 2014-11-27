#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "redBlackTree.h"
#include "memoryAllocator.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

#define BUFFER_SIZE 256 
#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
    int i; Record *record;
    printf("Requested to allocate %d size of memory\n and called "
			"from %s at %d line number \n",size,fileName,lineNumber);
    void *memory = allocateMemory(BUFFER_SIZE+size+BUFFER_SIZE);
    if(size > 1000){
        Throw(ERR_EXCEED_ALLOCATED_MEMORY);
        return 0;
    }
    *((char*)memory)='5';
	for(i=0;i<256;i++){
        if(*((char*)memory)=='5'){
            *((char*)memory) = 'A';
		}else if(*((char*)memory)=='A')
            *((char*)memory)='5';
	}
    record = createRecord(memory,size);
    
}

void safeFree(void *memoryToFree){
    free(memoryToFree);
}

