#include <iostream>
#include "IntList.h"
using namespace std;

IntList::IntList() {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->prev = nullptr;
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    dummyTail->next = nullptr;
}

IntList::~IntList() {
    while (dummyHead->next != dummyTail) {
        pop_front();
    }
    delete dummyHead;
    delete dummyTail;
}

void IntList::push_front(int value) {
    IntNode *newNode = new IntNode(value);
    IntNode *temp = dummyHead->next;
    newNode->prev = dummyHead;
    dummyHead->next = newNode;
    newNode->next = temp;
    temp->prev = newNode;
}

void IntList::pop_front() {
    if (dummyHead->next == dummyTail) {
        return;
    }
    else {
        IntNode* deletedNode = dummyHead->next;
        IntNode* nextNode = deletedNode->next;
        dummyHead->next = nextNode;
        nextNode->prev = dummyHead;
        delete deletedNode;
    }
}

void IntList::push_back(int value) {
    IntNode* temp = dummyTail->prev;
    IntNode* newNode = new IntNode(value);
    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = dummyTail;
    dummyTail->prev = newNode;
}

void IntList::pop_back() {
    if (dummyHead->next == dummyTail) {
        return;
    }
    else {
        IntNode* deletedNode = dummyTail->prev;
        IntNode* prevNode = deletedNode->prev;
        prevNode->next = dummyTail;
        dummyTail->prev = prevNode;
        delete deletedNode;
    }
}

bool IntList::empty() const {
    if (dummyHead->next == dummyTail && dummyTail->prev == dummyHead) {
        return true;
    }
    else {
        return false;
    }
}

void IntList::printReverse() const {
	if (dummyHead->next != dummyTail) {
		IntNode* curr = dummyTail->prev;
		while (curr != dummyHead) {
			if (curr == dummyHead->next) {
				cout << curr->data;
			}
			else {
				cout << curr->data << " ";
			}
			curr = curr->prev;
		}
	}
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    if (!rhs.empty()) {
        IntNode* curr = rhs.dummyHead->next;
        while (curr->next != rhs.dummyTail) {
            out << curr->data << " ";
            curr = curr->next;
        }
        out << curr->data;
    }
    return out;
}
