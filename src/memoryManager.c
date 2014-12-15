#include <stdio.h>
#include "MemoryRecord.h"
#include "Node.h"
#include "NodePtr.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"

void memoryManagerAddRecord(Record *record){
    if(root == NULL){
        genericAddRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    }else{
        genericAddRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    }
}

Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord){
	Record *target=NULL;
    target = (Record*)genericFindRedBlackTree(&root,(void*)targetRecord,findRecordCompare);
    return target;
}


Record *memoryManagerDelRecord(Record *record){
	Record *deletedRecord;
    deletedRecord = (Record*)genericDelRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    return deletedRecord;
}

