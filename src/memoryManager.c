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

Record *memoryManagerAddRecord(Record *record){
    Node *root;
    genericAddRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    return (Record*)root;
}

void memoryManagerFindRecord(Node *root,void *targetRecord){
	
}

Record *memoryManagerDelRecord(Record *record){
	
}

