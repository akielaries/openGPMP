#include "Graphs_Traversals_Part2.h"
#include "Queue_Utility.h"
#include "Stack_Utility.h"

const int NEIGHBOR_CAPACITY = 10;
const int NO_NEIGHBOR = -999999;

/*
Name: breadthFirstTraversal
Process: Function creates a queue,
         traverses the graph using the breadth first search algorithm,
         and places vertices in the outputArray to preserve the order each vertex is visited,
         and frees queue when traveral is complete.
Function input/parameters: vertexStruct (GraphType *)
Function output/parameters: updated vertexStruct, 
                            outputArray (place vertices in array as they are traversed)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: initializeQueue, enqueue, dequeue, free
*/
void breadthFirstTraversal(GraphType *vertexStruct, int outputArray[])
{
    // initialize variables
    bool visited;
    int outputIndex, totalVertices, vertexIndex, totalNeighbors;
    int currentNeighbor, neighborIndex, neighbor;    
    QueueType *queueStruct;
    GraphType vertexManager;

    GraphType visitedArray;
    QueueType *queueIndex;
    QueueType queue;
    // create queue
        // function: initializeQueue
    initializeQueue(queueStruct, vertexStruct->totalVertices);
    // visit first vertex (start at vertex 0; use visited array)
    vertexStruct->visitedArray[0] = true;
    // enqueue starting at vertex (0)
    enqueue(queueStruct, 0);
    // put starting vertex into the first element of the output array
    outputArray[outputIndex] = 0;
    // loop while the queue exists
    while (queueStruct != NULL)
    {
        // check to see if current neighbor has not be visited
        if (!(vertexStruct->visitedArray[currentNeighbor]))
        {
        // dequeue to get the current vertex
        dequeue(queueStruct);
        // get the first neighbor
        vertexStruct->visitedArray[currentNeighbor];
        // loop while neighbors exists (not NO_NEIGHBOR)
        while (totalNeighbors != NULL)
        {
            // enqueue the neighbor
            enqueue(currentNeighbor);
            // set the neighbor to visited
            currentNeighbor = visitedArray;
            // place neighbor into output array
            neighborIndex += outputArray[outputIndex];
        // get the next neigbor
            // increment neighbor index
        // currentNeighbor = array[][neighborIndex];
        currentNeighbor = array[vertexIndex][neighborIndex];
        }
    }   
    // free the queue (outside all loops)
    free(queueStruct);
}

/*
Name: depthFirstTraversal
Process: Function creates a stack pointer,
         traverses the graph using the depth first search algorithm,
         and places vertices in the outputArray to preserve the order
         each vertex is visited.
Function input/parameters: vertexStruct (GraphType *)
Function output/parameters: updated vertexStruct, 
                            outputArray (place vertices in array as they are traversed)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: push, pop
*/
void depthFirstTraversal(GraphType *vertexStruct, int outputArray[])
{
    // initialize variables
    bool vertexNotFound;
    
    StackNodeType stackTopPtr;
    StackNodeType *stackTypeStruct;
    // visiting the first vertext add to output array
    StackTypeStruct->visitedArray[0] = true;
    // push to stack
    push(stackTypeStruct, 0);
    // loop while stack exists
    while (StackTypeStruct != NULL)
    {
        // look at top of the stack (NOT POP), get current vertext
        currentVertex = stackTopPtr->value;
        // getting the first neighbor of the current vertex
        
        // set a boolean to true
        vertextNotFound = true;
        // loop while there are neighbors, and boolean is true
        while (totalNeighbors != 0)
        {
            // check if current neighbor has not been visited
            if (currentNeighbor = visitedArray)
                // visit it, put into output array, put onto top of stack
                currentNeighbor = visitedArray;
                // set vertexNotFoundToFalse
                vertexNotFound = false;
            // get next neighbor
        }
            currentNeighbor = array[vertexIndex][neighborIndex];
        // check to see if current neighbor is NO_NEIGHBOR and vertextNotFound is still true
        if (currentNeighbor == NO_NEIGHBOR && vertexNotFound == true)
            // pop the top of the stack
            pop(stackTopPtr);
    }
}

GraphType buildAdjacencyLists()
{
    // initialize variables
    int totalVertices, vertexIndex, totalNeighbors;
    int neighborIndex, neighbor;
    GraphType vertexManager;

    // prompt for total number of vertices
    printf("\nHow many vertices are in this graph? ");
    scanf("%d", &totalVertices);

    // put total verticies into struct
    vertexManager.totalVertices = totalVertices;

    // allocate memory for first dimension of array
    int **adjacencyListPtr = (int **)malloc(totalVertices * sizeof(int*));

    // loop to allocate memory for the second dimension of the array
    for(vertexIndex = 0; vertexIndex < totalVertices; vertexIndex++)
    {
        // allocate memory for each element
        adjacencyListPtr[vertexIndex] = (int *)malloc(
                                                NEIGHBOR_CAPACITY* sizeof(int));
    }

    // assign array ptr to struct
    vertexManager.vertexAdjacencyLists = adjacencyListPtr;

    // set each element in adjacency lists to NO_NEIGHBOR
    clearAdjacencyLists(&vertexManager);

    // display least to greatest message
    printf("\nPlease enter the neighbors of each vertex in increasing order.\n");

    // loop for all vertices
    for(vertexIndex = 0; vertexIndex < totalVertices; vertexIndex++)
    {
        // prompt for total neightbors of current vertex
        printf("\nHow many neighbors does vertex %d have? ", vertexIndex);
        scanf("%d", &totalNeighbors);

        // loop to prompt for neightbors individually
        for(neighborIndex = 0; neighborIndex < totalNeighbors; neighborIndex++)
        {
            // prompt for neighbor
            printf("   Enter vertex %d's neighbor: ", vertexIndex);
            scanf("%d", &neighbor);

            // place neightbors in adjacency matrix
            vertexManager.vertexAdjacencyLists[vertexIndex][neighborIndex]
                                                                     = neighbor;
        }
    }

   // create the visited array, set each to element to false
   initializeVisitedArray(&vertexManager);

   return vertexManager;

}

void clearAdjacencyLists(GraphType *vertexStruct)
{
    // initialize variables
    int index, innerIndex;

    for(index = 0; index < vertexStruct->totalVertices; index++)
    {
         for(innerIndex = 0; innerIndex < NEIGHBOR_CAPACITY; innerIndex++)
         {
             vertexStruct->vertexAdjacencyLists[index][innerIndex] = NO_NEIGHBOR;
         }
    }
}

void displayAdjacencyLists(GraphType *vertexStruct)
{
    int rowIndex, colIndex;

    printf("\n\nGraph adjacency lists: \n");

    for(rowIndex = 0; rowIndex < vertexStruct->totalVertices; rowIndex++)
    {
        printf("Vertex %d Neighbors:  ", rowIndex);

        for(colIndex = 0; colIndex < vertexStruct->totalVertices; colIndex++)
        {
            if(vertexStruct->vertexAdjacencyLists[rowIndex][colIndex] != NO_NEIGHBOR)
            {
                printf("%d ",
                        vertexStruct->vertexAdjacencyLists[rowIndex][colIndex]);

            }


        }

        printf("\n");
    }

    printf("\n\n");
}

void displayVisitationStatus(GraphType *vertexStruct)
{
    int index;

    for(index = 0; index < vertexStruct->totalVertices; index++)
    {
        if(vertexStruct->visitedArray[index])
        {
            printf("%d, visited\n", index);
        }
        else
        {
            printf("%d, not visited\n", index);
        }
    }
}

void freeAdjacencyLists(GraphType *vertexStruct)
{
    int rowIndex;

    for(rowIndex = 0; rowIndex < vertexStruct->totalVertices; rowIndex++)
    {

        free(vertexStruct->vertexAdjacencyLists[rowIndex]);
    }

    free(vertexStruct->vertexAdjacencyLists);

}

void initializeVisitedArray(GraphType *vertexStruct)
{
    // initialize variables
    bool *visitedArray;
    int index;

    // allocate memory for visited array
    visitedArray = (bool *)malloc(vertexStruct->totalVertices * sizeof(bool));

    for(index = 0; index < vertexStruct->totalVertices; index++)
    {
        visitedArray[index] = false;
    }

    vertexStruct->visitedArray = visitedArray;

}


