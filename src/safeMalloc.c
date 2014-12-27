#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "memoryAllocator.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

void *headerBlock;
void *footerBlock;

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
    Record *allocateRecord;
    Node *allocateNode;
    if(size == 0){
        return NULL;
    }else if(size > BUFFER_SIZE){
        printf("Out of Buffer Size at line %d from file %s\n",lineNumber,fileName);
        Throw(ERR_EXCEED_BUFFER_SIZE);
    }
	//Allocate a memory Block which consist of 3 segments
    /****************************************************
     |  HEADER      |    USER INPUT       |  FOOTER    |
     |      BLOCK   | MEMORY BLOCK        |     BLOCK  |
    *****************************************************/
    void *memoryBlock = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	headerBlock = memoryBlock;
    strcpy(headerBlock,"5A5A5A5A5A5A5A");
    void *userBlock = memoryBlock+HEADER_SIZE;
    footerBlock = memoryBlock+HEADER_SIZE+size;
    strcpy(footerBlock,"5A5A5A5A5A5A5A");
    allocateRecord = createRecord(userBlock,size);
    allocateNode = createNode(allocateRecord);
    addRecord(&allocatePool,allocateNode);
	
    return userBlock;
}

void safeFree(void *memoryToFree){
    
   
}

/*********************************************************************
* This function will destroy the allocated pool so prevent memory leak
*
*	Destroy: allocatedPool
*	
**********************************************************************/

void resetAllocatedPool(){
    //Record *newRecord = malloc(sizeof(Record));
    //Node *newNode = malloc(sizeof(Node));
    allocatePool = NULL;
}

void _checkMemoryContent(void *record,int lineNumber, char *fileName){
   if(headerBlock != "5A5A5A5A5A5A5A"){
        printf("User memory write into header Block at line %d from file %s\n",lineNumber-2,fileName);
        Throw(ERR_MEMORY_WRONG);
   }
   if(footerBlock != "5A5A5A5A5A5A5A"){
        printf("User memory write into header Block at line %d from file %s\n",lineNumber-2,fileName);
   }
}
