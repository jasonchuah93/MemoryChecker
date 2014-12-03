#include "unity.h"
#include "Node.h"
#include "MemoryRecord.h"
#include "Rotation.h"
#include "mock_redBlackTree.h"
#include "memoryManager.h"
#include "ErrorCode.h"
#include "CException.h"


void setUp(void){}

void tearDown(void){}

#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

void test_memoryManagerAddRecord_should_add_data_into_red_black_tree(void){
	char *memory = "5A5A5A";
	Record *record = createRecord(memory , 100);
	
    
	
}

