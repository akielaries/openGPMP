#ifndef QUEUE_UTILITY_H
#define QUEUE_UTILITY_H

// Header files
#include <stdio.h>
#include <stdlib.h>

// data structure
typedef struct queueStruct
   {
    int *queueArrayPtr;

    int size, capacity;
   } QueueType;

/*
Name: dequeue
Process:  Dequeues the value by moving every element up one spot. The dequeued value is returned.
         If the queue is empty, a message is displayed to the console indicating this.
Function input/parameters: queueStructPtr (struct with array pointer, size and capacity variables)
Function output/parameters: updated queue struct
Function output/returned: dequeued value
Device input/file: none
Device output/monitor: none
Dependencies: printf, stepForwardInQueue
*/
int dequeue(QueueType *queueStructPtr);

/*
Name: enqueue
Process: Adds the value passed in to the queue.
Function input/parameters: queueStructPtr (struct with array, size and capacity variables)
                           inData, data that should be added to the queue
Function output/parameters: updated queue struct
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: printf
*/
void enqueue(QueueType *queueStructPtr, int inData);

/*
Name: initializeQueue
Process: allocates memory for the queue (array),
         initializes the size and capacity values for
         the empty array.
Function input/parameters: amount of data queue can hold (capacity),
                           queueStructPtr (struct with array, size and capacity variables)
Function output/parameters: initialized queue data
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: malloc, size of
*/
void initializeQueue(QueueType *queueStructPtr, int capacity);

/*
Name: stepForwardInQueue
Process: Shifts the data at each element up one index. The data at index 0 is overwritten,
         the rest of the queue is intact.
         
         ex. 3, 7, 9, 1 ---> 7, 9, 1
Function input/parameters: queueStructPtr (struct with array, size and capacity variables)
Function output/parameters: updated queue struct
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
void stepForwardInQueue(QueueType *queueStructPtr);

// provided
void writeQueueToOutputFile(QueueType *queueStructPtr);



#endif