#include <stdio.h>
#include "safeMalloc.h"

/*********************************************************************
* This function will initialize allocated pool to null
*	Destroy: none
**********************************************************************/
void initializePool(){
	allocatedPool = NULL;
	freePool = NULL;
}

/*********************************************************************
* This function will allocate memory and create the relevant descriptor
* then add inside the allocated pool
*
*	Destroy: none
*	
**********************************************************************/
void *_safeMalloc(int unsigned size,int lineNumber, char *fileName){
    //Allocate a memory Block which consist of 3 segments
    /****************************************************
     |  HEADER      |    USER INPUT       |  FOOTER    |
     |      BLOCK   | MEMORY BLOCK        |     BLOCK  |
    *****************************************************/
    Allocation *ptrMemory = allocateMemory(size);
	Record *ptrRecord = createRecord(size,ptrMemory);
	Node *ptrNode = createNode(ptrRecord);
	addRecord(&allocatedPool,ptrNode);
	return ptrRecord->memoryAllocateAddr;
}





