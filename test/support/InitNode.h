#ifndef __InitNode_H__
#define __InitNode_H__

#include "Node.h"
#include "NodePtr.h"

void setNode(Node *target, Node *left, Node *right, char color);

void resetNode(Node *target, int data);

void setGenericNode(Node *target, void *data);

#endif // __InitNode_H__