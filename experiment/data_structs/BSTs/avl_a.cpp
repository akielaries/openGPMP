// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_NODES = 150000;

// data structure
typedef struct PasswordTypeStruct {
    int rank;
    unsigned long long int password;
    struct PasswordTypeStruct *leftChildPtr;
    struct PasswordTypeStruct *rightChildPtr;
} PasswordType;

// function declarations
// new functions
int getBalanceFactor(PasswordType *localPtr);
PasswordType *rebalanceTree(PasswordType *localPtr);
PasswordType *removeItem(PasswordType *rootPtr, PasswordType *toRemovePtr);
PasswordType *removeItemHelper(PasswordType *wkgPtr,
                               PasswordType *toRemovePtr);
PasswordType *search(PasswordType *wkgPtr, PasswordType *toRemovePtr);
PasswordType *removeFromMax(PasswordType *parentPtr,
                            PasswordType *childPtr);
void setNodeDataFromNode(PasswordType *destNode, PasswordType *srcNode);

// provided function
PasswordType *clearTree(PasswordType *wkgPtr);
void displayTreeInOrder(PasswordType *wkgPtr, FILE *outputFile);
int findSubTreeHeight(PasswordType *localPtr);
int getMax(int valOne, int valTwo);
PasswordType *leftRotation(PasswordType *localPtr);
PasswordType *rightRotation(PasswordType *localPtr);
PasswordType *importData(int size);
PasswordType *insert(PasswordType *wkgPtr, PasswordType *inNodePtr);
PasswordType *initializeNodeFromData(int rankInput,
                                     unsigned long long int passInput);

// main driver
int main() {
    // initialize variables
    int size;
    PasswordType *rootPtr = NULL;
    PasswordType tempNode;
    FILE *outputFilePtr;

    // prompt for size
    printf("Enter the number of values to be sorted: ");
    scanf("%d", &size);

    // check for acceptable size input
    if (size >= 1 && size <= MAX_NODES) {
        // build the AVL tree
        rootPtr = importData(size);

        // check for rootPtr not null
        if (rootPtr != NULL) {
            printf("\nStarting rootPtr: %d\n", rootPtr->rank);

            // remove some nodes
            tempNode.rank = 79681;

            printf("\nRemoving %d\n", tempNode.rank);

            rootPtr = removeItem(rootPtr, &tempNode);

            printf("\nRank at root node after removal is %d\n",
                   rootPtr->rank);

            // remove some nodes
            tempNode.rank = 45267;

            printf("\nRemoving %d\n", tempNode.rank);

            rootPtr = removeItem(rootPtr, &tempNode);

            printf("\nRank at root node after removal is %d\n",
                   rootPtr->rank);

            // remove some nodes
            tempNode.rank = 157255;

            printf("\nRemoving %d\n", tempNode.rank);

            rootPtr = removeItem(rootPtr, &tempNode);

            printf("\nRank at root node after removal is %d\n",
                   rootPtr->rank);

            int heightDiff = findSubTreeHeight(rootPtr->leftChildPtr) -
                             findSubTreeHeight(rootPtr->rightChildPtr);

            printf("\nHeight difference of root node subtrees after "
                   "removals: %d\n",
                   heightDiff);

            // open an output file to write to
            outputFilePtr = fopen("AVL_Tree_1.csv", "w+");

            // write tree to file
            displayTreeInOrder(rootPtr, outputFilePtr);

            // close output file
            fclose(outputFilePtr);

            printf("\nData written to AVL_Tree_1.csv\n");

        }

        // otherwise, empty tree
        else {
            // display error message to console
            printf("\nError: no data found\n");
        }
    }

    // otherwise, size input is not acceptable
    else {
        // display error message to console
        printf("\nIncorrect input\n");
    }

    // display program end
    printf("\nEnd program\n");

    // return function success
    return 0;
}

// functions for students to write

/*
Name: getBalanceFactor
Process: calculates the height difference of a given node's subtrees
Function input/parameters: localPtr
Function output/parameters: none
Function output/returned: height difference between the localPtr's subtrees
(int) Device input/file: none Device output/monitor: none Dependencies:
findSubTreeHeight
*/
int getBalanceFactor(PasswordType *localPtr) {
    // initialize variables

    if (localPtr == NULL)
        return 0;

    // find sub tree height for left and right
    // calculate balance factor (the difference)
    // return balance factor
    return findSubTreeHeight(localPtr->leftChildPtr) -
           findSubTreeHeight(localPtr->rightChildPtr);
}

/*
Name: rebalanceTree
Process: Checks if tree needs to be rebalanced at the node passed in. If it
does, the appropriate rotation steps are taken to rebalance the tree.
Function input/parameters: pointer to node to rebalance (localPtr)
Function output/parameters: none
Function output/returned: updated localPtr
Device input/file: none
Device output/monitor: none
Dependencies: getBalanceFactor
*/
PasswordType *rebalanceTree(PasswordType *localPtr) {
    // initialize variables
    int currentNodeHeightDifference;
    int leftChildHeightDifference;

    // determine if a rebalance is necessary
    // function: getBalanceFactor
    currentNodeHeightDifference = getBalanceFactor(localPtr);

    // check for a left side imbalance  (cNHD is > 1)
    if (currentNodeHeightDifference > 1) {
        // get balance factor of current node's (localPtr) left child
        leftChildHeightDifference =
            getBalanceFactor(localPtr->leftChildPtr);

        // check for a left left case (balance factor >=0)
        if (getBalanceFactor(localPtr->leftChildPtr->leftChildPtr) >= 0) {
            // rotate to resolve the tree (rightRotation)
            // function: rightRotation
            rightRotation(localPtr->leftChildPtr->leftChildPtr);
        }
        // otherwise, assume left right case
        else {
            // rotate as necessary to resolve tree
            leftRotation(localPtr->leftChildPtr->leftChildPtr);
        }
    }
    // otherwise, check for a right side imbalance (cNHD < -1)
    else if (currentNodeHeightDifference < -1) {
        // get balance factor for currentNode's right child
        getBalanceFactor(localPtr->rightChildPtr);
        // check for right right case (balance factor is <=0)
        if (getBalanceFactor(localPtr->rightChildPtr->rightChildPtr) <=
            0) {
            //  rotate to rebalance
            rightRotation(localPtr->rightChildPtr->rightChildPtr);
        }
        // otherwise, assume right - left case
        else {
            // rotate to rebalance
            leftRotation(localPtr->rightChildPtr->rightChildPtr);
        }
    }
    return localPtr;
}

/*
Name: removeFromMax
Process: recursively traverses for max node. When found, unlinks node from
tree and returns it. Function input/parameters: pointer to parent and child
nodes Function output/parameters: none Function output/returned: pointer to
unlinked node Device input/file: none Device output/monitor: none
Dependencies: removeFromMax
*/
PasswordType *removeFromMax(PasswordType *parentPtr,
                            PasswordType *childPtr) {
    // check to see if the child has a right child
    if (childPtr->rightChildPtr != NULL) {
        // call removeFromMax with the child as the parent parameter, and
        // the
        //  child's right child as the child parameter
        return removeFromMax(childPtr, childPtr->rightChildPtr);
    }
    // unlink right most node from the tree
    parentPtr->rightChildPtr = childPtr->leftChildPtr;
    // return pointer to unlinked node
    return childPtr;
}

/*
Name: removeItem
Process: searches for item to be removed, if item is present then helper
function is called to remove it. Otherwise, a message is displayed to the
console indicating the item is not present. Function input/parameters:
rootPtr of tree, pointer to data that should be removed Function
output/parameters: none Function output/returned: updated rootPtr Device
input/file: none Device output/monitor: none Dependencies:  printf,
removeItemHelper, search
*/
PasswordType *removeItem(PasswordType *rootPtr,
                         PasswordType *toRemovePtr) {
    // initialize variables
    PasswordType *temp;
    // call search function
    temp = search(rootPtr, toRemovePtr);
    // check to see if the pointer assigned to the search call is not null
    if (temp != NULL) {
        // call removeItemHelper to remove the data from the tree
        rootPtr = removeItemHelper(rootPtr, toRemovePtr);
    }

    // otherwise, assume search returned null
    else {
        // display message to console indicating data is not present
        printf("Data is not present!");
    }
    return rootPtr;
}

/*
Name: removeItemHelper
Process: recursively searches for item, removes node,
         returns dynamic memory of removed node to OS,
         rebalances the tree and returns updated link to parent (at each
recursive level) Function input/parameters: rootPtr of tree, pointer to
data that should be removed Function output/parameters: none Function
output/returned: link to recursive parent Device input/file: none Device
output/monitor: none Dependencies: rebalanceTree, removeItemHelper,
removeFromMax, setNodeDataFromNode, free
*/
PasswordType *removeItemHelper(PasswordType *wkgPtr,
                               PasswordType *toRemovePtr) {
    // initialize variables
    PasswordType *temp = NULL;
    // check for wkgPtr is not null
    if (wkgPtr != NULL) {
        // check if the the data to be removed is less than the current
        // node data
        if (toRemovePtr->rank < wkgPtr->rank) {
            // recurse to the left
            wkgPtr->leftChildPtr =
                removeItemHelper(wkgPtr->leftChildPtr, toRemovePtr);
        }
        // otherwise, check to see if removal data is larger than the data
        // at the current node
        else if (toRemovePtr->rank > wkgPtr->rank) {
            // recurse to the right
            wkgPtr->rightChildPtr =
                removeItemHelper(wkgPtr->rightChildPtr, toRemovePtr);
        }

        // otherwise, data to be removed has been found
        else {
            // check to see if the current node's (wkgPtr) left child is
            // null
            if (wkgPtr->leftChildPtr == NULL) {
                // assign a temporary ptr to current node's right chil
                temp = wkgPtr->rightChildPtr;
                // free the current node
                free(wkgPtr);
                // point wkgPtr at the temp ptr
                wkgPtr = temp;
            }
            // otherwise, check to see if the current node's right child is
            // null
            else if (wkgPtr->rightChildPtr == NULL) {
                // assign temp ptr to left child
                temp = wkgPtr->leftChildPtr;
                // free the current node
                free(wkgPtr);
                // point wkgPtr as tempPtr
                wkgPtr = temp;
            }
            // otherwise, assume node has two children
            else {
                // check to se if current node's left child has a right
                // child
                if (wkgPtr->leftChildPtr->rightChildPtr != NULL) {
                    // call remove from max
                    temp = removeFromMax(
                        wkgPtr, wkgPtr->leftChildPtr->rightChildPtr);
                    // copy data from removeFromMax into current node
                    // function: setNodeDataFromData
                    // setNodeDataFromNode(wkgPtr,
                    // wkgPtr->leftChildPtr->rightChildPtr);
                    setNodeDataFromNode(wkgPtr, temp);
                    // free the node that was unlinked (tempPtr)
                    free(temp);
                }
                // otherwise, current node's left child does not have a
                // right child
                else {
                    // copy left child into current node
                    setNodeDataFromNode(wkgPtr, wkgPtr->leftChildPtr);
                    // unlink the left child
                    wkgPtr->leftChildPtr = wkgPtr->rightChildPtr;
                    // free the left child
                    free(wkgPtr->leftChildPtr);
                }
            }
        }
        // check to see if wkgPtr is not null
        if (wkgPtr != NULL) {
            // rebalance tree
            rebalanceTree(wkgPtr);
        }
    }
    return wkgPtr;
}

/*
Name: search
Process: searches for data, if data is present function returns a pointer
to node, if node is not found, function returns NULL. Function
input/parameters: rootPtr of tree, pointer to data that should be removed
Function output/parameters: none
Function output/returned: pointer to node if found, NULL if node is not
found. Device input/file: none Device output/monitor: none Dependencies:
search (recursive)
*/
PasswordType *search(PasswordType *wkgPtr, PasswordType *toRemovePtr) {
    // initialize variables
    PasswordType *returnPtr = NULL;

    // check for wkgPtr is not null
    if (wkgPtr != NULL) {
        // check to see if the data at toRemovePtr is less than the rank at
        // wkgPtr
        if (toRemovePtr->rank < wkgPtr->rank) {
            // return a recursive call to the left
            return search(wkgPtr->leftChildPtr, toRemovePtr);
        }
        // otherwise, check to see if removal data is larger than data at
        // wkgPtr
        else if (toRemovePtr->rank > wkgPtr->rank) {
            // return a recursive call to the right
            return search(wkgPtr->rightChildPtr, toRemovePtr);
        }
        // otherwise data has been found
        else {
            // assign returnPtr to wkgPtr
            returnPtr = wkgPtr;
        }
    }
    return returnPtr;
}

/*
Name: setNodeFromNode
Process: copies data from source node into destination node
Function input/parameters: pointer to node with data that should be copied
(source) Function output/parameters: pointer to node that should have its
data changed (dest) Function output/returned: none Device input/file: none
Device output/monitor: none
Dependencies: none
*/
void setNodeDataFromNode(PasswordType *destNode, PasswordType *srcNode) {
    // memcpy(srcNode, destNode, sizeof(destNode));
    srcNode = destNode;
    destNode = srcNode;

    // void, no return
}

/* TO DO: Copy in these functions from previous homework:
PasswordType *clearTree(PasswordType *wkgPtr);
void displayTreeInOrder(PasswordType *wkgPtr, FILE *outputFile);
int findSubTreeHeight(PasswordType *localPtr);
int getMax(int valOne, int valTwo);
PasswordType *leftRotation(PasswordType *localPtr);
PasswordType *rightRotation(PasswordType *localPtr);
PasswordType *insert(PasswordType *wkgPtr, PasswordType *inNodePtr);
PasswordType *initializeNodeFromData(int rankInput,
                                              unsigned long long int
passInput); */

PasswordType *clearTree(PasswordType *wkgPtr) {
    // check for wkgPtr not null
    if (wkgPtr != NULL) {
        // clear the left side
        clearTree(wkgPtr->leftChildPtr);

        // clear the right side
        clearTree(wkgPtr->rightChildPtr);

        // free current node
        free(wkgPtr);
    }

    // return NULL
    return NULL;
}

PasswordType *insert(PasswordType *wkgPtr, PasswordType *inNodePtr) {
    // initialize variables
    int heightDifference, leftSubTreeHeight, rightSubTreeHeight;

    // check for wkgPtr not null
    if (wkgPtr != NULL) {
        // check to see in insertion data is smaller than current node data
        if (inNodePtr->rank < wkgPtr->rank) {
            // recurse to the left
            wkgPtr->leftChildPtr = insert(wkgPtr->leftChildPtr, inNodePtr);
        }

        // otherwise, check to see in insertiondata is larger than current
        // node
        else if (inNodePtr->rank > wkgPtr->rank) {
            // recurse to the right
            wkgPtr->rightChildPtr =
                insert(wkgPtr->rightChildPtr, inNodePtr);
        }

        // get difference of height between subtrees

        // get height of left subtree
        leftSubTreeHeight = findSubTreeHeight(wkgPtr->leftChildPtr);

        // get height of right subtree
        rightSubTreeHeight = findSubTreeHeight(wkgPtr->rightChildPtr);

        // calculate height difference
        heightDifference = leftSubTreeHeight - rightSubTreeHeight;

        printf("\n    Height difference: %d\n", heightDifference);

        // check for cases, and rebalance

        // check for left left case
        if (heightDifference > 1 &&
            inNodePtr->rank < wkgPtr->leftChildPtr->rank) {
            printf("\n    left left case\n");
            printf("\n      --rotating right on node with rank %d\n",
                   wkgPtr->rank);
            // right rotation to rebalance
            wkgPtr = rightRotation(wkgPtr);
        }

        // check for right right case
        else if (heightDifference < -1 &&
                 inNodePtr->rank > wkgPtr->rightChildPtr->rank) {
            printf("\n    right right case\n");
            printf("\n      --rotating left on node with rank %d\n",
                   wkgPtr->rank);

            // left rotation to rebalance
            wkgPtr = leftRotation(wkgPtr);
        }

        // check for left right case
        else if (heightDifference > 1 &&
                 inNodePtr->rank > wkgPtr->leftChildPtr->rank) {
            printf("\n    left right case\n");
            printf("\n      --rotating left on node with rank %d\n",
                   wkgPtr->leftChildPtr->rank);

            // left, then right rotation to rebalance
            wkgPtr->leftChildPtr = leftRotation(wkgPtr->leftChildPtr);

            printf("\n      --rotating right on node with rank %d\n",
                   wkgPtr->rank);

            wkgPtr = rightRotation(wkgPtr);
        }

        // check for right left case
        else if (heightDifference < -1 &&
                 inNodePtr->rank < wkgPtr->rightChildPtr->rank) {
            printf("\n    right left case\n");
            printf("\n      --rotating right on node with rank %d\n",
                   wkgPtr->rightChildPtr->rank);

            // right then left rotation to rebalance
            wkgPtr->rightChildPtr = rightRotation(wkgPtr->rightChildPtr);

            printf("\n      --rotating left on node with rank %d\n",
                   wkgPtr->rank);

            wkgPtr = leftRotation(wkgPtr);
        }

    }

    // otherwise, wkgPtr is null (end of tree is reached)
    else {
        // assign wkgPtr to inNodePtr, falling back to calling function
        // will link the node into tree
        wkgPtr = inNodePtr;

        printf("\nInserting node with rank: %d\n", wkgPtr->rank);
    }

    // return the current node
    return wkgPtr;
}

int findSubTreeHeight(PasswordType *localPtr) {
    // initialize variables
    int leftHeight, rightHeight;

    // check for localPtr not null
    if (localPtr != NULL) {
        // find height of left subtree
        leftHeight = findSubTreeHeight(localPtr->leftChildPtr);

        // find height of right subtree
        rightHeight = findSubTreeHeight(localPtr->rightChildPtr);

        // return 1 + the max height of either subtree
        return 1 + getMax(leftHeight, rightHeight);
    }

    // return -1 in the case that localPtr is null
    return -1;
}

int getMax(int valOne, int valTwo) {
    // initialize variables
    int largerVal = valOne;

    // check to see if valTwo is larger than one
    if (valTwo > valOne) {
        // reassign largerVal for return
        largerVal = valTwo;
    }

    // return the larger value
    return largerVal;
}

PasswordType *leftRotation(PasswordType *localPtr) {
    // initialize variables
    PasswordType *tempPtr = NULL;
    PasswordType *newParentPtr = localPtr->rightChildPtr;

    // assign temp ptr to newParentPtr's right child
    tempPtr = newParentPtr->leftChildPtr;

    // assign old parent (localPtr) as newParent's right child
    newParentPtr->leftChildPtr = localPtr;

    // assign temp ptr as localPtr's left child
    localPtr->rightChildPtr = tempPtr;

    // return pointer to new parent
    return newParentPtr;
}

PasswordType *rightRotation(PasswordType *localPtr) {
    // initialize variables
    PasswordType *tempPtr = NULL;
    PasswordType *newParentPtr = localPtr->leftChildPtr;

    // assign temp ptr to newParentPtr's left child
    tempPtr = newParentPtr->rightChildPtr;

    // assign old parent (localPtr) as newParent's left child
    newParentPtr->rightChildPtr = localPtr;

    // assign temp ptr as localPtr's left child
    localPtr->leftChildPtr = tempPtr;

    // return pointer to new parent
    return newParentPtr;
}

// provided
PasswordType *importData(int size) {
    // initialize variables
    PasswordType *rootPtr = NULL, *insertNodePtr = NULL;
    FILE *inputFilePtr;
    int index, rank;
    char comma;
    unsigned long long int password;

    // open input file
    // inputFilePtr = fopen("LeftLeftTest.csv", "r");
    // inputFilePtr = fopen("RightRightTest.csv", "r");
    // inputFilePtr = fopen("TestCases.csv", "r");
    inputFilePtr = fopen("BinarySearchTreeData.csv", "r");
    // inputFilePtr = fopen("LeftRightTest.csv", "r");

    // loop across the number of nodes to read in
    for (index = 0; index < size; index++) {
        // read in data pair
        fscanf(inputFilePtr, "%d", &rank);
        fscanf(inputFilePtr, "%c", &comma);
        fscanf(inputFilePtr, "%I64llu", &password);

        // create node and set data
        insertNodePtr = initializeNodeFromData(rank, password);

        // call insert to place node
        rootPtr = insert(rootPtr, insertNodePtr);
    }

    // close data file
    fclose(inputFilePtr);

    // return root node
    return rootPtr;
}

void displayTreeInOrder(PasswordType *wkgPtr, FILE *outputFile) {
    // initialize variables

    // check for wkgPtr not null
    if (wkgPtr != NULL) {
        // recursive call to the left
        displayTreeInOrder(wkgPtr->leftChildPtr, outputFile);

        // write  data at wkgPtr to file in format: rank, password
        fprintf(outputFile, "%d, %I64llu\n", wkgPtr->rank,
                wkgPtr->password);

        // recursive call to the right
        displayTreeInOrder(wkgPtr->rightChildPtr, outputFile);
    }
    // void, no return
}

PasswordType *initializeNodeFromData(int rankInput,
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
