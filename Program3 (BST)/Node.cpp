#include "Node.h"

Node::Node(string data) {
    this->data = data;
    count = 1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}
Node& Node::operator=(const Node& data){
    if(this != &data){
        this->data = data.data;
        this->count = data.count;
    }
    
    return *this;
}