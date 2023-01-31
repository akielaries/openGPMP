/*
 * function implementations for inserting data into 
 * our trees
 */
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "tree_init.h"
#include "tree_ops.h"
#include "tree_ops_helpers.h"

PasswordType *import_data(int size) {
    // initialize variables
    PasswordType *rootPtr = NULL, *insertNodePtr = NULL;
    FILE *inputFilePtr;
    int index, rank;
    char comma;
    unsigned long long int password;

    // open input file
    //inputFilePtr = fopen("LeftLeftTest.csv", "r");
    //inputFilePtr = fopen("RightRightTest.csv", "r");
    //inputFilePtr = fopen("TestCases.csv", "r");
    inputFilePtr = fopen("../data/BinarySearchTreeData.csv", "r");
    //inputFilePtr = fopen("LeftRightTest.csv", "r");
    // loop across the number of nodes to read in
    for(index = 0; index < size; index++) {
        // read in data pair
        fscanf(inputFilePtr, "%d", &rank);
        fscanf(inputFilePtr, "%c", &comma);
        fscanf(inputFilePtr, "%I64llu", &password);
        // create node and set data
        insertNodePtr = init_node_from_data(rank, password);
        // call insert to place node
        rootPtr = insert_AVL_data(rootPtr, insertNodePtr);
    }
    // close data file
    fclose(inputFilePtr);
    // return root node
    return rootPtr;
}

/*
Name: initializeNodeFromData
Process: creates a node, places data into node, sets child pointers 
to NULL, returns pointer to created node.
Function input/parameters: rankInput (int), passInput (unsigned long long int)
Function output/parameters: none
Function output/returned: pointer to created node
Device input/file: none
Device output/monitor: none
Dependencies: malloc, sizeof
*/
PasswordType *init_node_from_data(int rankInput,
        unsigned long long int passInput) {
    // initialize variables
    PasswordType *newNodePtr = NULL;
    // create new node
    newNodePtr = (PasswordType *)malloc(sizeof(PasswordType));
    // put data into node
    newNodePtr->rank = rankInput;
    newNodePtr->password = passInput;
    // initialize child pointer to null
    newNodePtr->leftChildPtr = NULL;
    newNodePtr->rightChildPtr = NULL;
    // return pointer to created node
    return newNodePtr;
}

/*
Name: setNodeFromNode
Process: copies data from source node into destination node
Function input/parameters: pointer to node with data that should be copied (source)
Function output/parameters: pointer to node that should have its data changed (dest)
Function output/returned: none
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
void set_node_data_from_node(PasswordType *destNode, PasswordType *srcNode)
{
    //memcpy(srcNode, destNode, sizeof(destNode));
    destNode->rank = srcNode->rank;
    destNode->password = srcNode->password;
    // void, no return
}

