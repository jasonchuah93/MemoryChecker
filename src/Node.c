#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "MemoryRecord.h"

#define createNode(record) _createNode(record)

/**
    This function will create node which contain a record as the input parameter.
    Return information in node when the function end.
	Input  : Record
    Output : node
**/

Node *_createNode(Record *record){
    Node *node  = malloc(sizeof(Node));
    node->data  = record;
    node->left  = NULL;
    node->right = NULL;
    node->color ='b';
    
    return node;
}
