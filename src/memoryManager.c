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

/*********************************************************************
* This function will add a new record into the tree
*
*	Input: 	record		the record that going to add into the tree
*
*	Destroy: none
*	
**********************************************************************/

void memoryManagerAddRecord(Record *record){
    if(root == NULL){
        genericAddRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    }else{
        genericAddRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    }
}

/*********************************************************************
* This function will find record in the tree
*
*	Input: 	rootPtr			the main root of the tree	
*			targetRecord	the record that going to find in the tree
*	
*	Output:	target		the found record
*	
*	Destroy: none
*	
**********************************************************************/

Record *memoryManagerFindRecord(Node *rootPtr,void *targetRecord){
	Record *target=NULL;
    target = (Record*)genericFindRedBlackTree(&root,(void*)targetRecord,findRecordCompare);
    return target;
}

/*********************************************************************
* This function will delete record in the tree
*
*	Input: 	record				the record that going to add into the tree
*			
*	Output:	deleteRecord		the deleted record
*	
*	Destroy: none
*	
**********************************************************************/

Record *memoryManagerDelRecord(Record *record){
	Record *deletedRecord;
    deletedRecord = (Record*)genericDelRedBlackTree(&root,(Node*)record,addAndDelRecordCompare);
    return deletedRecord;
}


