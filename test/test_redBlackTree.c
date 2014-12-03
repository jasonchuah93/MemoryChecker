#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "InitNode.h"
#include "Rotation.h"
#include "MemoryRecord.h"
#include "redBlackTree.h"
#include "CustomAssertions.h"
#include "ErrorCode.h"
#include "CException.h"

Node node5,node7,node10;

void setUp(void){
	resetNode(&node5,5);
	resetNode(&node7,7);
	resetNode(&node10,10);
}

void tearDown(void){}

/*****************************************

	1 NODE tests

*******************************************/
/**
*	root		root
*	 |    add 10	|
*	 v    ------>   v
*	NULL          10(b)
**/

void test_genericAddRedBlackTree_add_10(void){
  setNode(&node10,NULL,NULL,'r');
  Node *root = NULL;

  addRedBlackTree(&root,&node10);
  TEST_ASSERT_EQUAL_NODE(NULL,NULL,'b',root);
}


/**
*		root			      		 root
*		 |   add 7 to left node		   |
*		 v    ----------------->  	   v
*		10(b)                	      7(b)
*		 /			      			  /	\
*		5(r)			  		   5(r)  10(r)
**/

void test_genericAddRedBlackTree_add_node7_to_tree_with_root_10(void){
	setNode(&node10,&node5,NULL,'b');
	setNode(&node5,NULL,NULL,'r');
	setNode(&node7,NULL,NULL,'r');
	//Node *root = &node10;
	
	
}


