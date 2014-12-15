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

/*
void memoryManagerFindRecord(Node *root,void *targetRecord){
	
}

Record *memoryManagerDelRecord(Record *record){
	
}
*/
