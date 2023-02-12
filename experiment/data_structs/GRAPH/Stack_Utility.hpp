// Inclusion guard
#ifndef STACK_UTILITY_H
#define STACK_UTILITY_H

// Header files
#include <stdio.h>
#include <stdlib.h>

// Data structure
typedef struct StackTypeStruct {
    int value;
    struct StackTypeStruct *nextPtr;
} StackNodeType;

// Constants
//  none

// function declarations
/*
Name: clearStack
Process: clears the stack starting from the top
Function input/parameters: stackTopPtr (pointer to top of stack)
Function output/parameters: none
Function output/returned: NULL
Device input/file: none
Device output/monitor: none
Dependencies: free
*/
StackNodeType *clearStack(StackNodeType *stackTopPtr);

/*
Name: createStackNode
Process: Creates a node in memory, and sets the data in the node
Function input/parameters: inData, the value to be put in the node (int)
Function output/parameters: none
Function output/returned: pointer to created node
Device input/file: none
Device output/monitor: none
Dependencies: malloc, sizeof
*/
StackNodeType *createStackNode(int inData);

/*
Name: displayStack
Process: outputs the stack to the console,
          with each value in the stack on a new line. Also
          indicates where the top and bottom of the stack are.
          If the stack is empty, a message indicating this is displayed
Function input/parameters: stackTopPtr, pointer to top of stack
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: printf
*/
void displayStack(StackNodeType *stackTopPtr);

/*
Name: pop
Process: removes a node from the stack,
         displays a message indicating what data was removed,
         if the stack is empty, a message indicating this is displayed
         returns the updated top of stack ptr
Function input/parameters: stackTopPtr, pointer to top of stack
Function output/parameters: none
Function output/returned: updated stackTopPtr
Device input/file: none
Device output/monitor: none
Dependencies: printf
*/
StackNodeType *pop(StackNodeType *stackTopPtr);

/*
Name: push
Process: Adds a node to the stack.
         The top of the stack is at the front of the list,
         and the bottom of the stack is the last node in the list:

         4 -> 27 -> 8 -> 6 -|
         top of stack: 4
         bottom of stack: 6

Function input/parameters: stackTopPtr, pointer to top of stack
Function output/parameters: none
Function output/returned: updated stackTopPtr
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
StackNodeType *push(StackNodeType *stackTopPtr, int inData);

// provided
StackNodeType *createStack(int totalNodes);

#endif