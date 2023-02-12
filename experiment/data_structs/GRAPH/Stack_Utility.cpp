#include "Stack_Utility.h"

// function implementations
StackNodeType *clearStack(StackNodeType *stackTopPtr) {
    // initialize variables
    StackNodeType *tempPtr = NULL;

    // check for stack exists
    if (stackTopPtr != NULL) {
        // loop while nodes are in list
        while (stackTopPtr != NULL) {
            // point at current top node
            tempPtr = stackTopPtr;

            // update top of stack
            stackTopPtr = stackTopPtr->nextPtr;

            // free old top node
            free(tempPtr);
        }
    }

    return NULL;
}

StackNodeType *createStackNode(int inData) {
    // initialize variables
    StackNodeType *newStackNodePtr = NULL;

    // create node
    newStackNodePtr = (StackNodeType *)malloc(sizeof(StackNodeType));

    // put data into node
    newStackNodePtr->value = inData;
    newStackNodePtr->nextPtr = NULL;

    return newStackNodePtr;
}

void displayStack(StackNodeType *stackTopPtr) {
    // initialize variables
    StackNodeType *currentNodePtr = stackTopPtr;

    // check for stack exists
    if (stackTopPtr != NULL) {
        printf("\nTop of stack\n");

        while (currentNodePtr != NULL) {
            printf("    %d\n", currentNodePtr->value);

            currentNodePtr = currentNodePtr->nextPtr;
        }

        printf("Bottom of stack\n");
    }
    // otherwise, assume stack is empty
    else {
        // display empty stack message
        printf("\nStack is empty.\n");
    }
}

StackNodeType *pop(StackNodeType *stackTopPtr) {
    // initialize variables
    // int popVal;
    StackNodeType *tempPtr;

    // check for stack exists
    if (stackTopPtr != NULL) {
        // preserve removed value
        // popVal = stackTopPtr->value;

        // point temp ptr so node is not lost
        tempPtr = stackTopPtr;

        // reassign top of stack
        stackTopPtr = stackTopPtr->nextPtr;

        // free old stack top
        free(tempPtr);

        // display removal message to console
        // printf("\nRemoved from top of stack: %d\n", popVal);

    }
    // otherwise, stack is empty
    else {
        // display empty stack message to console
        printf("\nStack is empty\n");
    }

    return stackTopPtr;
}

StackNodeType *push(StackNodeType *stackTopPtr, int inData) {
    // initialize variables
    StackNodeType *newStackNodePtr = NULL;

    // create node
    newStackNodePtr = createStackNode(inData);

    // check for existing nodes in stack
    if (stackTopPtr != NULL) {
        // put new node on top of stack
        newStackNodePtr->nextPtr = stackTopPtr;

        // reassign top of stack ptr
        stackTopPtr = newStackNodePtr;
    }
    // otherwise, assume stack is empty
    else {
        // assign top to new node
        stackTopPtr = newStackNodePtr;
    }

    // return updated ptr to top of stack node
    return stackTopPtr;
}
