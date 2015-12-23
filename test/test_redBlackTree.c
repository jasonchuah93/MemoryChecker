#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include "MemoryBlocks.h"
#include "mock_MallocWrapper.h"
#include "Node.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "compareRecord.h"
#include "redBlackTree.h"
#include "RestructureNode.h"
#include "CustomAssertions.h"

void setUp(void){}
void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*   root              root
*	 |    add n100     |
*	 v    --------->   v
*	NULL              n100
**/
void test_addRecord_should_add_record_into_empty_root(void){
	MemoryBlock1 ptrBlock1 = {.header[49] = "##########" , .memory[99] = "abcdef", .footer[49] = "##########"};
	Allocation block1 = {.memoryAllocateAddr = (char*)sizeof(ptrBlock1.memory)};
    Record *ptrRecord1 = createRecord(100,&block1);
    Node *r100 = createNode(ptrRecord1);
	
	Node *root = NULL;
	addRecord(&root,r100);
	
	TEST_ASSERT_EQUAL_PTR(root,r100);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',r100);
}

/*****************************************

	2 NODE tests

*******************************************/
/**
*    root              root
*     |     add n100    |
*     v     -------->   v
*    n200              n200	    
*    / \               / \
*   -   -           n100  -   
**/
void test_addRecord_should_add_new_record_into_non_empty_root(void){
    Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Node n200 = {.data=&r200 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n200);
    addRecord(&root,&n100);
    
    TEST_ASSERT_EQUAL_PTR(root,&n200);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
    TEST_ASSERT_EQUAL_NODE(&n100,NULL,'b',root);
}

/**
*       root                root
*         |     add n500      |
*         v    --------->     v
*        n200               n200       
*        /  \               /   \
*      -     -             -   n500
**/

void test_addRecord_add_n500_into_n200_root(void){
    Record r200 = {.memoryAllocateAddr =(void*)200};  
    Record r500 = {.memoryAllocateAddr =(void*)500};
    Node n200 = {.data=&r200 ,.color='r'};
    Node n500 = {.data=&r500 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n200);
    addRecord(&root,&n500);
    
    TEST_ASSERT_EQUAL_PTR(root,&n200);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n500);
    TEST_ASSERT_EQUAL_NODE(NULL,&n500,'b',root);
}

/*****************************************

	3 NODE tests

*******************************************/
/**
*     root             root
*     |    add n300     |
*     v    -------->    v
*   n200              n200        
*   /  \              /   \      
*  n100 -          n100  n300
**/
void test_addRecord_add_n300_into_n100_n200_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100 };  
    Record r200 = {.memoryAllocateAddr =(void*)200 };
    Record r300 = {.memoryAllocateAddr =(void*)300 };  
    
	Node n100 = {.data=&r100 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n200);
    addRecord(&root,&n100);
    addRecord(&root,&n300);
    
    TEST_ASSERT_EQUAL_PTR(&n200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n300);
    TEST_ASSERT_EQUAL_NODE(&n100,&n300,'b',root);
}

/**
*     root             root
*     |    add n300     |
*     v    -------->    v
*   n100              n200        
*   /  \              /   \      
*  -   n200       n100  n300
**/
void test_addRecord_add_n200_and_n300_into_n100_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100 };  
    Record r200 = {.memoryAllocateAddr =(void*)200 };
    Record r300 = {.memoryAllocateAddr =(void*)300 };  
    
	Node n100 = {.data=&r100 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	
    Node *root = NULL;
    addRecord(&root,&n100);
    addRecord(&root,&n200);
    addRecord(&root,&n300);
    
    TEST_ASSERT_EQUAL_PTR(&n200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n300);
    TEST_ASSERT_EQUAL_NODE(&n100,&n300,'b',root);
}

/**
*        root                root
*          |       add n100   |
*          v      --------->  v
*        n200               n200    
*       /    \              /  \
*      -    n300         n100  n300  
**/
void test_addRecord_add_n100_into_n300_n200_root(void){
    Record r100 = {.memoryAllocateAddr =(void*)100 };  
    Record r200 = {.memoryAllocateAddr =(void*)200 };
    Record r300 = {.memoryAllocateAddr =(void*)300 };  
    
	Node n100 = {.data=&r100 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n200 = {.data=&r200 , .right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n100);
    
    TEST_ASSERT_EQUAL_PTR(&n200,root);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
    TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n300);
    TEST_ASSERT_EQUAL_NODE(&n100,&n300,'b',root);
}

/**
*        root              root                        root
*         |    add n400      |                          |
*         v    -------->     v      leftRotate          v  
*       n200               n200                        n300
*       /  \              /   \    ------------->     /   \
*     -   n300           -    n300                  n200  n400 
*                               \                     
*                              n400                
*
**/
void test_addRecord_add_r400_into_r200_r300_redBlackTree_and_leftRotate(void){
	Record r300 = {.memoryAllocateAddr =(void*)300 };  
    Record r400 = {.memoryAllocateAddr =(void*)400 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	
	Node n300 = {.data=&r300 ,.color='r'};
	Node n400 = {.data=&r400 ,.color='r'};
	Node n200 = {.data=&r200 , .left = NULL, .right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n400);
    
	TEST_ASSERT_EQUAL_PTR(&n300,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n400);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n200);
	TEST_ASSERT_EQUAL_NODE(&n200,&n400,'b',root);
}

/**
*        root               root                      root        
*         |     add n50	     |                         |     
*         v    -------->     v     rightRotate         v  
*       n200                n200   at n100            n100
*       /   \              /    \  ------------->     /  \
*     n100   -           n100    -                  n50  n200 
*                        /
*                      n50
*
**/
void test_addRecord_add_n50_into_n100_n200_root_and_rightRotate(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 };  
    Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	
	Node n50 = {.data=&r50 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	Node n200 = {.data=&r200 ,.left = &n100, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n50);
	
	TEST_ASSERT_EQUAL_PTR(&n100,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n200);
	TEST_ASSERT_EQUAL_NODE(&n50,&n200,'b',root);
}

/**
*     root                root                         root
*       |    add n200       |                            |
*       v    --------->     v       leftRightRotate      v  
*     n300                 n300     at n100             n200
*     /  \                 /  \   --------------->      /  \
*   n100  -             n100   -                     n100  n300
*                           \
*                          n200
*
**/
void test_addRecord_add_n200_into_n100_n300_root_and_do_leftRightRotate(void){
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };  
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n200 = {.data=&r200 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	Node n300 = {.data=&r300 ,.left = &n100, .color='b'};
	
	Node *root = &n300;
    addRecord(&root,&n200);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n300);
	TEST_ASSERT_EQUAL_NODE(&n100,&n300,'b',root);
}

/**
*       root            root                            root
*        |    add n250	  |                               |
*        v   --------->   v      rightLeftRotate          v  
*       n200             n200                            n250
*     /    \            /  \    ------------->          /   \
*   -     n300         -   n300                       n200  n300
*                           /
*                          n250             
*
**/
void test_addRecord_add_n250_into_n300_n200_root_and_do_rightLeftRotate(void){
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r250 = {.memoryAllocateAddr =(void*)250 };  
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n250 = {.data=&r250 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n200 = {.data=&r200 ,.right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n250);
	
	TEST_ASSERT_EQUAL_PTR(&n250,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n200);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n300);
	TEST_ASSERT_EQUAL_NODE(&n200,&n300,'b',root);
}

/*****************************************

	4 NODE tests

*******************************************/
/**
*     root                root                         
*       |    leftRight      |                           
*       v    add n50        v       
*     n300   --------->    n200     
*     /  \                 /  \        
*   n100  -             n100   n300                  
*     \                  /                           
*     n200              n50                        
*
**/
void test_addRecord_add_n50_into_n200_n100_n300_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 };  
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };  
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n50 = {.data=&r50 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	
	Node *root = NULL;
    addRecord(&root,&n300);
	addRecord(&root,&n100);
	addRecord(&root,&n200);
	addRecord(&root,&n50);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n50);
	TEST_ASSERT_EQUAL_NODE(&n50,NULL,'b',&n100);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n100,&n300,'r',root);
}

/**
*       root            root                      
*        |    add n25	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                     /   
*                   n25 
*
**/
void test_addRecord_add_n25_into_n50_n300_n200_root(void){
	Record r25 = {.memoryAllocateAddr =(void*)25 };  
	Record r50 = {.memoryAllocateAddr =(void*)50 };
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n25 = {.data=&r25 ,.color='r'};
	Node n50 = {.data=&r50 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n200 = {.data=&r200 ,.left = &n50 ,.right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n25);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n25);
	TEST_ASSERT_EQUAL_NODE(&n25,NULL,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n50,&n300,'r',root);
}

/**
*       root            root                      
*        |    add n100	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                       \   
*                      n100 
*
**/
void test_addRecord_add_n100_into_n50_n300_n200_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 };
	Record r100 = {.memoryAllocateAddr =(void*)100 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n100 = {.data=&r100 ,.color='r'};
	Node n50 = {.data=&r50 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n200 = {.data=&r200 ,.left = &n50 ,.right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n100);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n100);
	TEST_ASSERT_EQUAL_NODE(NULL,&n100,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n50,&n300,'r',root);
}

/**
*       root            root                      
*        |    add n250	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                           /   
*                          n250 
*
**/
void test_addRecord_add_n250_into_n50_n300_n200_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 };
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r250 = {.memoryAllocateAddr =(void*)250 };  
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n250 = {.data=&r250 ,.color='r'};
	Node n50 = {.data=&r50 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n200 = {.data=&r200 ,.left = &n50 ,.right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n250);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n250);
	TEST_ASSERT_EQUAL_NODE(&n250,NULL,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n50,&n300,'r',root);
}

/**
*       root            root                      
*        |    add n500	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*                            \   
*                            n500 
*
**/
void test_addRecord_add_n500_into_n50_n300_n200_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	Record r500 = {.memoryAllocateAddr =(void*)500 };
	
	Node n500 = {.data=&r500 ,.color='r'};
	Node n50 = {.data=&r50 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n200 = {.data=&r200 ,.left = &n50 ,.right = &n300, .color='b'};
	
	Node *root = &n200;
    addRecord(&root,&n500);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n500);
	TEST_ASSERT_EQUAL_NODE(NULL,&n500,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n50,&n300,'r',root);
}

/*****************************************

	More NODE tests

*******************************************/

/**
*       root            root                      
*        |    add n250	  |                        
*        v   --------->   v      
*       n200             n200   
*     /    \            /  \    
*   n50     n300      n50   n300
*            \              /  \   
*            n500        n250   n500 
*
**/
void test_addRecord_add_n250_into_n500_n50_n300_n200_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 };  
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r250 = {.memoryAllocateAddr =(void*)250 };
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	Record r500 = {.memoryAllocateAddr =(void*)500 };
	
	Node n50 = {.data=&r50 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n250 = {.data=&r250 ,.color='r'};
	Node n500 = {.data=&r500 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	
	Node *root = NULL;
	addRecord(&root,&n200);
    addRecord(&root,&n50);
	addRecord(&root,&n300);
	addRecord(&root,&n500);
	addRecord(&root,&n250);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n250);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n500);
	TEST_ASSERT_EQUAL_NODE(&n250,&n500,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n50,&n300,'r',root);
}

/**
*       root             root                 
*        |    add n70	  |                      
*        v   --------->   v         
*       n200             n200                  
*     /    \            /   \                 
*   n100   n300       n100  n300            
*   /  \             /  \   
*  n50 n150         n50 n150           
*                    \
*                    n70
**/
void test_addRecord_add_n70_into_n150_n50_n300_n100_n200_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 }; 
	Record r70 = {.memoryAllocateAddr =(void*)70 }; 
	Record r100 = {.memoryAllocateAddr =(void*)100 };
	Record r150 = {.memoryAllocateAddr =(void*)150 };
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	
	Node n50 = {.data=&r50 ,.color='r'};
	Node n70 = {.data=&r70 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	Node n150 = {.data=&r150 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	
	Node *root = NULL;
	addRecord(&root,&n200);
    addRecord(&root,&n100);
	addRecord(&root,&n300);
	addRecord(&root,&n50);
	addRecord(&root,&n150);
	addRecord(&root,&n70);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n70);
	TEST_ASSERT_EQUAL_NODE(NULL,&n70,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n150);
	TEST_ASSERT_EQUAL_NODE(&n50,&n150,'r',&n100);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(&n100,&n300,'b',root);
}

/**
*       root             root                             root
*        |    add n400	  |                                |
*        v   --------->   v                                v
*       n200             n200       rightLeftRotate       n200          
*     /    \            /   \       at n500              /    \
*   n100   n300       n100  n300    ---------------->  n100   n400     
*   /  \     \        /  \    \                        /  \   /   \
*  n50 n150  n500   n50 n150  n500                   n50 n150 n300 n500
*        \                    /                             \
*        n180                n400                          n180
**/
void test_addRecord_add_n400_into_n180_n150_n50_n300_n500_n100_n200_root(void){
	Record r50 = {.memoryAllocateAddr =(void*)50 }; 
	Record r180 = {.memoryAllocateAddr =(void*)180 }; 
	Record r100 = {.memoryAllocateAddr =(void*)100 };
	Record r150 = {.memoryAllocateAddr =(void*)150 };
	Record r200 = {.memoryAllocateAddr =(void*)200 };
	Record r300 = {.memoryAllocateAddr =(void*)300 };
	Record r400 = {.memoryAllocateAddr =(void*)400 };
	Record r500 = {.memoryAllocateAddr =(void*)500 };
	
	Node n50 = {.data=&r50 ,.color='r'};
	Node n180 = {.data=&r180 ,.color='r'};
	Node n100 = {.data=&r100 ,.color='r'};
	Node n150 = {.data=&r150 ,.color='r'};
	Node n200 = {.data=&r200 ,.color='r'};
	Node n300 = {.data=&r300 ,.color='r'};
	Node n400 = {.data=&r400 ,.color='r'};
	Node n500 = {.data=&r500 ,.color='r'};
	
	Node *root = NULL;
	addRecord(&root,&n200);
    addRecord(&root,&n100);
	addRecord(&root,&n300);
	addRecord(&root,&n50);
	addRecord(&root,&n150);
	addRecord(&root,&n500);
	addRecord(&root,&n180);
	addRecord(&root,&n400);
	
	TEST_ASSERT_EQUAL_PTR(&n200,root);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'r',&n180);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n50);
	TEST_ASSERT_EQUAL_NODE(NULL,&n180,'b',&n150);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n300);
	TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',&n500);
	TEST_ASSERT_EQUAL_NODE(&n50,&n150,'r',&n100);
	TEST_ASSERT_EQUAL_NODE(&n300,&n500,'r',&n400);
	TEST_ASSERT_EQUAL_NODE(&n100,&n400,'b',root);
}

