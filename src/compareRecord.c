#include <stdio.h>
#include "compareRecord.h"

/***********************************************************************************************************
* Compare the memoryAddr in descriptor locate in redBlackTree(RBT) with the incoming memoryAddr
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
int findAndRemoveRecordCompare(Node **recordFromRedBlackTree,char *targetMemoryAddr){
	char *recordAddr = ((Record*)((Node*)*recordFromRedBlackTree)->data)->memoryAllocateAddr;
    if(recordAddr > targetMemoryAddr){
       return 1;
    }else if(recordAddr < targetMemoryAddr){
       return -1;
    }else if(recordAddr == targetMemoryAddr){
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
int addRecordCompare(Node **recordFromRedBlackTree,Node *compareRecord){
	char *recordAddr = memoryAddr(*recordFromRedBlackTree);
    char *compareAddr = memoryAddr(compareRecord);
    
	if(recordAddr > compareAddr)
        return 1;
    else if(recordAddr < compareAddr){
		return -1;
	}
    else if(recordAddr == compareAddr)
		return 0;
    
}
