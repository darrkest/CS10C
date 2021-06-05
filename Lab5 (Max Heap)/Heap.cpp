#include <iostream>
#include "Heap.h"

Heap::Heap() {
    numItems = 0;
}

void Heap::enqueue ( PrintJob* value) {
    if (numItems < MAX_HEAP_SIZE)  {
        arr[numItems] = value;
        trickleUp(numItems);
        numItems++;
    }
}

void Heap::dequeue ( )  {
    if (numItems == 1) {
        arr[0] = nullptr;
        numItems = 0;
    }
    else if (numItems == 0) {
        return;
    }
    else {
        arr[0] = arr[numItems-1];
        arr[numItems-1] = nullptr;
        numItems--;
        trickleDown(0);
    }
}

PrintJob* Heap::highest ( ) {
    if (numItems == 0) {
        return nullptr;
    }
    else {
        return arr[0];
    }
}

void Heap::print ( )    {
    cout << "Priority: " << highest()->getPriority() << ", ";
    cout << "Job Number: " << highest()->getJobNumber() << ", ";
    cout << "Number of Pages: " << highest()->getPages() << endl;
}

void Heap::trickleDown(int index) {
    int childIndex = 2 * index + 1;
    PrintJob* value = arr[index];
    while (childIndex < numItems)   {
        PrintJob* maxValue = value;
        int maxIndex = -1;
        for (int i = 0; i < 2 && i + childIndex < numItems; ++i) {
            if (arr[i+childIndex]->getPriority() > maxValue->getPriority()) {
                maxValue = arr[i+childIndex];
                maxIndex = i + childIndex;
            }
        }
        if (maxValue->getPriority() == value->getPriority()) {
            return;
        }
        else {
            PrintJob* temp = arr[index];
            arr[index] = arr[maxIndex];
            arr[maxIndex] = temp;
            index = maxIndex;
            childIndex = 2 * index + 1;
        }
    }
}

void Heap::trickleUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) /2;
        if (arr[index]->getPriority() <= arr[parentIndex]->getPriority()) {
            return;
        }
        else {
            PrintJob* temp = arr[parentIndex];
            arr[parentIndex] = arr[index];
            arr[index] = temp;
            index = parentIndex;
        }
    }
}