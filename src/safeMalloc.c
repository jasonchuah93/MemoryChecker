#include <stdio.h>
#include <stdlib.h>
#include "safeMalloc.h"
#include "malloc.h"

#define BUFFER_SIZE 1000

void _safeMalloc(unsigned int size,int lineNumber, char *filename){
	printf("Requested to allocate %d size of memory\n and called "
			"from %s at %d line number\n",size,filename,lineNumber);
    
}

void *safeMalloc(unsigned int size,int lineNumber, char *filename){
	int *ptr;
    _safeMalloc(size,lineNumber,filename);
    
    return ptr;
}