#ifndef Node_H
#define Node_H

#include "MemoryRecord.h"

typedef struct Node Node;
struct Node {
 Record *data;
 Node *left;
 Node *right;
 char color; // 'b' or 'r'(black or red)
};

Node *createNode(Record *record);

#endif // Node_H
