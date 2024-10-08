#ifndef NODE_H
#define NODE_H

#include "Item.h"

class Node {
public:
    Item* item;
    Node* next;

    // Constructor declaration
    Node(Item* item);
};

#endif // NODE_H
