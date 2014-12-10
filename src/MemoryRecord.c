#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "NodePtr.h"
#include "MemoryRecord.h"

/**
    This function will create record for the input parameter.
    Return record when the function end.
**/
Record *_createRecord(char *memory,int size,int lineNumber,char *fileName){
    Record *record = malloc(sizeof(Record));
    record->memory =memory;
    record->size = size;
    record->lineNumber = lineNumber;
    record->fileName = fileName;
    return record;
}




