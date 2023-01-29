/*
 * implementation of clearLinkedList() method that will
 * be freeing the wkgPtr of the list (head)
 */

#include "constants.h"
PasswordType *clearLinkedList(PasswordType *wkgPtr)
{
    PasswordType *ptr = wkgPtr;

    while( ptr != NULL )
    {
        wkgPtr = wkgPtr->nextPtr;

        free(ptr);

        ptr = wkgPtr;
    }

    return NULL;

}

