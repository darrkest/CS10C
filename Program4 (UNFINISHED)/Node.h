#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

class Node {

 private:
	string token;
	int freq;
 public:
	Node(const string &, int);
	void addFreq(int);
	const string & getToken();
};
#endif