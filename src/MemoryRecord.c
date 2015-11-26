#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "MemoryRecord.h"
#include "ErrorCode.h"
#include "CException.h"

/**
    This function will create record with the input parameter.
    Return information in Record when the function end.
	Input : memory		the memory of user requested
			size		the size of user requested
			lineNumber	the lineNumber of each code
			fileName	the location of file of the functions written
**/
Record *_createRecord(void *memory,int size,int lineNumber,char *fileName){
    if(size <= 0){
        printf("Invalid size at line %d from file %s\n",lineNumber,fileName);
        Throw(ERR_INVALID_SIZE);
    }
    Record *record = (Record*)malloc(sizeof(Record));
    record->memoryAddr = ((Record*)memory)->memoryAddr;
    record->headerAddr = ((Record*)memory)->headerAddr;
    record->footerAddr = ((Record*)memory)->footerAddr;
    record->size = size;
    record->lineNumber = lineNumber;
    record->fileName = fileName;
    record->left = NULL;
    record->right = NULL;
    record->color = 'b';
	
    return record;
}

/**
    This function will create node which contain a record as the input parameter.
    Return information in node when the function end.
	Input  : Record
    Output : node
**/

Node *_createNode(Record *record){
    Node *node  = malloc(sizeof(Node));
    node->data  = record;
    node->left  = NULL;
    node->right = NULL;
    node->color ='b';
    
    return node;
}
