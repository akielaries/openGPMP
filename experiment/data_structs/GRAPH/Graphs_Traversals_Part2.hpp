// Inclusion guard
#ifndef GRAPH_UTILITY_H
#define GRAPH_UTILITY_H

// Header files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Data structure
typedef struct GraphType {
    int   totalVertices;
    int **vertexAdjacencyLists;
    bool *visitedArray;

} GraphType;

// constants
/* TO DO: Place these at the top of utility.c file
const int NEIGHBOR_CAPACITY = 10;
const int NO_NEIGHBOR = -999999; */

// New functions
/*
Name: breadthFirstTraversal
Process: Function creates a queue,
         traverses the graph using the breadth first search algorithm,
         and places vertices in the outputArray to preserve the order each
vertex is visited, and frees queue when traveral is complete. Function
input/parameters: vertexStruct (GraphType *) Function output/parameters:
updated vertexStruct, outputArray (place vertices in array as they are
traversed) Function output/returned: none Device input/file: none Device
output/monitor: none Dependencies: initializeQueue, enqueue, dequeue, free
*/
void breadthFirstTraversal(GraphType *vertexStruct, int outputArray[]);

/*
Name: depthFirstTraversal
Process: Function creates a stack pointer,
         traverses the graph using the depth first search algorithm,
         and places vertices in the outputArray to preserve the order
         each vertex is visited.
Function input/parameters: vertexStruct (GraphType *)
Function output/parameters: updated vertexStruct,
                            outputArray (place vertices in array as they
are traversed) Function output/returned: none Device input/file: none
Device output/monitor: none
Dependencies: push, pop
*/
void depthFirstTraversal(GraphType *vertexStruct, int outputArray[]);

// Have seen these functions before
/*
Name: buildAdjacencyList
Process:  Prompts user for total vertices, the total number of neighbors
each vertex has, all the neighbors, and builds adjacency list for each
vertex. Before neighbors are placed, the constant NO_NEIGHBOR is placed in
each element of the neighbor arrays. The visited array is initialized. All
relavent information is placed in vertexStruct. The vertexStruct variable
that has all relavent information is returned.

          Note about vertexAdjacencyList array:
          Adjacency vertex lists are stored in a 2D array
(vertexAdjacencyLists[firstDimension][secondDimension]). The second
dimension is an array of all the neighbors a given vertex has. The first
dimension is the vertex that has those neighbors.

          ex: vertexAdjacencyLists[1][0]; // this accesses vertex 1's first
neighbor

Function input/parameters: none
Function output/parameters: none
Function output/returned: created vertex struct (GraphType)
Device input/file: none
Device output/monitor: none
Dependencies: clearAdjacencyLists, printf, scanf, malloc, sizeof,
initializeVisitedArray

HINT: When a function requires a pointer parameter, and the only
information avaliable is not a pointer, passing in the address of that
variable will satisfy the parameter requirements.

    ex: &vertexStruct
*/
GraphType buildAdjacencyLists();

/*
Name: clearAdjacencyLists
Process: Sets each element in the adjacency lists to NO_NEIGHBOR.
Function input/parameters: vertexStruct (GraphType *)
Function output/parameters: updated vertexStruct
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
void clearAdjacencyLists(GraphType *vertexStruct);

/*
Name: displayAdjacencyLists
Process: Displays the adjacency list for each vertex.
Function input/parameters: vertexStruct (GraphType)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: adjacency lists
Dependencies: printf
*/
void displayAdjacencyLists(GraphType *vertexStruct);

/*
Name: displayVisitationStatus
Process: Displays each vertex, and whether or not is has been visited.
Function input/parameters: vertexStruct (GraphType)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: visitationStatus
Dependencies: printf
*/
void displayVisitationStatus(GraphType *vertexStruct);

/*
Name: freeAdjacencyLists
Process: Frees both dimensions of the vertexAdjacencyLists array
Function input/parameters: vertexStruct (GraphType)
Function output/parameters: none
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: free
*/
void freeAdjacencyLists(GraphType *vertexStruct);

/*
Name: initializeVisitedArray
Process: allocated memory for the visitedArray, and sets each element of
the visited array to false Function input/parameters: vertexStruct
(GraphType *) Function output/parameters: none Function output/returned:
none Device input/file: none Device output/monitor: none Dependencies: none
*/
void initializeVisitedArray(GraphType *vertexStruct);

#endif