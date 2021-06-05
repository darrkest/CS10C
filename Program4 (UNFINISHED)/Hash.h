#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include "Node.h"

using namespace std;

class Hash {
    private:
        list<Node> *hashTable;
        int size;
        int computeHash(const string &);
    public:
        Hash(int);
	    bool contains(const string &);
	    void put(const string &, int);
        void sortByFreq();
};

#endif