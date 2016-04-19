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
using namespace std;

#define DEFAULT_M 100000

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
 *  A method that will generate an array from 1 - n
 *
 *  @param size the size of the array to create
 *
 *  @return an array with distinct values
 */
vector<int> generateDistinctArray(int size);


vector<int> generateOrderedArray(int size);

vector<int> generateOrderedArrayReverse(int size);


struct RunningTime {
    time_t startTime;
    time_t endTime;
    double runningTime = 0;
};

struct AverageTime {
    double averageTime;
};

typedef struct {
    vector<int> testArray;
    int k;
    int m;
    RunningTime *t;
} thread_args_t;

void runInputsAlgorithm1(vector<int> testArray, int k, float m, RunningTime *t);
void runInputsAlgorithm2(vector<int> testArray, int k, float m, RunningTime *t);
void runInputsAlgorithm3(vector<int> testArray, int k, float m, RunningTime *t);
void runInputsAlgorithm4(vector<int> testArray, int k, float m, RunningTime *t);

AverageTime calculateAverageTime(vector<RunningTime*> runningTimes);

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
    

    //Algorithm 1
    for (int i = 0; i < sizeOfN.size(); i++) {
        vector<int> sortedArray = generateOrderedArray(sizeOfN[i]);
        RunningTime *t = new RunningTime;
        runInputsAlgorithm1(sortedArray, k, DEFAULT_M, t);
        runningTimes.push_back(t);
        RunningTime *t2 = new RunningTime;
        vector<int> reverseArray = generateOrderedArrayReverse(sizeOfN[i]);
        runInputsAlgorithm1(reverseArray, k, DEFAULT_M, t2);
        runningTimes.push_back(t);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm1(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t);
        }
        averageTimes.push_back(calculateAverageTime(runningTimes));
    }
    
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
        runningTimes.push_back(t);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm2(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t);
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
        runningTimes.push_back(t);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm3(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t);
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
        runningTimes.push_back(t);
        for (int j = 0; j < 10; j++) {
            RunningTime *t3 = new RunningTime;
            vector<int> random = generateRandomArray(sizeOfN[i]);
            runInputsAlgorithm4(random, k, DEFAULT_M, t3);
            runningTimes.push_back(t);
        }
        averageTimes.push_back(calculateAverageTime(runningTimes));
    }
    
    runningTimes.clear();
    writeAveragesToFile(averageTimes);
    
    return 0;
}

void writeAveragesToFile(vector<AverageTime> averages) {
    ofstream myFile;
    myFile.open("ProgrammingProject-pmb-Bush.txt");
    if (myFile.is_open()) {
        int i = 0;
        while (i <= averages.size()) {
            switch (i) {
                case 0:
                    myFile << std::fixed << std::setprecision(20) << averages[i].averageTime;
                    break;
                case 19:
                    myFile << std::fixed << std::setprecision(20) << averages[i].averageTime;
                    break;
                case 37:
                    myFile << std::fixed << std::setprecision(20) << averages[i].averageTime;
                    break;
                case 56:
                    myFile << std::fixed << std::setprecision(20) << averages[i].averageTime;
                    break;
                default:
                    myFile << std::fixed << std::setprecision(20) << ", " << averages[i].averageTime;
                    break;
            }
            if (i % 19 == 0) {
                myFile << "\n";
            }
            i++;
        }
    }
    myFile.close();
    
}


AverageTime calculateAverageTime(vector<RunningTime *> runningTimes) {
    AverageTime averageTime;
    double average = 0;
    for (int i = 0; i < runningTimes.size(); i++) {
        average += runningTimes[i]->runningTime;
    }
    average = average / runningTimes.size();
    averageTime.averageTime = average;
    return averageTime;
}

void runInputsAlgorithm1(vector<int> testArray, int k, float m, RunningTime *t) {
    t->startTime = time(0);
    for (int j = 0; j < m; j++) {
        selectKAlgorithm1(testArray, k);
    }
    t->endTime = time(0);
    double times = difftime(t->endTime, t->startTime);
    if (times == 0) {
        runInputsAlgorithm1(testArray, k, m * 2, t);
    } else {
        t->runningTime = times / m;
        return;
    }
}

void runInputsAlgorithm2(vector<int> testArray, int k, float m, RunningTime *t) {
    t->startTime = time(0);
    for (int j = 0; j < DEFAULT_M; j++) {
        selectKAlgorithm2(testArray, k);
    }
    t->endTime = time(0);
    double times = difftime(t->endTime, t->startTime);
    if (times == 0) {
        runInputsAlgorithm2(testArray, k, m * 2, t);
    } else {
        t->runningTime = times / m;
        return;
    }
}

void runInputsAlgorithm3(vector<int> testArray, int k, float m, RunningTime *t) {
    t->startTime = time(0);
    for (int j = 0; j < DEFAULT_M; j++) {
        selectKAlgorithm3(testArray, k);
    }
    t->endTime = time(0);
    double times = difftime(t->endTime, t->startTime);

    if (times == 0) {
        runInputsAlgorithm3(testArray, k, m * 2, t);
    } else {
        t->runningTime = times / m;
        return;
    }
}

void runInputsAlgorithm4(vector<int> testArray, int k, float m, RunningTime *t) {
    int right = testArray.size() - 1;
    int left = 0;
    t->startTime = time(0);
    for (int j = 0; j < DEFAULT_M; j++) {
        selectKAlgorithm4(testArray, left, right, k);
    }
    t->endTime = time(0);
    double times = difftime(t->endTime, t->startTime);
    if (times == 0) {
        runInputsAlgorithm4(testArray, k, m * 2, t);
    } else {
        t->runningTime = times / m;
        return;
    }
}
/**
 Generate an array of random numbers of size N
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

vector<int> generateDistinctArray(int size) {
    vector<int> distinctValues = vector<int>(size, 0);
    //Need to create the random array, but before a number is added
    //we have to check to see if it already exists, and if so decrement i
    for (int i = 0; i < distinctValues.size(); i++) {
        int x = rand() % 1000;
        if (find(distinctValues.begin(), distinctValues.end(), x) != distinctValues.end()) {
            i--;
            break;
        }
        distinctValues[i] = x;
    }
    return distinctValues;
}

vector<int> generateOrderedArray(int size) {
    vector<int> orderedArray = vector<int>(size, 0);
    for (int i = 0; i < orderedArray.size(); i++) {
        orderedArray[i] = i + 1;
    }
    return orderedArray;
}

vector<int> generateOrderedArrayReverse(int size) {
    vector<int> orderedArray = generateOrderedArray(size);
    reverse(orderedArray.begin(), orderedArray.end());
    return orderedArray;
}

/**
 Get the results of running the first Algorithm
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

int rangeRandomAlg (int min, int max){
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do{
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

