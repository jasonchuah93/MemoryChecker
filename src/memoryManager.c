#include <stdio.h>
#include <malloc.h>
#include "MemoryRecord.h"
#include "Node.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"

/*********************************************************************
* This function will create a memory pool to allocate memory
*
*	Input: memorySize --> user can input the size of allocation
*                         if user input 0, the program will use the default 
                          memory size
*	Destroy: none
*	
**********************************************************************/
void *initializeMemoryPool(int memorySize){
	if(memorySize == 0){
		memorySize = DEFAULT_MEMORY_SIZE;
	}
	Pool *newPool = malloc(sizeof(Pool));
	newPool->size = memorySize;
	newPool->memoryAddr = memoryPool;
	
	return newPool;
}
/*********************************************************************
* This function will allocate a new record into the allocatedPool
*
*	Input: 	record		the record that going to add into the tree
*
*	Destroy: none
*	
**********************************************************************/

void memoryManagerAllocateRecord(Record *record){
    if(allocatedPool == NULL){
        genericAddRedBlackTree(&allocatedPool,(Node*)record,addAndDelRecordCompare);
    }else{
        genericAddRedBlackTree(&allocatedPool,(Node*)record,addAndDelRecordCompare);
    }
}

/*********************************************************************
* This function will dellocate a record from the allocatedPool
* and place into freePool
*	Input: 	record		the record that going to add into the tree
*
*	Destroy: none
*	
**********************************************************************/

void memoryManagerFreeRecord(Record *record){
    if(freePool == NULL){
        genericAddRedBlackTree(&freePool,(Node*)record,addAndDelRecordCompare);
    }else{
        genericAddRedBlackTree(&freePool,(Node*)record,addAndDelRecordCompare);
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
    target =(Record*)genericFindRedBlackTree(&rootPtr,(void*)targetRecord,findRecordCompare);
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

void memoryManagerDelRecord(Record *record){
	genericDelRedBlackTree(&allocatedPool,(Node*)record,addAndDelRecordCompare);
}


