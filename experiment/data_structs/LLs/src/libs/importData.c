/*
 * function implementation of writeToFile which will write
 * out sorted data to .csv files of respective sort names
 */
#include <stdio.h>              // file io
#include <string.h>
#include <stdlib.h>
#include "../libs/constants.h"          // constants

PasswordType *importData(int size) {
    // initialize variables
    FILE *inputFile;
    int index, strIndex, rank, strLen;
    unsigned long long int result = 0;
    char comma, password[40];
    PasswordType *previousNodePtr, *nextNodePtr, *headPtr = NULL;

    // prime loop
    previousNodePtr = (PasswordType *)malloc(sizeof(PasswordType));

    // open file
    inputFile = fopen("HW_1_DATA_UNSORTED.csv", "r");


    // read in first number
    fscanf( inputFile, "%d", &rank );

    // capture comma
    fscanf( inputFile, "%c", &comma );

    // read in second number
    fscanf( inputFile, "%s", password );

    strLen = strlen(password);

    for(strIndex = 0; strIndex < strLen; strIndex++) {
       result = (result * 10 ) + (password[strIndex] - '0');
    }

    // put data into node
    previousNodePtr->rank = rank;
    previousNodePtr->password = result;
    previousNodePtr->nextPtr = NULL;
    previousNodePtr->prevPtr = NULL;

    // set headPtr
    headPtr = previousNodePtr;

    // loop to import up to size
    for(index = 1; index < size; index++) {
        result = 0;

        // create next node
        nextNodePtr = (PasswordType *)malloc(sizeof(PasswordType));

        // assign next ptr and previous node ptr
        previousNodePtr->nextPtr = nextNodePtr;
        nextNodePtr->prevPtr = previousNodePtr;

        // read in first number
        fscanf( inputFile, "%d", &rank );

        // capture comma
        fscanf( inputFile, "%c", &comma );

        // read in second number
        fscanf( inputFile, "%s", password );
        strLen = strlen(password);

        for(strIndex = 0; strIndex < strLen; strIndex++) {
           result = (result * 10 ) + (password[strIndex] - '0');
        }

       // put data into node
       nextNodePtr->rank = rank;
       nextNodePtr->password = result;
       nextNodePtr->nextPtr = NULL;
       previousNodePtr = nextNodePtr;
    }
    fclose(inputFile);
    // return head pointer
    return headPtr;
}



