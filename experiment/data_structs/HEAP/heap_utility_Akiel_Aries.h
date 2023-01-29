/*
 *  function declarations for MaxHeap
 */

#ifndef HEAP_UTILITY_H
#define HEAP_UTILITY_H

void bubbleUp(int currentIndex, int *heapArray);
int findMax(int *heapArray);
int findMin(int *heapArray, int size);
int insertInHeap(int inData, int size, int *heapArray);
void swap(int firstIndex, int otherIndex, int *heapArray);
int removeFromHeap(int size, int *heapArray);
void trickleDown(int currentIndex, int size, int *heapArray);
int *createHeap(int size);
void writeHeapToFile(int size, FILE *outputFilePtr, int *heapArray);

#endif

