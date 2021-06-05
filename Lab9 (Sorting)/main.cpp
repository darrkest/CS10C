#include <iostream>
#include <ctime>
#include <string>

using namespace std;

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

int Partition_midpoint(int numbers[], int lowIndex, int highIndex) {
    // Pick middle element as pivot
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    int pivot = numbers[midpoint];
   
    bool done = false;
    while (!done) {
        // Increment lowIndex while numbers[lowIndex] < pivot
        while (numbers[lowIndex] < pivot) {
            lowIndex += 1;
        }
      
        // Decrement highIndex while pivot < numbers[highIndex]
        while (pivot < numbers[highIndex]) {
            highIndex -= 1;
        }
      
        // If zero or one elements remain, then all numbers are 
        // partitioned. Return highIndex.
        if (lowIndex >= highIndex) {
            done = true;
        }
        else {
            // Swap numbers[lowIndex] and numbers[highIndex]
            int temp = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = temp;
         
            // Update lowIndex and highIndex
            lowIndex += 1;
            highIndex -= 1;
        }
    }
   
   return highIndex;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    // Base case: If the partition size is 1 or zero 
    // elements, then the partition is already sorted
    if (i >= k) {
        return;
    }
   
    // Partition the data within the array. Value lowEndIndex 
    // returned from partitioning is the index of the low 
    // partition's last element.
    int lowEndi;
    lowEndi = Partition_midpoint(numbers, i, k);
   
    // Recursively sort low partition (lowIndex to lowEndIndex) 
    // and high partition (lowEndIndex + 1 to highIndex)
    Quicksort_midpoint(numbers, i, lowEndi);
    Quicksort_midpoint(numbers, lowEndi + 1, k);
}

int Partition_medianOfThree(int numbers[], int lowIndex, int highIndex) {
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;

    // Pick median element as pivot
    midpoint = lowIndex + (highIndex - lowIndex) / 2;

    if (numbers[midpoint] > numbers[lowIndex]){

        if (numbers[midpoint] > numbers[highIndex]){ // right most is median
            pivot = numbers[highIndex];
        }
        else{      // midpoint is median
            pivot = numbers[midpoint];
        }
    }

    else{

        if (numbers[lowIndex] > numbers[highIndex]){ // right most is median
            pivot = numbers[highIndex];
        }
        else{     // left most is median
            pivot = numbers[lowIndex];
        }
    }

    while (!done){

        // Increment lowIndex while numbers[lowIndex] < pivot
        while (numbers[lowIndex] < pivot){           
            ++lowIndex;
        }
        // Decrement highIndex while pivot < numbers[highIndex]
        while (pivot < numbers[highIndex]){
            --highIndex;
        }

        // If there are zero or one elements remaining,
        // all numbers are partitioned. Return highIndex
        if (lowIndex >= highIndex){
            done = true;
        }
        else{
            // Swap numbers[lowIndex] and numbers[highIndex],
            // update lowIndex and highIndex
            temp = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = temp;

            ++lowIndex;
            --highIndex;
        }
    }

    return highIndex;
}


void Quicksort_medianOfThree(int numbers[], int i, int k) {
    // Base case: If the partition size is 1 or zero 
    // elements, then the partition is already sorted
    if (i >= k) {
        return;
    }
   
    // Partition the data within the array. Value lowEndIndex 
    // returned from partitioning is the index of the low 
    // partition's last element.
    int lowEndi;
    lowEndi = Partition_medianOfThree(numbers, i, k);
   
    // Recursively sort low partition (lowIndex to lowEndIndex) 
    // and high partition (lowEndIndex + 1 to highIndex)
    Quicksort_medianOfThree(numbers, i, lowEndi);
    Quicksort_medianOfThree(numbers, lowEndi + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
    int i = 0;
    int j = 0;
    int temp = 0;
   
    for (i = 1; i < numbersSize; ++i) {
        j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
}

int main() {
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr1,arr2,arr3); 
    const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;

    clock_t Start1 = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    clock_t End1 = clock();
    int elapsedTime1 = (End1 - Start1)/CLOCKS_PER_MS;
    cout << "Elapsed time of Quicksort (midpoint): " << elapsedTime1 << endl;

    clock_t Start2 = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    clock_t End2 = clock();
    int elapsedTime2 = (End2 - Start2)/CLOCKS_PER_MS;
    cout << "Elapsed time of Quicksort (median of 3): " << elapsedTime2 << endl;

    clock_t Start3 = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    clock_t End3 = clock();
    int elapsedTime3 = (End3 - Start3)/CLOCKS_PER_MS;
    cout << "Elapsed time of insertion sort: " << elapsedTime3 << endl;

    return 0;
}