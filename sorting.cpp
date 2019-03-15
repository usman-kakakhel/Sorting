/* *
* Title : Algorithm Efficiency and Sorting
* Author : Main Usman Naeem Kakakhel
* ID : 21701015
* Section : 2
* Assignment : 1
* Description : This file has all the sorting algorithms including radix, merge, bubble, quick sort.
*/

#include "sorting.h"

void swap(int &x, int &y) {
   int temp = x;
   x = y;
   y = temp;
}

void bubbleSort(int *arr, int size, int &compCount, int &moveCount)
{
    compCount = 0;
    moveCount = 0;

    bool flag = false;

    for (int a  = size - 1; (a > 0) && (!flag); a--) //traverse over the whole array atmost n - 1 times
    {
        flag = true;
        for (int index = 0; index < a; index++)
        {
            int nextIndex = index + 1;
            compCount++; //the elements at index are being checked thus increase compCount by 1
            if (arr[nextIndex] < arr[index])
            {
                moveCount = moveCount + 3;
                flag = false;
                swap(arr[index], arr[nextIndex]); //swap the twp elements if the one on the right is greater
            }
        }
    }

}

void partition(int *arr, int first, int last, int &partLoc, int &compCount, int &moveCount)
{
    int smaller = first;
    int sorted = first;
    partLoc = first;

    while (sorted < last)
    {
        compCount++;
        if (arr[sorted + 1] > arr[partLoc])
        {
            sorted++; //increment only the sorted pointer as the element is already greater than partition
        }
        else
        {
            //since arr[sorted + 1] < arr[partLoc] swap it with the first element which is bigger than partion
            swap(arr[smaller + 1], arr[sorted + 1]);
            moveCount = moveCount + 3;
            smaller++; //increment both pointers
            sorted++;
        }
    }

    swap(arr[smaller], arr[partLoc]);//put partition in its place
    moveCount = moveCount + 3;
    partLoc = smaller;
}

void quickSort(int *arr, int first, int last, int &compCount, int &moveCount)
{   
    if (first < last) //recursion exit condition
    {
        int partLoc;
        //create the partiton for quicksort
        partition(arr, first, last, partLoc, compCount, moveCount);
        quickSort(arr, first, partLoc - 1, compCount, moveCount); //run quicksort on left side
        quickSort(arr, partLoc + 1, last, compCount, moveCount);   //run quicksort on right side
    }
}

void quickSort(int *arr, int size, int &compCount, int &moveCount)
{
    int first = 0;  //setting the the first componenet of array
    int last = size - 1; //setting the the last componenet of array
    compCount = 0;
    moveCount = 0;
    quickSort(arr, first, last, compCount, moveCount); //the function which calls recursion
}





int widthDig(int num) 
{
	return (int)log10(num) + 1;//finds the size of the digit
}

int getLoc(int num, int loc)
{
    int calc = num;
    int mod = 0;
    int temp = widthDig(num);
    if (loc > (temp - 1))//if the index is greater than the number, return zero
    {
        return 0; 
    } 
    else
    {
        mod = calc % ((int)pow(10, loc));//mod the the non required number and remove it fro the original number
        calc = (calc - mod)/((int)pow(10, loc)); //divide the remaining zeroes
        mod = (int)calc % 10;//just get the last digit
        return mod;
    }
    
    
}

void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount)
{
    int list[last - first + 1]; // new list for the merged list

    int start = first; //store starting of the first original array
    int st = mid;//store starting of the second original array
    mid++;
    for (int i = 0; i < last - start + 1; i++) // run the loop the number of elements we have
    {
        if ((st >= first ) && (last >= mid)) //if both arrays have elements
        {
            compCount++;
            if (arr[first] < arr[mid])//if the selected element of the first array is 
            {                           //greater than selected element of the second array 
                moveCount++;
                list[i] = arr[first];
                first++;
            }
            else
            {
                moveCount++;
                list[i] = arr[mid];
                mid++;
            }
        }
        else if (st >= first)//if second array was finished, finish off the first array
        {
            moveCount++;
            list[i] = arr[first];
            first++;
        }
        else if (last >= mid)//if first array was finished, finish off the second array
        {
            moveCount++;
            list[i] = arr[mid];
            mid++;
        }
    }
    first = start;
    for (int i = 0; i < last - start + 1; i++)//Shift merged array from temp array to original one
    {
        moveCount++;
        arr[first] = list[i];
        first++;
    }
}

void mergeSort(int *arr, int first, int last, int &compCount, int &moveCount)
{   
    if (first < last) //recursion exit condition
    {
        int mid = (last + first)/2; // calculating mid
        mergeSort(arr, first, mid, compCount, moveCount); //run merge sort on left side
        mergeSort(arr, mid + 1, last, compCount, moveCount);   //run merge sort on right side
        merge(arr, first, mid, last, compCount, moveCount); // merge the sorted arrays
    }
}

void mergeSort(int *arr, int size, int &compCount, int &moveCount)
{
    int first = 0;  //setting the the first componenet of array
    int last = size - 1; //setting the the last componenet of array
    compCount = 0;
    moveCount = 0;
    mergeSort(arr, first, last, compCount, moveCount); //the function which calls recursion
}


void radixSort(int *arr, int size)
{
    //get size of biggest int
    int width = 0; //width of the biggest element

    for (int i = 0; i < size; i++)
    {
        int temp = widthDig(arr[i]);
        if (temp > width)//get the highest width
            width = temp;
    }

    int a[10][size];

    for (int i = 0; i < width; i++) //run the loop the maximum width of the elements times so if max 
    {                                    //element is 200 the loop runs 3 times
        int sizes[10];
        for (int l = 0; l < 10; l++)//an array that stores the index at which the next element in that particular
            sizes[l] = 0;           //group shold be stored
        for (int j = 0; j < size; j++)//start the groupings
        {
            int loc = getLoc(arr[j], i);
            a[loc][sizes[loc]] = arr[j];
            sizes[loc]++;//basically put the elemnt in its group according to its number
            //then increase the number for the index of the grouped arrays in the sizes array
        }
        int cntr = 0;
        for (int l = 0; l < 10; l++)
        {
            for (int z = 0; z < sizes[l]; z++)//put all of the grouped elements back in their own array
            {
                arr[cntr] = a[l][z];
                cntr++;
            }
        }
    }

}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        cout << arr[i] << ", ";
    } 
    cout << arr[size - 1] <<  endl;
}

void performanceAnalysis()
{
    double blis[8][3];//get 4 arrays one for each sorting
    double mlis[8][3];//each array has time and compCount and moveCount
    double qlis[8][3];
    double rlis[8];

    

    int cntr = 0;
    double etime;
    int compCount;
    int moveCount;

    clock_t startTime;
    srand(time(0));
    
    for (int j = 2000; j <= 30000; j = j + 4000)
    {
        int blist[j];
        int mlist[j];
        int qlist[j];
        int rlist[j];
        int r;

        for (int i = 0; i < j; i++)
        {
            r = rand() ;
            blist[i] = r;//fill random digits in each of the list
            mlist[i] = r;
            qlist[i] = r;
            rlist[i] = r;
        }
        
        startTime = clock();
        mergeSort(mlist, j, compCount, moveCount);
        etime =  1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        mlis[cntr][0] = etime;
        mlis[cntr][1] = compCount;
        mlis[cntr][2] = moveCount;
        
        startTime = clock();
        quickSort(qlist, j, compCount, moveCount);
        etime =  1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        qlis[cntr][0] = etime;
        qlis[cntr][1] = compCount;
        qlis[cntr][2] = moveCount;
        
        startTime = clock();
        bubbleSort(blist,j, compCount, moveCount);
        etime =  1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        blis[cntr][0] = etime;
        blis[cntr][1] = compCount;
        blis[cntr][2] = moveCount;
        
        startTime = clock();
        radixSort(rlist, j);
        etime =  1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        rlis[cntr] = etime;
 
    
        cntr++;
    }
 
    cout << "-----------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Radix Sort" << endl;
    cout << "Array Size      Time Elapsed" << endl;
    cntr = 0;
    for (int j = 2000; j <= 30000; j = j + 4000)
    {
        cout << j << "          "<< rlis[cntr] << " ms " << endl;
        cntr++;
    }
    cout << "-----------------------------------------------------" << endl;

    cout << "-----------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Bubble Sort" << endl;
    cout << "Array Size      Time Elapsed     compCount     moveCount" << endl;
    cntr = 0;
    for (int j = 2000; j <= 30000; j = j + 4000)
    {
        cout << j << "          "<< blis[cntr][0] << " ms " << "        " << (int)blis[cntr][1] << "        " << (int)blis[cntr][2] << endl;
        cntr++;
    }
    cout << "-----------------------------------------------------" << endl;

    cout << "-----------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Quick Sort" << endl;
    cout << "Array Size      Time Elapsed     compCount     moveCount" << endl;
    cntr = 0;
    for (int j = 2000; j <= 30000; j = j + 4000)
    {
        cout << j << "          "<< qlis[cntr][0] << " ms " << "        " << (int)qlis[cntr][1] << "        " << (int)qlis[cntr][2] << endl;
        cntr++;
    }
    cout << "-----------------------------------------------------" << endl;

    cout << "-----------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Merge Sort" << endl;
    cout << "Array Size      Time Elapsed     compCount     moveCount" << endl;
    cntr = 0;
    for (int j = 2000; j <= 30000; j = j + 4000)
    {
        cout << j << "          "<< mlis[cntr][0] << " ms " << "        " << (int)mlis[cntr][1] << "        " << (int)mlis[cntr][2] << endl;
        cntr++;
    }
    cout << "-----------------------------------------------------" << endl;
        
    
}
