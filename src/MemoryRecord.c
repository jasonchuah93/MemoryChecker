#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "MemoryRecord.h"

/**
    This function will create record for the input parameter.
    Return record when the function end.
**/
Record *_createRecord(char *memory,int size,int lineNumber,char *fileName){
    Record *record;
    record = malloc(size);
    record->memory =memory;
    record->size = size;
    record->lineNumber = lineNumber;
    record->fileName = fileName;
    return record;
}

int findRecordCompare(void *memory,void *memoryFromRedBlackTree){
	char *_memory = (char *)memory;
	Record *_memoryFromRedBlackTree = (Record *)memoryFromRedBlackTree;
	
	if(_memory > (char*)_memoryFromRedBlackTree->memory){
		return 1;
	}else if(_memory < (char*)_memoryFromRedBlackTree->memory){
		return -1;
	}else{
		return 0;
	}
}

int addDelRecordCompare(void *memory,void *memoryFromRedBlackTree){
	Record *_memory = (Record *)memory;
	Record *_memoryFromRedBlackTree = (Record *)memoryFromRedBlackTree;
	
	if(_memory > (Record*)_memoryFromRedBlackTree->memory){
		return 1;
	}else if(_memory < (Record*)_memoryFromRedBlackTree->memory){
		return -1;
	}else{
		return 0;
	}
}


