#include "Graphs_Traversals_Part2.h"

int main()
{
    // initialize variables
    int traversalArray[15];
    int index;
    
    GraphType vertexManager = buildAdjacencyLists();
    
    displayAdjacencyLists(&vertexManager);
    
    breadthFirstTraversal(&vertexManager, traversalArray );
    
    printf("\n Visitation Status: \n");
    displayVisitationStatus(&vertexManager);
    
    printf("\n BFS Traversal: ");
    for(index = 0; index < vertexManager.totalVertices; index++)
    {
        printf("%d ", traversalArray[index]);
    }
    
    printf("\n\nResetting each vertex to not visited.\n");
    initializeVisitedArray(&vertexManager);
    
    depthFirstTraversal(&vertexManager, traversalArray);
    
     printf("\n DFS Traversal: ");
    for(index = 0; index < vertexManager.totalVertices; index++)
    {
        printf("%d ", traversalArray[index]);
    }
    
    printf("\n\n");
    
    displayVisitationStatus(&vertexManager);
    
    freeAdjacencyLists(&vertexManager);
    free(vertexManager.visitedArray);
        
    printf("\n\nEnd Program\n");
    
    return 0;
}
