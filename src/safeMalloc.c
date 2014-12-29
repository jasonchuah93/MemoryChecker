#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "Rotation.h"
#include "memoryManager.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "safeMalloc.h"
#include "ErrorCode.h"
#include "CException.h"

/*********************************************************************
* This function will allocate memory and create record
* to add inside the allocated pool
*
*	Destroy: none
*	
**********************************************************************/

void *_safeMalloc(int size,int lineNumber, char *fileName){
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
    void *memoryPool = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	void *headerBlock = memoryPool;
    strcpy(headerBlock,"5A5A5A5A5A5A5A");
    void *userBlock = memoryPool+HEADER_SIZE;
    void *footerBlock = userBlock+size;
    strcpy(footerBlock,"5A5A5A5A5A5A5A");
    Record *tempRecord = createRecord(userBlock,size);
    memoryManagerAllocateRecord(tempRecord);
	return userBlock;
}

/*********************************************************************
* This function will deallocate memory from allocate pool and place
* to free pool
*
*	Destroy: none
*	
**********************************************************************/

void safeFree(void *memoryToFree){
   
}

/*********************************************************************
* This function will destroy the allocated pool so prevent memory leak
*
*	Destroy: allocatedPool
*	
**********************************************************************/

void resetAllocatedPool(){
    allocatedPool = NULL;
    
}

/*********************************************************************
* This function will check the content of the header block 
*
*	Destroy: nonde
*	Throw error if the memory being overwritten
**********************************************************************/

void _checkHeaderMemoryContent(void *record,int lineNumber, char *fileName){
    
    char *tempRecord;
    strcpy(tempRecord,"5A5A5A5A5A5A5A");
    int comp;
    comp = strncmp(record,tempRecord,15);
    if(comp>0){    
        printf("user write exceed header block at line %d from file %s \n",lineNumber-2,fileName);
        Throw(ERR_CORRUPTED_HEADER_MEMORY);
    }
    
}

/*********************************************************************
* This function will check the content of the footer block
*
*	Destroy: nonde
*	Throw error if the memory being overwritten
**********************************************************************/

void _checkFooterMemoryContent(void *record,int lineNumber, char *fileName){
    
    char *tempRecord;
    strcpy(tempRecord,"5A5A5A5A5A5A5A");
    int comp;
    comp = strcmp(record,tempRecord);
    if(comp<0){    
        printf("user write exceed header block at line %d from file %s \n",lineNumber-2,fileName);
        Throw(ERR_CORRUPTED_FOOTER_MEMORY);
    }
}

/*********************************************************************
* This function will free all the record in allocate pool 
*
*	Destroy: allocatedPool
*	
**********************************************************************/

void saveSummary(){
   
    
}

