#include "BSTree.h"
#include <iostream>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

BSTree::~BSTree() {
    deleteSubtree(root);
}

void BSTree::deleteSubtree(Node* curr) {
    if (curr != nullptr)    {
        if (curr->left != nullptr) {
            deleteSubtree(curr->left);
        }
        else if (curr->right != nullptr) {
            deleteSubtree(curr->right);
        }
        delete curr;
    }
}

void BSTree::insert(const string &newString) {
    Node *curr = root;
    Node *newNode = new Node(newString);
    
    if(search(newString))  {
        curr = search(newString, root);
        curr->count++;
    }
    else    {
        if (curr == nullptr) {
            root = newNode;
        }
        else {
            while (curr != nullptr) {
                if (newNode->data < curr->data) {
                    if (curr->left == nullptr)  {
                        curr->left = newNode;
                        newNode->parent = curr;
                        curr = nullptr;
                        return;
                    }
                    else {
                        curr = curr->left;
                    }
                }
                else {
                    if (curr->right == nullptr) {
                        curr->right = newNode;
                        newNode ->parent = curr;
                        curr = nullptr;
                        return;
                    }
                    else {
                        curr = curr->right;
                    }
                }
            }
        }
    }
}

void BSTree::remove(const string &key) {
    if (search(key)) {
        Node* curr = search(key, root);
        if(curr->count >1 ){
            curr->count = curr->count - 1;
        }
        else{
            del(curr);
        }
    }
}

void BSTree::del(Node* data) {
    Node *curr = data;
	Node *suc = 0;

	if(curr->left == 0 && curr->right == 0) {
		if(curr->parent != 0) {
			if(curr->parent->left == curr) {
				curr->parent->left = 0;
			}
			else {
				curr->parent->right = 0;
			}
		}
		else {
			root = 0;
		}
		delete curr;
	}
	else if(curr->left != 0) {
		suc = curr->left;
		while(suc->right != 0) {
			suc = suc->right;
		}
		*curr = *suc;
		del(suc);
	}
	else {
		suc = curr->right;
		while(suc->left != 0) {
			suc = suc->left;
		}
		*curr = *suc;
		del(suc);
	}
}


Node* BSTree::search(const string &key, Node* curr) const {
    if (curr != nullptr) {
        if (key == curr->data) {
            return curr;
        }
        else {
            if (key < curr->data) {
                return search(key, curr->left);
            }
            else if (key > curr->data) {
                return search(key, curr->right);
            }
        }
    }
    return nullptr;
}

bool BSTree::search(const string &key) const {
    return search(key, root);
}

string BSTree::largest() const {
    Node* curr = root;
    if (curr == nullptr) {
        return "";
    }
    else{
        while (curr != nullptr) {
            if (curr->right == nullptr) {
                return curr->data;
            }
            else {
                curr = curr->right;
            }
        }
    }
    return curr->data;
}

string BSTree::smallest() const {
    Node* curr = root;
    if (curr == nullptr) {
        return "";
    }
    else{
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                return curr->data;
            }
            else {
                curr = curr->left;
            }
        }
    }
    return curr->data;
}
int BSTree::height(const string& key) const {
   
    if(!search(key)) {
        return -1;
    }

    Node *curr = search(key, root);
    Node *currL = curr;
    Node *currR = curr;
    int Lcount = 0;
    int Rcount = 0;
    
    if(curr->left != 0) {
        currL = currL->left;
        Lcount++;
        Lcount = Lcount + height(currL->data);
    }

    if(curr->right != 0) {
        currR = currR->right;
        Rcount++;
        Rcount = Rcount + height(currR->data);
    }
    if(Lcount >= Rcount) {
        return Lcount;
    }

    else {
        return Rcount;
    }

}

void BSTree::inOrder(Node* curr) const   {
    if (curr == nullptr) {
        return;
    }
    else {
        inOrder(curr->left);
        cout << curr->data << "(" << curr->count << "), ";
        inOrder(curr->right);
    }
}

void BSTree::postOrder(Node* curr) const  {
    if (curr == nullptr) {
        return;
    }
    else {
        postOrder(curr->left);
        postOrder(curr->right);
        cout << curr->data << "(" << curr->count << "), ";
    }
}

void BSTree::preOrder(Node* curr) const   {
    if (curr == nullptr) {
        return;
    }
    else {
        cout << curr->data << "(" << curr->count << "), ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void BSTree::preOrder() const {
    return preOrder(root);
}

void BSTree::postOrder() const {
    return postOrder(root);
}

void BSTree::inOrder() const {
    return inOrder(root);
}