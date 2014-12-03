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

int findRecordCompare(void *memoryFromRedBlackTree,void *memory){
	char *_memory = (char *)memory;
	Record *_memoryFromRedBlackTree = (Record *)memoryFromRedBlackTree;

	if(_memoryFromRedBlackTree->memory > memory){
		return 1;
	}else if(_memoryFromRedBlackTree->memory < memory){
		return -1;
	}else{
		return 0;
	}
}

int addDelRecordCompare(void **memoryFromRedBlackTree,void *memory){
	Node *memoryRoot = (Node*)*memoryFromRedBlackTree;
    Node *newMemoryRoot = (Node*)memory;
    
    Record *_memoryFromRedBlackTree = (Record*)(memoryRoot->memoryData);
    Record *_memory = (Record *)(newMemoryRoot->memoryData);
	
	if(_memoryFromRedBlackTree->size > _memory->size){
		return 1;
	}else if(_memoryFromRedBlackTree->size < _memory->size){
		return -1;
	}else{
		return 0;
	}
}

Record *allocatedRecords(Record *record){
    
}

Record *freedRecords(Record *record){

}


