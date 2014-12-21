#include <stdio.h>
#include <stdlib.h>
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

Record *allocateRecord;

void memoryInitialization(){
   memoryPool = malloc(sizeof(void)*BUFFER_SIZE);
}

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
    
    void *pointerToUserBlock = NULL;
    ErrorCode e;
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
    //Allocate memory 
    void *memoryBlock = NULL;
    memoryBlock = malloc(HEADER_SIZE+size+FOOTER_SIZE);
    //Header block is the pointer that point to HEADER BLOCK 
    //in the memory block
    headerBlock = memoryBlock;
    //Content of the memory is write into the headerBlock
    headerBlock =(void*)"5A5A5A5A5A5A5A";
    //pointerToUserBlock is the pointer that point to the segment
    //of the user requested memory block
    pointerToUserBlock = memoryBlock+HEADER_SIZE;
    //Content of the memory is write into the pointerToUserBlock
    pointerToUserBlock =(void*)size;
    //Footer block is the pointer that point at the FOOTER BLOCK 
    //in the memory block
    footerBlock = memoryBlock+HEADER_SIZE+size;
    //Content of the memory is write into the footer block
    footerBlock = headerBlock;
    //A record is create with the memory requested by user
    allocateRecord = createRecord(pointerToUserBlock,size);
    memoryManagerAddRecord(allocateRecord);
    
    return pointerToUserBlock;
    
}

void _safeFree(void *memoryToFree,int lineNumber, char *fileName){
    Node *freeRoot = NULL;
    Node *freeNode = NULL;
    
    if(memoryToFree == NULL){
        return ;
    }
    Record tempRecord={.memory = memoryToFree};
    Node tempNode = {.data = &tempRecord};
    freeRoot = (Node*)memoryManagerFindRecord(root,&tempRecord);
    if(freeRoot = NULL){
        return ; 
    }
    freeRoot = (Node*)memoryManagerDelRecord(&tempRecord);
    freeRoot->left = NULL;
    freeRoot->right = NULL;
    
    freeNode = (Node*)memoryManagerFindRecord(root
}

void testFree(void *memoryToFree,int lineNumber, char *fileName){
    if(headerBlock != (void*)"5A5A5A5A5A5A5A" || footerBlock != headerBlock){
        printf("Memory been modified at line %d from file %s\n",lineNumber,fileName);
        Throw(ERR_MEMORY_WRONG);
    }
    memoryManagerDelRecord(allocateRecord);
    memoryToFree = NULL;
    free(root);
}

