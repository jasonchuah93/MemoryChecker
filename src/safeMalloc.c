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

char *headerBlock;
char *footerBlock;
char *userBlock ;

void *_safeMalloc(int size,int lineNumber, char *fileName){
    allocatePool=NULL;
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
    memoryPool = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	headerBlock = memoryPool;
    strcpy(headerBlock,"5A5A5A5A5A5A5A");
    userBlock = memoryPool+HEADER_SIZE;
    footerBlock = memoryPool+HEADER_SIZE+size;
    strcpy(footerBlock,"7A7A7A7A7A7A7A");
    Node *recordNode = createNode(userBlock,size);
    addRecord(&allocatePool,recordNode);
	return userBlock;
}

void safeFree(void *memoryToFree){
    Node *freeNode = NULL;
    if(memoryToFree == NULL){
        Throw(ERR_FREE_NULL_PTR);
    }   
    Record tempRecord={.memory = memoryToFree};
    Node tempNode = {.data = &tempRecord};
    freeNode = findRecord(&allocatePool,memoryToFree);
    if(freeNode == NULL){
        return ;
    }
    freeNode = removeNode(&allocatePool,freeNode);
    freeNode->left=NULL;
    freeNode->right=NULL;
    
    addRecord(&freePool,freeNode);
}

void safeSummary(){
    if(allocatePool!=NULL){
        
    }
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
   if(strcpy(headerBlock,"5A5A5A5A5A5A5A")!="5A5A5A5A5A5A5A"){
        printf("User memory write into header Block at line %d from file %s\n",lineNumber-2,fileName);
        Throw(ERR_CORRUPTED_MEMORY);
   }else if(strcpy(footerBlock,"7A7A7A7A7A7A7A")!= "7A7A7A7A7A7A7A"){
        printf("User memory write into footer Block at line %d from file %s\n",lineNumber-2,fileName);
        Throw(ERR_CORRUPTED_MEMORY);
   }
   
   
}
