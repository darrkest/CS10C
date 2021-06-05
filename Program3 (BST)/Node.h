#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>
using namespace std;

struct Node {
    string data;
    int count;
    Node* left;
    Node* right;
    Node* parent;
    Node(string data);
    Node& operator=(const Node&data);
};

#endif