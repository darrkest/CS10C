#include <iostream>
#include <stack>
#include <sstream>
#include <fstream>
#include "arithmeticExpression.h"
using namespace std;

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

arithmeticExpression::arithmeticExpression(const string &value) {
    infixExpression = value;
    root = nullptr;
}

void arithmeticExpression::buildTree() {
    infixExpression = infix_to_postfix();                                       // Change to postfix
    stack<TreeNode*> stack;                                                     // Create a stack to store the expression as its traversed
    for (unsigned int i = 0; i < infixExpression.size(); ++i) {                 // Traverse the expression
        TreeNode* curr = new TreeNode(infixExpression.at(i), 'a' + i);          // Create a node with the current character
        if (priority(infixExpression.at(i)) == 0) {                             // If the current character is not an operation, then push it on the stack
            stack.push(curr);
        }
        else {                                                                   // If the current character is an operation, then it's gonna become the root node
            curr->right = stack.top();                                           // Make the right node of the operation's node what's at the top of the stack, then remove from stack
            stack.pop();                                                                    
            curr->left = stack.top();                                            // Make the left node of the operation's node anything that is next on top of stack, then remove from stack
            stack.pop();
            stack.push(curr);                                                    // Push the current tree to the top of stack
            root = curr;                                                         // Set the root to be the current tree
        }
    }
}

void arithmeticExpression::infix() {
    infix(root);
}

void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::infix(TreeNode *tree) {
    if (tree == nullptr) {
        return;
    }
    if (priority(tree->data) != 0) {
        cout << "(";
        infix(tree->left);
        cout << tree->data;
        infix(tree->right);
        cout << ")";
    }
    else {
        infix(tree->left);
        cout << tree->data;
        infix(tree->right);
    }
}

void arithmeticExpression::prefix(TreeNode *tree) {
    if (tree == nullptr) {
        return;
    }
    cout << tree->data;
    prefix(tree->left);
    prefix(tree->right);
}

void arithmeticExpression::postfix(TreeNode *tree) {
    if (tree == nullptr) {
        return;
    }
    postfix(tree->left);
    postfix(tree->right);
    cout << tree->data;
}

void arithmeticExpression::visualizeTree(ofstream & outFS, TreeNode *n){
    if(n){
        outFS<<n->key << "[ label = \""<<n->data<<"\"];"<<endl;
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->key <<" -> " <<n->left->key<<";"<<endl;    
        }
        
        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->key <<" -> " <<n->right->key<<";"<<endl;    
        }
    }
}