#include <stdio.h>
#include "Node.h"
#include "MemoryRecord.h"

int findRecordCompare(Node **recordFromRedBlackTree,void *targetMemory){
	Record *_recordFromRedBlackTree=(Record*)*recordFromRedBlackTree;
    char *_targetMemory=(char*)targetMemory;
    if((char*)_recordFromRedBlackTree->memory > _targetMemory){
        return 1;
    }else if((char*)_recordFromRedBlackTree->memory < _targetMemory){
        return -1;
    }else
        return 0;
}

int addAndDelRecordCompare(Node **recordFromRedBlackTree,Record *targetRecord){
	Record *_recordFromRedBlackTree=(Record*)*recordFromRedBlackTree;
    if(_recordFromRedBlackTree->memory > targetRecord->memory)
        return 1;
    else if(_recordFromRedBlackTree->memory < targetRecord->memory)
        return -1;
    else
        return 0;
    
}



