#include <stdio.h>
#include "safeMalloc.h"

/*********************************************************************
* This function will initialize allocated pool and 
  free pool to null
  Every test need to call this function to reset the allocatedPool 
  and freePool to null for next test
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
	Record *ptrRecord = createRecord(ptrMemory);
	Node *ptrNode = createNode(ptrRecord);
	addRecord(&allocatedPool,ptrNode);
	return ptrMemory->memoryAllocateAddr;
}

/*********************************************************************
* This function will use size to compare for adding into allocatedPool
**********************************************************************/
void *_safeMallocTest(int unsigned size,int lineNumber, char *fileName){
    //Allocate a memory Block which consist of 3 segments
    /****************************************************
     |  HEADER      |    USER INPUT       |  FOOTER    |
     |      BLOCK   | MEMORY BLOCK        |     BLOCK  |
    *****************************************************/
    Allocation *ptrMemory = allocateMemoryTest(size);
	Record *ptrRecord = createRecord(ptrMemory);
	Node *ptrNode = createNode(ptrRecord);
	addRecord(&allocatedPool,ptrNode);
	return ptrMemory->memoryAllocateAddr;
}



