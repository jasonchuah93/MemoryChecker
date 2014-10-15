#include "MemoryChecker.h"

#define safeMalloc(size) _safeMalloc_(size,__LINE__,__FILE__)

void _safeMalloc_(unsigned int size,int lineNumber, char *filename){
	printf("requested to allocate %d this much of memory\n And called"
			"from %s at %d line number\n",size,filename,lineNumber);
}

void test_lineNumber(){

  safeMalloc(100);
}