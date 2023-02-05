#include "Queue_Utility.h"

int dequeue(QueueType *queueStructPtr) {
    int dequeuedVal = 0;

    if (queueStructPtr->size > 0) {
        // display dequeueing message
        // printf("\nDequeueing %d\n", queueStructPtr->queueArrayPtr[0]);

        dequeuedVal = queueStructPtr->queueArrayPtr[0];

        stepForwardInQueue(queueStructPtr);

    } else {
        printf("\nQueue is empty\n");
    }

    return dequeuedVal;

    // void, no return
}
void enqueue(QueueType *queueStructPtr, int inData) {
    // display queueing statement
    // printf("\nEnqueueing %d\n", inData);

    // put the data into the queue
    queueStructPtr->queueArrayPtr[queueStructPtr->size] = inData;

    // increment size
    queueStructPtr->size++;

    // void, no return
}

void initializeQueue(QueueType *queueStructPtr, int capacity) {
    // initialize variables

    queueStructPtr->queueArrayPtr = (int *)malloc(capacity * sizeof(int));

    queueStructPtr->capacity = capacity;

    queueStructPtr->size = 0;

    // no return
}
void stepForwardInQueue(QueueType *queueStructPtr) {
    // initialize variables
    int index;

    for (index = 0; index < queueStructPtr->size - 1; index++) {
        queueStructPtr->queueArrayPtr[index] =
            queueStructPtr->queueArrayPtr[index + 1];
    }

    // update the queue size
    queueStructPtr->size--;

    // void, no return
}
