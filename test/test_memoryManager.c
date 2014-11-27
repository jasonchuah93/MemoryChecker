#include "unity.h"
#include "Node.h"
#include "MemoryRecord.h"
#include "mock_redBlackTree.h"
#include "memoryManager.h"

void setUp(void){}

void tearDown(void){}

#define createRecord(memory,size) _createRecord(memory,size,__LINE__,__FILE__)

void test_memoryManagerAddRecord_should_add_all_the_input_parameter_from_create_record(void){
    char *memory = "5A5A5A";
    Record *record;
    Record *recordCompare;
    record = createRecord(memory,100);
    
    //Do no understand the recordCompare...what should I compare to 
   //genericAddRedBlackTree_Expect(record,&recordCompare);
    //memoryManagerAddRecord(record);
}