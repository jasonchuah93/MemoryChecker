#include <stdio.h>
#include <stdlib.h>
#include "MemoryRecord.h"
#include "Node.h"
#include "redBlackTree.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"

void memoryManagerAddRecord(Record *record){
	Node *rootPtr;
    genericAddRedBlackTree((Node*)record);
    
}

void memoryManagerFindRecord(Record *record){
	
}

Record *memoryManagerDelRecord(Record *record){
	
}

