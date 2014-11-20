#include <stdio.h>
#include <stdlib.h>
#include "MemoryRecord.h"

void *addRecord(void *memory,int size,int lineNumber,char *fileName){
    Record *record = malloc(sizeof(Record));
    record->memory= memory;
    record->size= size;
    record->lineNumber =lineNumber;
    record->fileName = fileName;
}




