/*  C Program displaying knowledge of different sorting algorithms.
 *  Goal is to read in csv file of unsorted data (300,000 data pairs)
 *  containing a key and a value. In this case password rank and its 
 *  corresponding password. We are to sort the rankArray of ints
 *  and assign the iterated positions to passwordArray of 
 *  unsigned long long ints. Using bubble and insertion sort we sort the
 *  values and export them into files of their respective names.
 *  
 *  Author: Akiel Aries
 */


// header files
#include <stdio.h>              // file io
#include <time.h>               // measuring time
#include <string.h>
#include "../libs/constants.h"          // constants
#include "../libs/writeToFile.h"        // write sorted data to .csv file
#include "../libs/importData.h"         // import data from unsorted .csv file
#include "../libs/bubbleSort.h"         // bubble sort algorithm
#include "../libs/insertionSort.h"      // insertion sort algorithm
#include "../libs/selectionSort.h"      // selection sort algorithm
#include "../libs/compare.h"            // compare data lib
#include "../libs/swap.h"               /* swap data lib. C does
                                         * not have such lib so made 
                                         * my own for this case
                                        */
// function implementations
void importData(int rankArray[], unsigned long long int passwordArray[]);

// main driver
int main() {
    // initialize variables
    int rankArray[MAX_CAPACITY];
    unsigned long long int passwordArray[MAX_CAPACITY];
    int size;
    double runTime;
    FILE *bubbleSortOutputFile, *insertionSortOutputFile, 
         *selectionSortOutputFile;    
    // import data
    //importData();
    // prompt for size
    printf("Enter the number of values to be sorted: ");
	scanf("%d", &size);
    
    // check for data in array
    if(size > 0) {
        // FOR BUBBLE SORT; read in csv
        importData(rankArray, passwordArray);      
        // open bubble sort output file
        bubbleSortOutputFile = fopen("../reports/bubbleSort.csv", "w+");
        // write bubble sort title to output file
        fprintf(bubbleSortOutputFile, "Array Bubble Sort:\n");
        // run bubble sort
            // function: runBubbleSort()
        runTime = runBubbleSort(rankArray, passwordArray, size);
        // write elapsed time to file
        fprintf(bubbleSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);
        // write bubble-sorted data from array to output file
        writeDataToFile(rankArray, passwordArray, size, bubbleSortOutputFile);
        // close bubble sort file
        fclose(bubbleSortOutputFile);

        // FOR RECURSIVE BUBBLE SORT
        //importData(rankArray, passwordArray);
        //recursiveBubbleSortOutputFile = fopen("../reports/recursiveBubbleSort.csv", "w+");
        //fprintf(bubbleSortOutputFile, "Array Recursive Bubble Sort:\n");
        //runTime = runRecursiveBubbleSort(rankArray, passwordArray, size);
        //fprintf(recursiveBubbleSortOutputFile, 
        //            "It took %f seconds to sort %d elements.\n", runTime, size);
        //writeDataToFile(rankArray, passwordArray, size, recursiveBubbleSortOutputFile);
        //fclose(recursiveBubbleSortOutputFile);
        // FOR SELECTION SORT; read in csv
        importData(rankArray, passwordArray);
        selectionSortOutputFile = fopen("../reports/selectionSort.csv", "w+");
        fprintf(selectionSortOutputFile, "Array Selection Sort:\n");
        runTime = runSelectionSort(rankArray, passwordArray, size);
        fprintf(selectionSortOutputFile,
                    "It took %f seconds to sort %d elements. \n", runTime, size);
        writeDataToFile(rankArray, passwordArray, size, selectionSortOutputFile);
        fclose(selectionSortOutputFile);

        // FOR INSERTION SORT; overwrite array for next sort
        importData(rankArray, passwordArray);
        insertionSortOutputFile = fopen("../reports/insertionSort.csv", "w+");
        fprintf(insertionSortOutputFile, "Array Insertion Sort:\n");
        runTime = runInsertionSort(rankArray, passwordArray, size);
        fprintf(bubbleSortOutputFile,
                    "It took %f seconds to sort %d elements.\n", runTime, size);
        writeDataToFile(rankArray, passwordArray, size, insertionSortOutputFile);
        fclose(insertionSortOutputFile);
        
        // display success message to screen
        printf("\nSorted data written to bubbleSort.csv, recursiveBubbleSort.csv, selectionSort.csv, insertionSort.csv, & mergeSort.csv");
    }
    
    // otherwise, data was not in array
    else {
        printf("\n\nError: no data found\n");
    }
    
    // write data to file
    //writeDataToFile(int rankArray[], unsigned long long int passwordArray[]);
    // display function success
    printf("\n\nProgram End\n");
    
    // return function success
    return 0;
}
