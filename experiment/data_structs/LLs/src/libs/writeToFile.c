/*
 * function implementation of writeToFile that
 * writes our sorted data to a .csv file with the
 * respective sort name
 */
#include <stdio.h>
#include "constants.h"

void writeDataToFile(PasswordType *headPtr, FILE *fileName)
{
    // initialize variables
    PasswordType *wkgPtr = headPtr;
    // loop across specified elements
    while(wkgPtr != NULL)
    {
        // write data pair to file
        fprintf( fileName, "%d, %I64llu\n", wkgPtr->rank, wkgPtr->password);
        wkgPtr = wkgPtr->nextPtr;
    }
}

