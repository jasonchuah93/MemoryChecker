#include <stdio.h>
#include "Node.h"
#include "MemoryRecord.h"

/***********************************************************************************************************
* Compare the record inside the redBlackTree(RBT) with the incoming record
*
*	Input: 	recordFromRedBlackTree	the record inside the node of RBT 
*			targetMemory			the target that going to find in the RBT	
*	Output: 1			indicated address contain in the record from RBT is larger than the target memory
*			-1			indicated address contain in the record from RBT is smaller than the target memory
*			0			address in both record are the same
*	
*	Destroy: none
*
************************************************************************************************************/

int findRecordCompare(Node **recordFromRedBlackTree,void *targetMemory){
	Record *_recordFromRedBlackTree=(Record*)*recordFromRedBlackTree;
    char *_targetMemory=(char*)targetMemory;
  
    if((char*)_recordFromRedBlackTree->memoryAddr > _targetMemory){
       return 1;
    }else if((char*)_recordFromRedBlackTree->memoryAddr < _targetMemory){
       return -1;
    }else if((char*)_recordFromRedBlackTree->memoryAddr == _targetMemory){
       return 0;
    }
}

/***********************************************************************************************************
* Compare the record inside the redBlackTree(RBT) with the incoming record
*
*	Input: 	recordFromRedBlackTree	the record inside the node of RBT 
*			targetRecord			the target that going to add or delete in the RBT	
*	Output: 1			indicated address contain in the record from RBT is larger than the target record
*			-1			indicated address contain in the record from RBT is smaller than the target record
*			0			address in both record are the same
*	
*	Destroy: none
*
************************************************************************************************************/

int addAndDelRecordCompare(Node **recordFromRedBlackTree,Record *targetRecord){
	Record *_recordFromRedBlackTree=(Record*)*recordFromRedBlackTree;
    if(_recordFromRedBlackTree->memoryAddr > targetRecord->memoryAddr)
        return 1;
    else if(_recordFromRedBlackTree->memoryAddr < targetRecord->memoryAddr)
        return -1;
    else
        return 0;
}



