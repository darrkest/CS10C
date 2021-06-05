#ifndef NODE_H 
#define NODE_H 

#include <iostream> 
#include <string> 

using namespace std;
class Node {
    public:
        friend class AVLTree;
    private:
      string data; 
      int count;
      int height;
      Node *left;
      Node *right; 
      Node *parent;
      Node(string userData);
};

#endif