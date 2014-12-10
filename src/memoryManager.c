#include <stdio.h>
#include <stdlib.h>
#include "MemoryRecord.h"
#include "Node.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"

void *memoryManagerAddRecord(Record *record){
    if(record == NULL){
        Throw(ERR_EMPTY_RECORD);
    }
    
    
}

void memoryManagerFindRecord(Node *root,void *targetRecord){
	
}

Record *memoryManagerDelRecord(Record *record){
	
}

