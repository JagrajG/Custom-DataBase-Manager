#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();
    
    // Public methods
    void addItem(Item* newItem);
    void displayItems() const;
    void deleteList();

    // Getter for head (to allow controlled access to private head)
    Node* getHead() const;
};

#endif // LINKEDLIST_H
