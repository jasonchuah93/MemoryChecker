#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "MemoryRecord.h"

/**
    This function will create record with the input parameter.
    Return information in Record when the function end.
	Input : memory		the memory of user requested
			size		the size of user requested
			lineNumber	the lineNumber of each code
			fileName	the location of file of the functions written
**/
Record *_createRecord(void *memory,int size,int lineNumber,char *fileName){
    Record *record = malloc(sizeof(Record));
    record->memory = memory;
    record->size = size;
    record->lineNumber = lineNumber;
    record->fileName = fileName;
	return record;
}

Node *_createNode(void *memory,int size,int lineNumber,char *fileName){
    Record *record = malloc(sizeof(Record));
    Node *node  = malloc(sizeof(Node));
    record->memory =memory;
    record->size = size;
    record->lineNumber = lineNumber;
    record->fileName = fileName;
	node->data  = record;
    node->left  = NULL;
    node->right = NULL;
    node->color ='b';
    
    return node;
}