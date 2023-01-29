/*
Name: runInsertionSort
Process: sorts the data using the insertion sort algorithm
Function input/parameters: headPtr of list to be sorted
Function output/parameters: none
Function output/returned: updated headPtr of sorted list
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
#include "constants.h"
#include "compare.h"

double runInsertionSort(PasswordType *headPtr)
{
    // initialize variables
    clock_t startTime, endTime;
    double totalTime;
    // temp var for setting ptrs that need swapping equal to
    int tempRank = 1;
    unsigned long long int tempPass = 1;
    PasswordType *startPtr;
    PasswordType *endPtr = NULL;
    startPtr = headPtr;

    startTime = clock();

    // while startPtr is not empty
    while (startPtr != NULL)
    {
        // get next node
        // setting endPtr = the start next 
        endPtr = startPtr->nextPtr;

        // update node val when consecutive nodes not sorted
        // call compareData for end and previous
        while (endPtr != NULL
                && endPtr->prevPtr != NULL && (
                compareData(endPtr->rank, endPtr->prevPtr->rank) == -1))
        {
            // swap nodes
            tempRank = endPtr->rank;
            endPtr->rank = endPtr->prevPtr->rank;
            endPtr->prevPtr->rank = tempRank;

            // apply same logic as above for swapping passwords 
            tempPass = endPtr->password;
            endPtr->password = endPtr->prevPtr->password;
            endPtr->prevPtr->password = tempPass;

            // visit prev node
            endPtr = endPtr->prevPtr;
        }
        // set start to next
        startPtr = startPtr->nextPtr;
    }
    // end time
    endTime = clock();

    // calculate difference to get total
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    return totalTime;

}

