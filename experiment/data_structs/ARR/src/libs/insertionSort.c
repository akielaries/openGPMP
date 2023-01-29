/*
 *  implementation of insertionSort.h
 */

// header files
#include <stdio.h>          // in/out
#include <time.h>           // measuring run time of our algos with this
#include <string.h>

/*
Name: runInsertionSort
Process: sorts data with insertion sort algorithm
Function input/parameters: arrays with data to be sorted, size of array
Function output/parameters: sorted arrays
Function output/returned: length of time for sort (provided)
Device input/file: none
Device output/monitor: none
Dependencies: clock, compareData
*/

double runInsertionSort(int rankArray[], unsigned long long int passwordArray[],
                                                                    int size) {
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    int list, search, tempRank = 1;
    unsigned long long int tempPass = 1;

    startTime = clock();

    // loop while listIndex is smaller than size
    while (list < size) {
        // set copy of original data    
        tempRank = rankArray[list];
        tempPass = passwordArray[list];

        // set search index
        search = list - 1;

        // loop while search index > 0 AND element below search index is smaller than temp data
        while (search >= 0 && rankArray[search] > tempRank) {
            // copy element below into current search index
            rankArray[search + 1] = rankArray[search];
            passwordArray[search + 1] = passwordArray[search];
            // decrement search index
            search--;
        }

        // insert temp at search index 
        rankArray[search + 1] = tempRank;
        passwordArray[search + 1] = tempPass;

        // increment list index
        list++;
    }

    // end time
    endTime = clock();

    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return totalTime;
}


