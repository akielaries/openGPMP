/*
 * function implementation of writeToFile that
 * writes our sorted data to a .csv file with the
 * respective sort name
 */
#include <stdio.h>

void writeDataToFile(int rankArray[], unsigned long long int passwordArray[], 
                                                int size,FILE *fileName) {
    // initialize variables
    int index = 0;

    // loop across specified elements
    for(index; index < size; index++) {
        // write data pair to file
        fprintf( fileName, "%d, ", rankArray[index]);
        fprintf( fileName, "%I64llu\n", passwordArray[index]);
    }
    // void, no return
}


