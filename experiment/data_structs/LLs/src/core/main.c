// header files
//include <stdio.h>
//#include <stdlib.h> // malloc/free
//#include <time.h>
//#include <string.h>
#include "../libs/constants.h"          // constants
#include "../libs/clearLinkedList.h"     // clear the linked list
#include "../libs/writeToFile.h"        // write sorted data to .csv file
#include "../libs/importData.h"         // import data from unsorted .csv file
#include "../libs/bubbleSort.h"         // bubble sort algorithm
#include "../libs/insertionSort.h"      // insertion sort algorithm
#include "../libs/compare.h"            // compare data lib
#include "../libs/swap.h"               /* swap data lib. C does
                                         * not have such lib so made 
                                         * my own for this case
                                        */


//eafunction declarations
    // for you to write
//double runBubbleSort(PasswordType *headPtr);
//double runInsertionSort(PasswordType *headPtr);
//int compareData(int dataOne, int dataTwo);
//void swapData(PasswordType *dataOne, PasswordType *dataTwo);

    // provided
//PasswordType *clearLinkedList(PasswordType *wkgPtr);
//PasswordType *importData(int size); // provided

//void writeDataToFile(PasswordType *headPtr, FILE *fileName);  // provided

// main driver
int main()
{
    // initialize variables
    PasswordType *headPtr = NULL;
    FILE *bubbleSortOutputFile, *insertionSortOutputFile;
    int size;
    double runTime;
   
    // prompt for size
    printf("Enter the number of values to be sorted: ");
	scanf("%d", &size);
    
    // check for data to sort
    if(size > 0 && size <= MAX_CAPACITY)
    {
        // create linked list from input file
            // function: importData
        headPtr = importData(size);
        

        // check for headptr not null
        if(headPtr != NULL)
        {         
            // open output file
            bubbleSortOutputFile = fopen("bubbleSortLL.csv", "w+");

            // write bubble sort title to file
            fprintf(bubbleSortOutputFile, "Linked List Bubble Sort:\n");
            
            // sort data using bubble sort algorithm
                // function: runBubbleSort
            runTime = runBubbleSort(headPtr);
            
            // write elapsed time to file
           fprintf(bubbleSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);
         
            // write linked list data to file
            writeDataToFile(headPtr, bubbleSortOutputFile);
            
            // close file
            fclose(bubbleSortOutputFile);
            
            // clear sorted linked list, reset cpdHeadPtr
                // function: clearLinkedList
            headPtr = clearLinkedList(headPtr);
        }
        
        // otherwise, list is null
        else
        {
            // display error message to console
            printf("\nError: No data found. \n");
        }
            
        // read in data again for next sort
            // function: import
         headPtr = importData(size);
        
        if(headPtr != NULL)
        {
            // open output file
            insertionSortOutputFile = fopen("insertionSortLL.csv", "w+");
            
            // write title to file
            fprintf(insertionSortOutputFile, "Linked List Insertion Sort:\n");

            // sort data using insertion sort algorithm  
                // function: runInsertionSort
            runTime = runInsertionSort(headPtr);

           fprintf(insertionSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);            

            // write linked list data to file
            writeDataToFile(headPtr, insertionSortOutputFile);
            
            // close output file  
            fclose(insertionSortOutputFile);
            
            // clear all linked lists (original and copied) 
                // function: clearLinkedList  
            headPtr = clearLinkedList(headPtr);

                    
        }
        
        // otherwise, list is null
        else
        {
            // display error message to console
            printf("\nError: No data found. \n");
        }
        
        // display program success to console.
         printf("\nData written to bubbleSortLL.csv and insertionSortLL.csv\n");
    }
    
    // Otherwise, size is not a valid input
    else
    {
        printf("Incorrect input.\n");
    }
    
    printf("\nEnd program\n");
    
    // return function success
    return 0;
}

