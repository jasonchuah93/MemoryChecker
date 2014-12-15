#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "MemoryRecord.h"

/**
    This function will create record for the input parameter.
    Return information in Record when the function end.
**/
Record *_createRecord(void *memory,int size,int lineNumber,char *fileName){
    Record *record = malloc(sizeof(Record));
    record->memory =memory;
    record->size = size;
    record->lineNumber = lineNumber;
    record->fileName = fileName;
    return record;
}

void destroyRecord(Record *record){
    if(record){
        record->memory = NULL;
        record->size = 0;
    }
    free(record);
}



