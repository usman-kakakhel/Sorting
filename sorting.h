/* *
* Title : Algorithm Efficiency and Sorting
* Author : Main Usman Naeem Kakakhel
* ID : 21701015
* Section : 2
* Assignment : 1
* Description : header for sorting functions
*/


#ifndef MAIN_CPP_SORTING_H
#define MAIN_CPP_SORTING_H
#include <iostream>
#include <ctime>
#include <time.h>
#include <cmath>
#include <cstdlib>
using namespace std;

void bubbleSort(int *arr, int size, int &compCount, int &moveCount);
void quickSort(int *arr, int size, int &compCount, int &moveCount);
void mergeSort(int *arr, int size, int &compCount, int &moveCount);
void radixSort(int *arr, int size);
void printArray(int *arr, int size);
void performanceAnalysis();
#endif

