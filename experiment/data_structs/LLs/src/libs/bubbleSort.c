/*
Name: runBubbleSort
Process: sorts the data using the bubble sort algorithm
Function input/parameters: headPtr of list to be sorted
Function output/parameters: none
Function output/returned: updated headPtr of sorted list
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
#include "constants.h"
#include "compare.h"

double runBubbleSort(PasswordType *headPtr)
{
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    int swapped;
    // temp var for setting ptrs that need swapping equal to
    int tempRank = 0;
    unsigned long long int tempPass = 0;
    PasswordType *startPtr;
    PasswordType *endPtr = NULL;

    startTime = clock();

    do
    {
        // swapped variable for before/after sort is ran
        swapped = 0;
        // start pointer
        startPtr = headPtr;

        // while nextptr is not end
        while (startPtr->nextPtr != endPtr)
        {
            // call compareData, comparing start and next
            if (compareData(startPtr->rank,
                        startPtr->nextPtr->rank) == 1)
            {
                // swap start ptr and next if startPtr > startPtr next
                // using temp variable, swap start and next
                tempRank = startPtr->rank;
                startPtr->rank = startPtr->nextPtr->rank;
                startPtr->nextPtr->rank = tempRank;

                // same logic as above, swapping rank assignments
                // the password values
                tempPass = startPtr->password;
                startPtr->password = startPtr->nextPtr->password;
                startPtr->nextPtr->password = tempPass;
                // if condition hit swapped 
                swapped = 1;

            }
            // set start = to next 
            startPtr = startPtr->nextPtr;

        }
        // set end = to start to begin process over
        endPtr = startPtr;

    }
    // continue algorithm until 
    while (swapped);

    // end time
    endTime = clock();

    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return totalTime;

}

