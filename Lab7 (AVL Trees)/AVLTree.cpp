#include <iostream>
#include <fstream>
#include "AVLTree.h"

void AVLTree::insert(const string &newString) {
    Node* newNode = new Node(newString);
    if (root == nullptr) {
        root = newNode;
        newNode->parent = nullptr;
        return;
    }
    Node* curr = root;
    while (curr != nullptr) {
        if (newNode->data == curr->data) {
            curr->count++;
            curr = nullptr;
        }
        else if (newNode->data < curr->data) {
            if (curr->left == nullptr) {
                curr->left = newNode;
                newNode->parent = curr;
                curr = nullptr;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            if (curr->right == nullptr) {
                curr->right = newNode;
                newNode->parent = curr;
                curr = nullptr;
            }
            else {
                curr = curr->right;
            }
        }
    }
    newNode = newNode->parent;
    while (newNode != nullptr) {
        rotate(newNode);
        newNode = newNode->parent;
    }
}

void AVLTree::rotate(Node* node) {
    updateHeight(node);
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) == 1) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
    else if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) == -1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
}

int AVLTree::balanceFactor(Node* curr) {
    int leftHeight = -1;
    int rightHeight = -1;

    if (curr->left != nullptr) {
        leftHeight = curr->left->height;
    }
    if (curr->right != nullptr) {
        rightHeight = curr->right->height;
    }
    return (leftHeight - rightHeight);
}

void AVLTree::updateHeight(Node* node) {
    int leftHeight = -1;
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }
    int rightHeight = -1;
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }
    node->height = max(leftHeight, rightHeight) +1;
}

bool AVLTree::setChild(Node* parent, string whichChild, Node* child) {
    if (whichChild != "left" && whichChild != "right") {
        return false;
    }
    if (whichChild == "left") {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    if (child != nullptr) {
        child->parent = parent;
    }
    updateHeight(parent);
    return true;
}

bool AVLTree::replaceChild(Node* parent, Node* currChild, Node* newChild) {
    if (parent->left == currChild) {
        return setChild(parent, "left", newChild);
    }
    else if (parent->right == currChild) {
        return setChild(parent, "right", newChild);
    }
    return false;
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* curr)   {
    if (curr == nullptr) {
        return;
    }
    else {
        printBalanceFactors(curr->left);
        cout << curr->data << "(" << balanceFactor(curr) << "), ";
        printBalanceFactors(curr->right);
    }
}

void AVLTree::rotateLeft(Node* node) {
    Node* rightLeftChild = node->right->left;
    if (node->parent != nullptr) {
        replaceChild(node->parent, node, node->right);
    }
    else {
        root = node->right;
        root->parent = nullptr;
    }
    setChild(node->right, "left", node);
    setChild(node, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node* node) {
    Node* leftRightChild = node->left->right;
    if (node->parent != nullptr) {
        replaceChild(node->parent, node, node->left);
    }
    else {
        root = node->left;
        root->parent = nullptr;
    }
    setChild(node->left, "right", node);
    setChild(node, "left", leftRightChild);
}


void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}