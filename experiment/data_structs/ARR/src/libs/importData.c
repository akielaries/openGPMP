/*
 * function implementation of writeToFile which will write
 * out sorted data to .csv files of respective sort names
 */
#include <stdio.h>              // file io
#include <string.h>
#include "../libs/constants.h"          // constants


void importData(int rankArray[], unsigned long long int passwordArray[]) {
    // initialize variables
    FILE *inputFile;
    int rankIndex = 0, passIndex = 0;
    int rank, strLen;
    unsigned long long int result = 0;
    char password[40];
    char commaCapture;
    int index;

    // open file from data folder
    inputFile = fopen("../data/UNSORTED_DATA.csv", "r");

    for(rankIndex = 0, passIndex = 0; rankIndex < MAX_CAPACITY;
                                                       rankIndex++, passIndex++) {
        result = 0;

        // read in first number
        fscanf( inputFile, "%d", &rank );
        // capture comma
        fscanf( inputFile, "%c", &commaCapture );
        // read in second number
        fscanf( inputFile, "%s", password );

        strLen = strlen(password);

        for(index = 0; index < strLen; index++) {
           result = (result * 10 ) + (password[index] - '0');
        }

        // put data into array, cast as integer
        rankArray[rankIndex] = rank;
        passwordArray[passIndex] = result;
    }

    // close file
    fclose(inputFile);

    // void, no return
}

