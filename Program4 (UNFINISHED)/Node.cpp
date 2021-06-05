#include "Node.h"

Node::Node(const string &text, int frequency)
 : token(text), freq(1) {}

void Node::addFreq(int s) {
	++freq;
}

const string & Node::getToken() {
    return token;
}
