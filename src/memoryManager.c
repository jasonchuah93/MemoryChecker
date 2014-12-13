#include <stdio.h>
#include "MemoryRecord.h"
#include "Node.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"

void *memoryManagerAddRecord(Record *record){
    Node **rootPtr=NULL;
    Node *root;
    if(record->color == 'b'){
        if(root == NULL){
            *rootPtr = (Node*)record;
        }
    }else{
        printf("come not NULL\n");
       // genericAddRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);  
    }
    //return root;
}

void memoryManagerFindRecord(Node *root,void *targetRecord){
	
}

Record *memoryManagerDelRecord(Record *record){
	
}

