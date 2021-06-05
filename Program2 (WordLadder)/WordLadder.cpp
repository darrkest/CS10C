#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include "WordLadder.h"
using namespace std;

WordLadder::WordLadder(const string &userFile) {
    ifstream inFS;
    inFS.open(userFile);

    if (!inFS.is_open()) {
        cout << "Could not open file " << userFile << "." << endl;
        return;
    }
    else {
        string userInput;
        while (!inFS.eof())   {
            inFS >> userInput;
            if (userInput.length() != 5) {
                cout << "Word inputted is not 5 letter long" << endl;
                return;
            }
            else {
                dict.push_back(userInput);
            }
        }
        inFS.close();
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    ofstream outFS;
    outFS.open(outputFile);
    if (!outFS.is_open()) {
        cout << "Opening output file failed." << endl;
    }
 
    queue<stack<string>> initialQueue;
    stack<string> initialStack;
    string topWord;
    list<string>::iterator i;
    bool startPos = false; 
    bool endPos = false;
  
    for (i = dict.begin(); i != dict.end(); ++i) {                                                  // Check if start and end words are in dictionary
        if (*i == start) {
            startPos = true;
        }
        if (*i == end) {
            endPos = true;
        }
    }
    if (!startPos or !endPos) {                                                                     // If not, then return
        cout << "Not found in the dictionary." << endl;
        return;
    }
    if (start == end) {                                                                             // If start and end words are the same, output the word and return
        outFS<< start;
        outFS.close();
        return;    
    }

    initialStack.push(start);                                                                       // Push first word to stack
    initialQueue.push(initialStack);                                                                // Push stack w/ first word to queue

    dict.remove(start);                                                                             // Remove the start word
    while(!initialQueue.empty()) {                                                                  
      
        topWord = initialQueue.front().top();                                                       
        for (i = dict.begin(); i != dict.end(); ++i) {                                              // Traverse entire dictionary
            if (check(topWord,*i)) {                                                                    // If the top word and the current word being traversed share 4 characters,
                stack<string> copyStack = initialQueue.front();                                         // Create a new stack and copy over the previous word that was saved
                copyStack.push(*i);                                                                     // Push the current word that's similar to the stack
                
                if(*i == end){                                                                      // If the current word is the same as the end one, then done
                    output(copyStack, outFS);
                    return;
                }
                initialQueue.push(copyStack);                                                       // Add the updated stack to the queue
                i = dict.erase(i);                                                                  // Remove the word found from the dictionary to avoid repeat
             
                i--;
            }
        }
        initialQueue.pop();
    }

    if (outFS.is_open()) {
        outFS << "No Word Ladder Found.";
    
    }
}

bool WordLadder::check(string word, string dictionaryWord) {
    int character = 0;
    for (int i = 0; i < 5; ++i) {
        if (word[i] == dictionaryWord[i]) { 
            character++; 
            }
        }
    if (character == 4) {
        return true;
    } else {
        return false;
    }
}

void WordLadder::output(stack<string> stack, ofstream &outFS) {
    int i = 0;
    vector<string> ladder;

    while (!stack.empty()) {
        ladder.push_back(stack.top());
        stack.pop();
        i++;
    }
  
    if (outFS.is_open()) {
        while (i != 0) {
            i--;
            outFS << ladder.at(i);
     
            if (i != 0) {
                outFS << " ";
                
            }
        }
       
    }
   
  
}