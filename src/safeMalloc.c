#include <stdio.h>
#include <stdlib.h>
#include "safeMalloc.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

#define BUFFER_SIZE 256 

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
	int i ;
    char *firstPtr,*lastPtr,*userPtr,content[256],tempContent ='5';
    printf("Requested to allocate %d size of memory\n and called "
			"from %s at %d line number\n",size,fileName,lineNumber);
    void *memory = malloc(sizeof(620));
   if(size<=620-size){
        firstPtr = memory+256;
        for(i=0;i<256;i++){
            content[i]=tempContent;
            if(tempContent=='5')
                tempContent = 'A';
            else
                tempContent = '5';
        }
        firstPtr = content;
    }
    
}

void safeFree(void *memoryToFree){
    free(memoryToFree);
}

