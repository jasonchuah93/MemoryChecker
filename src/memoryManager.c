#include <stdio.h>
#include <stdlib.h>
#include "MemoryRecord.h"
#include "Node.h"
#include "redBlackTree.h"
#include "memoryManager.h"

void *memoryManagerAddRecord(Record *record){
    Record *recordCompare;
    Node *nodeRecord =(Node*)record;
    genericAddRedBlackTree(nodeRecord,recordCompare);
}