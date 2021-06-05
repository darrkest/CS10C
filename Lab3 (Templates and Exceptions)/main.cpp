#include <iostream>
#include <vector>
#include <ctime>
#include <stdexcept>
using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned int minIndex = index;
    for (unsigned i = index; i < vals.size(); ++i) {
        if (vals.at(i) < minIndex) {
            minIndex = i;
        }
    }
    return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals) {
    for (unsigned int i = 0; i < vals.size(); ++i) {
        int indexSmallest = i;
        for (unsigned int j = i + 1; j < vals.size(); ++j) {
            if (vals.at(j) < vals.at(indexSmallest)) {
                indexSmallest = j;
            }
        }
        T temp = vals.at(i);
        vals.at(i) = vals.at(indexSmallest);
        vals.at(indexSmallest) = temp;
    }
}

template<typename T>
T getElement(vector<T> vals, int index) {
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){

    // Test harness for selection_sort
    // vector<char> temp;
    // temp.push_back('h');
    // temp.push_back('e');
    // temp.push_back('l');
    // temp.push_back('l');
    // temp.push_back('o');
    // for (unsigned int i = 0; i < temp.size(); ++i) {
    //     cout << temp.at(i) << " ";
    // }

    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     unsigned int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;

         try {
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
            //  if (index < 0) {
            //      throw std::out_of_range("Number too low");
            //  }
            //  else if (index >= vals.size()) {
            //      throw std::out_of_range("Number too high");
            //  }
         }
         catch (const std::out_of_range& excpt) {
             cout << "out of range exception occured" << endl;
         }
     }
     

    return 0;
}