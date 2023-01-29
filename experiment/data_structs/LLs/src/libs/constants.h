/*
 *  constants used in program
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdio.h>
#include <stdlib.h> // malloc/free
#include <time.h>
#include <string.h>


static const int MAX_CAPACITY = 150000;
// Data structures
typedef struct PasswordTypeStruct
   {

    int rank;
    unsigned long long int  password;
    struct PasswordTypeStruct *nextPtr;
    struct PasswordTypeStruct *prevPtr;

   } PasswordType;


#endif

