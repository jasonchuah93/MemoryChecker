#include <stdio.h>
#include "safeMalloc.h"

void _safeMalloc(unsigned int size,int lineNumber, char *filename){
	printf("Requested to allocate %d size of memory\n and called "
			"from %s at %d line number\n",size,filename,lineNumber);
}

void *safeMalloc(unsigned int size,int lineNumber, char *filename){
	//_safeMalloc(size,lineNumber,filename);
}