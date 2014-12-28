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
char *userBlock;

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
    memoryPool = malloc(HEADER_SIZE+size+FOOTER_SIZE);
	headerBlock = memoryPool;
    strcpy(headerBlock,"5A5A5A5A5A5A5A");
    userBlock = memoryPool+HEADER_SIZE;
    footerBlock = memoryPool+HEADER_SIZE+size;
    strcpy(footerBlock,"5A5A5A5A5A5A5A");
    Record *tempRecord = createRecord(userBlock,size);
    Node *recordNode = createNode(tempRecord);
    addRecord(&allocatePool,recordNode);
	return userBlock;
}

void safeFree(void *memoryToFree){
    if(memoryToFree == NULL){
        Throw(ERR_FREE_NULL_PTR);
    }   
    Record *freeNode = (Record*)findRecord(&allocatePool,memoryToFree);
    //addRecord(&freePool,freeNode);
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
    freePool = NULL;
}

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

void _checkFooterMemoryContent(void *record,int lineNumber, char *fileName){
    
    char *tempRecord;
    strcpy(tempRecord,"5A5A5A5A5A5A5A");
    int comp;
    comp = strcmp(record,tempRecord);
    if(comp>0){    
        printf("user write exceed header block at line %d from file %s \n",lineNumber-2,fileName);
        Throw(ERR_CORRUPTED_FOOTER_MEMORY);
    }
    
}

void saveSummary(){
    free(memoryPool);
    freeNode(freePool);
    freePool=NULL;
    freeNode(allocatePool);
    allocatePool=NULL;
}

void freeNode(Node *root){
    if(root == NULL){
        return;
    }
    if(root->left!=NULL){
        freeNode(root->left);
        root->left=NULL;
        if(root->right!=NULL){
            freeNode(root->right);
            root->right=NULL;
        }
    }else if(root->right!=NULL){
        freeNode(root->right);
        root->right=NULL;
        if(root->left!=NULL){
            freeNode(root->left);
            root->left=NULL;
        }
    }else{
        free(root->data);
        free(root);
    }    
}