#include <iostream>
#include "IntList.h"
using namespace std;

int main () {

    IntList temp;
    cout << "Testing if IntList is empty: " << endl;
    cout << temp.empty() << endl;
    temp.push_back(125);
    cout << "Testing if IntList is empty after push_back(125): " << endl;
    cout << temp.empty() << endl;
    cout << "Current list: " << temp << endl;
    cout << "Pushing value of -48 to the front" << endl;
    temp.push_front(-48);
    cout << "Current list: " << temp << endl;
    cout << "Pushing back values of 1, 2000 to the back" << endl;
    temp.push_back(1);
    temp.push_back(2000);
    cout << "Current list: " << temp << endl;
    cout << "Printing reverse: ";
    temp.printReverse();
    cout << endl;
    cout << "Testing pop_back()" << endl;
    temp.pop_back();
    cout << "Current list: " << temp << endl;
    cout << "testing pop_front()" << endl;
    temp.pop_front();
    cout << "Current list: " << temp << endl;
    cout << "Printing reverse: ";
    temp.printReverse();

    return 0;
}