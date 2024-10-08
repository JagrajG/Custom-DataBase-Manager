#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    deleteList();
}

void LinkedList::addItem(Item* newItem) {
    Node* newNode = new Node(newItem);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::displayItems() const {
    Node* temp = head;
    while (temp != nullptr) {
        temp->item->displayItemInfo();
        temp = temp->next;
    }
}

void LinkedList::deleteList() {
    Node* temp = head;
    while (temp != nullptr) {
        head = head->next;
        delete temp->item;
        delete temp;
        temp = head;
    }
    head = nullptr;
}

Node* LinkedList::getHead() const {
    return head;
}
