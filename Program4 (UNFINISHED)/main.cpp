#include "Hash.h"
#include <fstream>
using namespace std;

int main() {
    string userFile;
    cout << "Enter file name: ";
    cin >> userFile;
    cout << endl;

    ifstream inFS(userFile);
    if (!inFS.is_open()) {
        cout << "Error opening file." << endl;
        exit(1);
    }

    string currLine;
    Hash table(20071);
    int numWords;

    while (!inFS.eof()) {
	    getline(inFS, currLine);
	    int len = currLine.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = currLine.find(" ");
	        if (len > 0) {
	            sub = currLine.substr(0, len);
	            currLine = currLine.substr(len + 1, currLine.size());
	        }
	        else {
	            sub = currLine.substr(0, currLine.size() - 1);
	        }
            table.put(sub, 1); // insert string with freq 1
	    }
	}
    

    return 0;
}

