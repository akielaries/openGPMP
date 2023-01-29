// header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap_utility_Akiel_Aries.h"

// constants
const int MAX_CAPACITY = 300000;

/*
// function declarations
  // for students to write
void bubbleUp(int currentIndex, int *heapArray);
int findMax(int *heapArray);
int findMin(int *heapArray, int size);
int insertInHeap(int inData, int size, int *heapArray);
void swap(int firstIndex, int otherIndex, int *heapArray);
int removeFromHeap(int size, int *heapArray);
void trickleDown(int currentIndex, int size, int *heapArray);

  // provided
int *createHeap(int size);
void writeHeapToFile(int size, FILE *outputFilePtr, int *heapArray);
*/

// main driver
int main()
{
    // initialize variables
    int maxData, maxVal, minVal, index;
    int *heapPtr = NULL;
    clock_t startTime, endTime;
    double runTime;
    FILE *outputFilePtr;

    // prompt for number of data to include in heap
    printf("Enter the number of values to put in the heap: ");
    scanf("%d", &maxData);

    // check for acceptable size input
    if(maxData >= 1 && maxData <= MAX_CAPACITY)
    {

        // build the heap
        heapPtr = createHeap(maxData);



        // check for successful heap creation
        if(heapPtr != NULL)
        {

            // open output file
            outputFilePtr = fopen("HeapOutput.csv", "w+");

          // do some stuff with the heap

            // start the clock
            startTime = clock();

            // find the max value
            maxVal = findMax(heapPtr);

            // stop the clock
            endTime = clock();

            // calculate difference
            runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

            fprintf(outputFilePtr,
                      "It took %f seconds to find the max value %d\n",
                                                               runTime, maxVal);

            // start the clock
            startTime = clock();

            // find the min value
            minVal = findMin(heapPtr, maxData);

            // stop the clock
            endTime = clock();

            // calculate difference
            runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

            fprintf(outputFilePtr,
                  "It took %f seconds to find the min value %d\n",
                                                               runTime, minVal);


                // remove some values from the heap
                for(index = 0; index < maxData/3; index++)
                {
                    maxData = removeFromHeap(maxData, heapPtr);
                }

               fprintf(outputFilePtr,"Heap array after removing some values\n");

                // create ouput file
                writeHeapToFile(maxData, outputFilePtr, heapPtr);

                // free the heap
                free(heapPtr);

                // display output file to console
                printf("\nThe heap was written to HeapOuput.csv\n");
        }

    }

    // display program end
    printf("\nEnd program\n");

    // return function success
    return 0;
}

