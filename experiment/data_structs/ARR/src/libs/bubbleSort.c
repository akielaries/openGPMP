/*
 * implementation of bubbleSort.h file
 */

// header files
#include <stdio.h>          // in/out
#include <time.h>           // measuring run time of our algos with this
#include <string.h>
#include "swap.h"

/*
Name: runBubbleSort
Process: sorts data with bubble sort algorithm
Function input/parameters: array for rank, array for password,
                                 and size (number to be sorted)
Function output/parameters: sorted arrays
Function output/returned: length of time of sort (provided)
Device input/file: none
Device output/monitor: none
Dependencies: clock, compareData, swap
*/

double runBubbleSort(int rankArray[], unsigned long long int passwordArray[],
                                                                    int size) {
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    int list, search = 0;
    unsigned long long int tempPass = 0;

    startTime = clock();

    // outer loop: n-1 elements
    for (list = 0; list < (size - 1); list++) {
        // inner loop: n-1 elements
        for (search = 0; search < size - list - 1; search++) {
            // check to see if next element is larger than current
            if (rankArray[search] > rankArray[search + 1]) {
                // swap current and next element 
                swap(&rankArray[search], &rankArray[search + 1]);
                // assign int rank vals to ulli pass w/o writing new
                // fun
                tempPass = passwordArray[search];
                passwordArray[search] = passwordArray[search + 1];
                passwordArray[search + 1] = tempPass;
            }
        }
    }

    // end time
    endTime = clock();

    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return totalTime;
}
/*
Name: runRecursiveBubbleSort
Process: sorts data with bubble sort algorithm like above but
instead recursively. Set base case, iterate our array and call
swap() function then call again!
Function input/parameters: array for rank, array for password,
                                 and size (number to be sorted)
Function output/parameters: sorted arrays
Function output/returned: length of time of sort (provided)
Device input/file: none
Device output/monitor: none
Dependencies: clock, compareData, swap

double runRecursiveBubbleSort(int rankArray[], unsigned long long int passwordArray[],
                                                                            int size) {
    // intialize varables
    clock_t startTime, endTime;
    double totalTime;
    int list = 0;
    unsigned long long int tempPass = 0;
    startTime = clock();
    // base case for recursive sort
    if (size == 1){
        return 1;
    }
    // pass thru sort once, then move largest element to end
    for (list = 0; list < size - 1; list++) {
        // if first element is greater than next swap using swap() fun
        if (rankArray[list] > rankArray[list + 1]){
            swap(&rankArray[list], &rankArray[list + 1]);
            // assign int rank assingment to llu pass data
            tempPass = passwordArray[list];
            passwordArray[list] = passwordArray[list + 1];
            passwordArray[list + 1] = tempPass;
        }
    }
    runRecursiveBubbleSort(rankArray, passwordArray, size - 1);
    
    // end time
    endTime = clock();

    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return totalTime;
}
*/






