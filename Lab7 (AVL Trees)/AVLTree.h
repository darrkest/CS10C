#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Node.h"
using namespace std;

class AVLTree {
    private:
        Node* root = nullptr;

    public:
        void insert(const string &);
        int balanceFactor(Node*);
        void printBalanceFactors();
        void visualizeTree(const string &);

    private:
        void rotate(Node*);
        void rotateLeft(Node*);
        void rotateRight(Node*);
        void printBalanceFactors(Node*);
        void visualizeTree(ofstream &, Node*);
        void updateHeight(Node*);
        bool setChild(Node*, string, Node*);
        bool replaceChild(Node*, Node*, Node*);
};

#endif