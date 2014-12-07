#ifndef NodePtr_H
#define NodePtr_H

typedef struct NodePtr NodePtr;

struct NodePtr {
 NodePtr *left;
 NodePtr *right;
 char color; // 'b' or 'r'(black or red)
 void *address;
};

#endif // Node_H
