#include <iostream>
#include "Node.h"

Node::Node(string userData) {
    data = userData;
    count = 0;
    height = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}