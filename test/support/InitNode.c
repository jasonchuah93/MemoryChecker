#include <stdio.h>
#include "Node.h"
#include "InitNode.h"

void setNode(Node *target, Node *left, Node *right, char color){
	target->left = left;
	target->right = right;
	target->color = color;
}

void resetNode(Node *target, int data){
	target->left = NULL;
	target->right = NULL;
	target->color = 'b';
	target->data = data;
}

void genericResetNode(Node *target, void *data){
	target->left = NULL;
	target->right = NULL;
	target->color = 'b';
	target->memoryData = data;
}
