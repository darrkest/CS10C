#include "Hash.h"

Hash::Hash(int s) {
    hashTable = new list<Node>[s];
    size = s;
}

int Hash::computeHash(const string &s) {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < s.size(); ++i) {
        sum = (sum *  33) + s[i];
    }
    return (sum % size);
}

void Hash::put(const string &s, int freq) {
    int index = computeHash(s);
	for (list<Node>::iterator i = hashTable[index].begin(); i != hashTable[index].end(); ++i) {
        if (i->getToken() == s) {
            i->addFreq(freq);
            return;
        }
    }
    Node* curr = new Node(s, freq);
    hashTable[index].push_back(*curr);
}

bool Hash::contains(const string &s) {
    int index = computeHash(s);
    for (list<Node>::iterator i = hashTable[index].begin(); i != hashTable[index].end(); ++i) {
        if (i->getToken() == s) {
            return true;
        }
    }
    return false;
}

void Hash::sortByFreq() {
    
}