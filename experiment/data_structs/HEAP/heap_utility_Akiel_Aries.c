/*
 *  function implementations for Max heap
 */

#include <stdio.h>
#include <stdlib.h>

/*
Name: swap
Process: swaps the data in the array at the two indicies passed in
Function input/parameters: firstIndex, otherIndex, heapArray
Function output/parameters: updated heapArray
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
  void swap(int firstIndex, int otherIndex, int *heapArray)
{
    int temp = heapArray[firstIndex];
    heapArray[firstIndex] = heapArray[otherIndex];
    heapArray[otherIndex] = temp;
    // void, no return
}

/*
Name: bubbleUp
Process: recursively traverses heap to place data into correct location
Function input/parameters: currentIndex (index of data to be placed), heapArray
Function output/parameters: updated heapArray
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: bubbleUp, swap, printf
*/
void bubbleUp(int currentIndex, int *heapArray)
{
    // initialize variables
    int parentIndex, bubbleVal = heapArray[currentIndex];
    // check for current index is greater than 0
    if (currentIndex > 0)
    {
        // calculate parent index of the current index
        parentIndex = (currentIndex - 1) / 2;
        // check to see if the data at current index larger than parent
        if (bubbleVal > heapArray[parentIndex])
        {
            printf("    --Swapping %d with it's parent %d\n", bubbleVal, heapArray[parentIndex]);
            printf("\n");
            // call swap
            swap(currentIndex, parentIndex, heapArray);
            // call bubbleUp again with the parent index
            bubbleUp(parentIndex, heapArray);
        }
    }
    // void, no return
}

/*
Name: findMax
Process: returns the maximum value in the heap
Function input/parameters: heapArray
Function output/parameters: none
Function output/returned: largest value in heap
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int findMax(int *heapArray)
{
    // return first element in array
    return heapArray[0];
}

/*
Name: findMin
Process: searches for, and returns the minimum value in the heap
Function input/parameters: heapArray, size
Function output/parameters: none
Function output/returned: smallest value in heap
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
int findMin(int *heapArray, int size)
{
    // initialize variables
    int iter = 0;
    int minVal = heapArray[iter];
    // iterate thru array
    for (iter = 1; iter < size; ++iter)
    {
        // check to see if element array is less than smallest val
        if (heapArray[iter] < minVal)
            minVal = heapArray[iter];
    }
    return minVal;
}
/*
Name: insertInHeap
Process: Adds a piece of data to the heap, and bubbles it up to the correct location. Insertion message is
displayed to the console and the updated heap size is returned to the calling function
Function input/parameters: insertion data, size, heapArray
Function output/parameters: updated heapArray
Function output/returned: updated size of the heap
Device input/file: none
Device output/monitor: none
Dependencies: bubbleUp, printf
*/
int insertInHeap(int inData, int size, int *heapArray)
{
    printf("Inserting %d\n", inData);
    printf("\n");
    // add new data to the array
    heapArray[size] = inData;
    // update size of the array
    size++;
    // call bubbleUp() to find the correct location for new data
    bubbleUp(size - 1, heapArray);
    // return updated size
    return size;
}

/*
Name: trickleDown
Process: recursively searches heap to place data at currentIndex at the correct location
Function input/parameters: currentIndex, size, heapArray
Function output/parameters: updated heapArray
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: trickleDown, printf, swap
*/
void trickleDown(int currentIndex, int size, int *heapArray)
{
    // initialize variables
    int leftChildIndex, rightChildIndex, swapIndex;
    int leftChildData, rightChildData;
    int parentData = heapArray[currentIndex];
    // calculate child indices
    leftChildIndex = (currentIndex * 2) + 1;
    rightChildIndex = (currentIndex * 2) + 2;
    leftChildData = heapArray[leftChildIndex];

    // check for both child indices are less than array size
    if (leftChildIndex < size && rightChildIndex < size)
    {
        // set child data
        rightChildData = heapArray[rightChildIndex];
        leftChildData = heapArray[rightChildIndex];

        // check for one of the children to be larger than the parent
        if (leftChildData > parentData || rightChildData > parentData)
          {
            // find larger child
            if (heapArray[leftChildIndex] > heapArray[rightChildIndex])
            {
                swapIndex = leftChildIndex;
                // swap larger child with the parent
            }
            else
            {
                swapIndex = rightChildIndex;
            }

            printf("    --Swapping %d with it's child %d\n",
                heapArray[currentIndex], heapArray[swapIndex]);
            printf("\n");

            swap(swapIndex, currentIndex, heapArray);
            // call trickleDown again with the child index
            return trickleDown(swapIndex, size, heapArray);
        }
    }
    // check for only left child index less than the array size
    else if (leftChildIndex < size)
    {
        // set left child data
        leftChildData = heapArray[leftChildIndex];
        // check for left to be larger than parent
        if (leftChildData > parentData)
        {
            printf("    --Swapping %d with it's child %d\n",
                heapArray[currentIndex], heapArray[leftChildIndex]);
            // swap left with parent
            swap(leftChildIndex, currentIndex, heapArray);
            // call function recursively with left child index
            return trickleDown(leftChildIndex, size, heapArray);
        }
    }
    // void, no return
}

/*
Name: removeFromHeap
Process: removes a piece of data from the heap, and resolves the heap
Function input/parameters: size, heapArray
Function output/parameters: updated heapArray
Function output/returned: updated heap size
Device input/file: none
Device output/monitor: none
Dependencies: trickleDown, printf
*/
int removeFromHeap(int size, int *heapArray)
{
    // initialize variables
    int lastElement;
    lastElement = heapArray[0];

    printf("Removing %d\n", lastElement);
    printf("\n");

    // move last element in array to the first element
    heapArray[0] = heapArray[size - 1];
    // update size of the heap
    size--;
    // call trickledown to find the correct location for the new first element
    trickleDown(0, size, heapArray);
    // return updated size
    return size;
}

// provided function
int *createHeap(int size)
{
    // initialize variables
    int capacity, currentSize = 0, num;
    char comma;
    int *heapArrayPtr = NULL;
    FILE *inputFilePtr = NULL;

    // calculate capacity 
    capacity = 1.5 * size;

    // allocate memory for heap (create array with 50% more room than will be used)
    heapArrayPtr = (int *)malloc(capacity * sizeof(int));

    // open data file to read in data
    inputFilePtr = fopen("HeapData.csv", "r");

    // loop to read data into heap
    while(currentSize < size)
    {
        // read in data
        fscanf(inputFilePtr, "%d", &num);
        fscanf(inputFilePtr, "%c", &comma);

        // call to place it in heap
       currentSize = insertInHeap(num, currentSize, heapArrayPtr);

    }

    return heapArrayPtr;
}

void writeHeapToFile(int size, FILE *outputFilePtr, int *heapArray)
{
    // initialize variables
    int index;

    for(index = 0; index < size; index++)
    {
        fprintf(outputFilePtr, "%d,\n", heapArray[index]);
    }

    // void, no return
}

