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

void memoryInitialization(){
    Node *newNode = malloc(sizeof(Node));
    Record *newRecord = malloc(sizeof(Record));
    memoryPool = malloc(sizeof(void)*BUFFER_SIZE);
    newRecord->memory = memoryPool;
    newRecord->size = BUFFER_SIZE;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 'b';
    newNode->data = newRecord;
    
    allocatePool = NULL;
}

void *_safeMalloc(unsigned int size,int lineNumber, char *fileName){
    Record *tempRecord;
    void *pointerToUserBlock;
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
    void *memoryBlock = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	//Header block is the pointer that point to HEADER BLOCK 
    //in the memory block
    //printf("size : %d \n",memoryBlock);
    headerBlock = memoryBlock;
    //Content of the memory is write into the headerBlock
    headerBlock = (void*)"5A5A5A5A5A5A5A";
    //pointerToUserBlock is the pointer that point to the segment
    //of the user requested memory block
    pointerToUserBlock = memoryBlock+HEADER_SIZE;
    //Footer block is the pointer that point at the FOOTER BLOCK 
    //in the memory block
    footerBlock = memoryBlock+HEADER_SIZE+size;
    //Content of the memory is write into the footer block
    footerBlock = headerBlock;
    //A record is create with the memory requested by user
    allocateRecord = createRecord(pointerToUserBlock,size);
    memoryManagerAddRecord(allocateRecord);
    
    return allocateRecord->memory;
}

void safeFree(void *memoryToFree){
   memoryManagerDelRecord(allocateRecord);
   allocateRecord = NULL;
}

void *testMalloc(int size){
    Record *recordTest;
    void *testPointer;
    testPointer=malloc(sizeof(void)*BUFFER_SIZE);
    recordTest = createRecord(testPointer,size);
    
    return recordTest->memory;
}
