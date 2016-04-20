//
//  main.cpp
//  Algorithm Programming Project
//
//  Created by Patrick M. Bush on 3/28/16.
//  Copyright © 2016 Lead Development Co. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
using namespace std;

#define DEFAULT_M 1000

/**
 @param distinctNumbers array of distinct integers of size n
 @param k an integer representing the indexed largest number to find (1 < k < n)
 *
 *@return int the kth larest number
 */
int selectKAlgorithm1(vector<int> distinctNumbers, int k);

/**
 @param numbers an array of numbers (not ordered, not distinct) of size n
 @param k an interger representing the indexed largest number to find (1 < k < n)
 *
 *@returns int the kth largest number
 */
int selectKAlgorithm2(vector<int> numbers, int k);

/**
 @param numbers an array of numbers of size n
 @param k an integer representing the indexed largest number to find (1 < k < n)
 *
 *@returns int the kth largest number
 */
int selectKAlgorithm3(vector<int> numbers, int k);

/**
 @param distinctNumbers an array of distinct integers
 @param left an int for the left of the partition (1 < left < n)
 @param right an int for the right side of the partition (1 < right < n)
 @param k an int for the indexed largest number to find (1 < k < n)
 */
int selectKAlgorithm4(vector<int> distinctNumbers, int left, int right, int k);

/**
 @param arrayToPartition an array of integers to parition based on two indices (left and right)
 @param left an int for the left partition area
 @param right an int for the right partition area
 @param pivotIndex the index on which to pivot
 *
 *@returns int the partition point to choose for sorting
 */
int partition(vector<int> &arrayToPartition, int left, int right, int pivotIndex);

/**
 *Algorithm to generate a random number to be used as the pivot index.
 *This has been adjusted from the typical way to find a random number in C++
 *to account for bias towards the low end of the random number range, so that
 *the pivot index will be unbiased
 *
 *@param min the lower end of the range
 *@param max the high end of the range
 */
int rangeRandomAlg (int min, int max);

/**
 *  A method that will generate an array with non-duplicated random numbers between 1 and size
 *
 *  @param size The size of the array to create
 *
 *  @return an array of size
 */
vector<int> generateRandomArray(int size);

/**
 *  A method tht will generate an ordered array of a certain size
 *
 *  @param size size the size of the array to create
 *
 *  @return an array of size in order of 1 -n
 */
vector<int> generateOrderedArray(int size);

/**
 *  A method that will generate an ordered array in reverse.
 *
 *  @param size the size of the array to create
 *
 *  @return An array for size from n -> 1
 */
vector<int> generateOrderedArrayReverse(int size);

/**
 *  A test function for writing to the file.
 */
void testWrite();

/**
 *  A struct representing the Running times of a given algorithm. It includes it's start time, end time, and differences in running time.
 */
struct RunningTime {
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    std::chrono::nanoseconds runningTime;
    float duration;
};

/**
 *  A struct representing the average times for each algorithm
 */
struct AverageTime {
    double averageTime;
};

/**
 *  This function can be called to run the given inputs on Alogrithm 1.
 *
 *  @param testArray an array of size N for the input
 *  @param k         the kth value
 *  @param m         the number of loop executions
 *  @param t         a RunningTime to keep track of how long it takes an algorithm to run
 */
void runInputsAlgorithm1(vector<int> testArray, int k, float m, RunningTime *t);

/**
 *  This function can be called to run the given inputs on Alogrithm 2.
 *
 *  @param testArray an array of size N for the input
 *  @param k         the kth value
 *  @param m         the number of loop executions
 *  @param t         a RunningTime to keep track of how long it takes an algorithm to run
 */
void runInputsAlgorithm2(vector<int> testArray, int k, float m, RunningTime *t);

/**
 *  This function can be called to run the given inputs on Alogrithm 3.
 *
 *  @param testArray an array of size N for the input
 *  @param k         the kth value
 *  @param m         the number of loop executions
 *  @param t         a RunningTime to keep track of how long it takes an algorithm to run
 */
void runInputsAlgorithm3(vector<int> testArray, int k, float m, RunningTime *t);

/**
 *  This function can be called to run the given inputs on Alogrithm 4.
 *
 *  @param testArray an array of size N for the input
 *  @param k         the kth value
 *  @param m         the number of loop executions
 *  @param t         a RunningTime to keep track of how long it takes an algorithm to run
 */
void runInputsAlgorithm4(vector<int> testArray, int k, float m, RunningTime *t);

/**
 *  This function will be called after each run of an algorithm to calculate the runtime for the given input
 *
 *  @param runningTimes All of the running times for a given input size of N
 *
 *  @return A struct of Average Times
 */
AverageTime calculateAverageTime(vector<RunningTime*> runningTimes);

/**
 *  A function that will write all the averages to the file after execution.
 *
 *  @param averages All of the averages that need to be written
 */
void writeAveragesToFile(vector<AverageTime> averages);


int main(int argc, const char * argv[]) {
    // insert code here...
    //std::setprecision(20);
    const int k = 5;
    vector<int> sizeOfN = {10, 20, 30, 40, 50, 70, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    
    srand(time(NULL)); // Seed the time
    vector<RunningTime *> runningTimes;
    runningTimes.reserve(228);
    vector<AverageTime> averageTimes;
    averageTimes.reserve(19);
    

    //Algorithm 1 - Run all of the inputs on Algorithm 1
    //For each run, generate an ordered array of size N, a reversed array of size N
    //and ten random arrays of size N.
    //After each run, calculate the averages for the run, and add the averages to the file
    for (int i = 0; i < sizeOfN.size(); i++) {
        vector<int> sortedArray = generateOrderedArray(sizeOfN[i]);
        RunningTime *t = new RunningTime;
        runInputsAlgorithm1(sortedArray, k, DEFAULT_M, t);
        runningTimes.push_back(t);
        RunningTime *t2 = new RunningTime;
        vector<int> reverseArray = generateOrderedArrayReverse(sizeOfN[i]);
        runInputsAlgorithm1(reverseArray, k, DEFAULT_M, t2);
        runningTimes.push_back(t2);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm1(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t3);
        }
        averageTimes.push_back(calculateAverageTime(runningTimes));
    }
    
    //clear the running times to manage memory
    runningTimes.clear();
    //writeAveragesToFile(averageTimes);
    
    //Algorithm 2
    for (int i = 0; i < sizeOfN.size(); i++) {
        vector<int> sortedArray = generateOrderedArray(sizeOfN[i]);
        RunningTime *t = new RunningTime;
        runInputsAlgorithm2(sortedArray, k, DEFAULT_M, t);
        runningTimes.push_back(t);
        RunningTime *t2 = new RunningTime;
        vector<int> reverseArray = generateOrderedArrayReverse(sizeOfN[i]);
        runInputsAlgorithm2(reverseArray, k, DEFAULT_M, t2);
        runningTimes.push_back(t2);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm2(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t3);
        }
        averageTimes.push_back(calculateAverageTime(runningTimes));
    }
    
    runningTimes.clear();
    //writeAveragesToFile(averageTimes);

    for (int i = 0; i < sizeOfN.size(); i++) {
        vector<int> sortedArray = generateOrderedArray(sizeOfN[i]);
        RunningTime *t = new RunningTime;
        runInputsAlgorithm3(sortedArray, k, DEFAULT_M, t);
        runningTimes.push_back(t);
        RunningTime *t2 = new RunningTime;
        vector<int> reverseArray = generateOrderedArrayReverse(sizeOfN[i]);
        runInputsAlgorithm3(reverseArray, k, DEFAULT_M, t2);
        runningTimes.push_back(t2);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm3(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t3);
        }
        averageTimes.push_back(calculateAverageTime(runningTimes));
    }
    
    runningTimes.clear();
    //writeAveragesToFile(averageTimes);
    
    for (int i = 0; i < sizeOfN.size(); i++) {
        vector<int> sortedArray = generateOrderedArray(sizeOfN[i]);
        RunningTime *t = new RunningTime;
        runInputsAlgorithm4(sortedArray, k, DEFAULT_M, t);
        runningTimes.push_back(t);
        RunningTime *t2 = new RunningTime;
        vector<int> reverseArray = generateOrderedArrayReverse(sizeOfN[i]);
        runInputsAlgorithm4(reverseArray, k, DEFAULT_M, t2);
        runningTimes.push_back(t2);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm4(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t3);
        }
        averageTimes.push_back(calculateAverageTime(runningTimes));
    }
    
    runningTimes.clear();
    //after all the averages have been calculated, write them to the file
    writeAveragesToFile(averageTimes);
    //testWrite();
    return 0;
}

void writeAveragesToFile(vector<AverageTime> averages) {
    ofstream myFile;
    myFile.open("ProgrammingProject-pmb-Bush.txt");
    if (myFile.is_open()) {
        myFile << std::fixed << std::setprecision(5) << averages[0].averageTime;
        int i = 1;
        for (; i < 75; i++) {
            if (i % 19 == 0) {
                myFile << "\n" << std::fixed << std::setprecision(5) << averages[i].averageTime;
                continue;
            }
            myFile << std::fixed << std::setprecision(5) << ", " << averages[i].averageTime;
        }
        myFile << std::fixed << std::setprecision(5) << ", " << averages[75].averageTime;
    }
    myFile.close();

}

/**
 *  Calculate the average time by taking the running times for each run, and adding it.
 *  Then divide by the number of inputs
 *
 *  @param runningTimes All of the running times for certain input size
 *
 *  @return An average time for the given input
 */
AverageTime calculateAverageTime(vector<RunningTime *> runningTimes) {
    AverageTime averageTime;
    double average = 0;
    for (int i = 0; i < runningTimes.size(); i++) {
        average += runningTimes[i]->duration;
    }
    average = average / runningTimes.size();
    averageTime.averageTime = average;
    return averageTime;
}

/**
 For each input running function...
 *  Get the start time from the system clock
 *  Run the selected algorithm M times
 *  Get the end time from the system clock
 *  Calculate the running time: cast the duration to nanoseconds and get the difference
 *  Check if the running time is 0, and if it is then call the function again with a different M size
 *  Otherwise, get the duration divided by M and back out
 */
void runInputsAlgorithm1(vector<int> testArray, int k, float m, RunningTime *t) {
    t->startTime = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < m; j++) {
        selectKAlgorithm1(testArray, k);
    }
    t->endTime = std::chrono::high_resolution_clock::now();
    t->runningTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t->endTime - t->startTime);
    if (t->runningTime.count() == 0) {
        runInputsAlgorithm1(testArray, k, m * 2, t);
    } else {
        t->duration = t->runningTime.count() / m;
        return;
    }
}

void runInputsAlgorithm2(vector<int> testArray, int k, float m, RunningTime *t) {
    t->startTime = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < DEFAULT_M; j++) {
        selectKAlgorithm2(testArray, k);
    }
    t->endTime = std::chrono::high_resolution_clock::now();
    t->runningTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t->endTime - t->startTime);
    if (t->runningTime.count() == 0) {
        runInputsAlgorithm2(testArray, k, m * 2, t);
    } else {
        t->duration = t->runningTime.count() / m;
        return;
    }
}

void runInputsAlgorithm3(vector<int> testArray, int k, float m, RunningTime *t) {
    t->startTime = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < DEFAULT_M; j++) {
        selectKAlgorithm3(testArray, k);
    }
    t->endTime = std::chrono::high_resolution_clock::now();
    t->runningTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t->endTime - t->startTime);
    if (t->runningTime.count() == 0) {
        runInputsAlgorithm3(testArray, k, m * 2, t);
    } else {
        t->duration = t->runningTime.count() / m;
        return;
    }
}

void runInputsAlgorithm4(vector<int> testArray, int k, float m, RunningTime *t) {
    int right = testArray.size() - 1;
    int left = 0;
    t->startTime = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < DEFAULT_M; j++) {
        selectKAlgorithm4(testArray, left, right, k);
    }
    t->endTime = std::chrono::high_resolution_clock::now();
    t->runningTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t->endTime - t->startTime);
    if (t->runningTime.count() == 0) {
        runInputsAlgorithm4(testArray, k, m * 2, t);
    } else {
        t->duration = t->runningTime.count() / m;
        return;
    }
}
/**
 Generate an array of random numbers of size N
 *  Create an array of a certain size
 *  Generate a random number, and if it's not in the list then add it, otherwise
 *  back out and create a new number
 */

vector<int> generateRandomArray(int size) {
    vector<int> randomArray = vector<int>(size, 0);
    for (int i = 0; i < randomArray.size(); i++) {
        int num = rangeRandomAlg(1, size);
        if (find(randomArray.begin(), randomArray.end(), num) != randomArray.end()) {
            i--;
        } else {
            randomArray[i] = num;
        }
    }
    return randomArray;
}

/**
 To generate an ordered array...
 *  Create an array of the specific size
 *  Add the elements, and return
 */
vector<int> generateOrderedArray(int size) {
    vector<int> orderedArray = vector<int>(size, 0);
    for (int i = 0; i < orderedArray.size(); i++) {
        orderedArray[i] = i + 1;
    }
    return orderedArray;
}

/**
 To generate an ordered array in reverse
 *  Generate an ordered array, and then reverse the array
 *  return
 */
vector<int> generateOrderedArrayReverse(int size) {
    vector<int> orderedArray = generateOrderedArray(size);
    reverse(orderedArray.begin(), orderedArray.end());
    return orderedArray;
}

/**
 Algorithm 1
 */

int selectKAlgorithm1(vector<int> distinctNumbers, int k) {
    int n = distinctNumbers.size();
    k--;
    for (int i = 1; i <= k; i++) {
        for (int j = n - 1; j >= i; j--) {
            if (distinctNumbers[j] > distinctNumbers[j - 1]) {
                int temp = distinctNumbers[j];
                distinctNumbers[j] = distinctNumbers[j - 1];
                distinctNumbers[j - 1] = temp;
            }
        }
    }
    
    return distinctNumbers[--k];
}

/**
 Alorithm 2
 */
int selectKAlgorithm2(vector<int> numbers, int k) {
    int n = numbers.size();
    for (int i = 1; i <= k; i++) {
        int position = i;
        for(int j = (i + 1); j <= n; j++) {
            if (numbers[j] > numbers[position]) {
                position = j;
            }
            if (position != i) {
                int temp = numbers[i];
                numbers[i] = numbers[position];
                numbers[position] = temp;
            }
        }
    }
    return numbers[k - 1];
}

/**
 Alogorithm 3
 */
int selectKAlgorithm3(vector<int> numbers, int k) {
    int n = numbers.size();
    vector<int> sortedNumbers = vector<int>(k);
    k--;
    for (int i = 0; i <= k; i++) {
        sortedNumbers[i] = numbers[i];
    }
    int min = 0;
    for (int j = 1; j <= k; j++) {
        if (sortedNumbers[j] < sortedNumbers[min]) {
            min = j;
        }
    }
    
    for (int p = (k + 1); p < n; p++) {
        if (numbers[p] > sortedNumbers[min]) {
            sortedNumbers[min] = numbers[p];
            min = 0;
            for (int l = 1; l <= k; l++) {
                if (sortedNumbers[l] < sortedNumbers[min]) {
                    min = l;
                }
            }
        }
    }
    return sortedNumbers[min];
}

/**
 Algorithm 4
 */
int selectKAlgorithm4(vector<int> distinctNumbers, int left, int right, int k) {
    int pivotIndex = rangeRandomAlg(left, right); //generate a random number such that left <= index <= right
    int newPivotIndex = partition(distinctNumbers, left, right, pivotIndex);
    if ((newPivotIndex - left) >= k) {
        return selectKAlgorithm4(distinctNumbers, left, (newPivotIndex -1), k);
    } else if (newPivotIndex - left == k - 1) {
        return distinctNumbers[newPivotIndex];
    } else {
        return selectKAlgorithm4(distinctNumbers, (newPivotIndex + 1), right, (k - newPivotIndex + left - 1));
    }
}

/**
 Partition used in Algorithm 4
 */
int partition(vector<int> &arrayToPartition, int left, int right, int pivotIndex) {
    int pivotValue = arrayToPartition[pivotIndex];
    swap(arrayToPartition[pivotIndex], arrayToPartition[right]);
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arrayToPartition[i] > pivotValue) {
            swap(arrayToPartition[storeIndex], arrayToPartition[i]);
            storeIndex++;
        }
    }
    swap(arrayToPartition[right], arrayToPartition[storeIndex]);
    return storeIndex;
}

/**
 This algorithm was used from the wonderful people at StackOverflow.
 The source can be found here: http://stackoverflow.com/questions/11758809/what-is-the-optimal-algorithm-for-generating-an-unbiased-random-integer-within-a?answertab=votes#tab-top
 It's design is such that it takes into account true randomness
 */
int rangeRandomAlg (int min, int max){
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do{
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

void testWrite() {
    vector<AverageTime> test = vector<AverageTime>(76);
    for (int i = 0; i < 76; i++) {
        AverageTime t;
        t.averageTime = i;
        test[i] = t;
    }
    writeAveragesToFile(test);
}

