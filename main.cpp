/* *
* Title : Algorithm Efficiency and Sorting
* Author : Main Usman Naeem Kakakhel
* ID : 21701015
* Section : 2
* Assignment : 1
* Description : All sorting functions are being called
*/




#include "sorting.h"

int main()
{
    int lista[] = {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    int listb[] = {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    int listc[] = {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    int listd[] = {7, 3, 6, 12, 13, 4, 1, 9, 15, 0, 11, 14, 2, 8, 10, 5};
    int compCount;
    int moveCount;
    int size = 16;

    bubbleSort(lista, size, compCount, moveCount);
    printArray(lista, size);
    
    mergeSort(listb, size, compCount, moveCount);
    printArray(listb, size);
    
    quickSort(listc, size, compCount, moveCount);
    printArray(listc, size);
    
    radixSort(listd, size);
    printArray(listd, size);

    performanceAnalysis();



    return 0; 
}
