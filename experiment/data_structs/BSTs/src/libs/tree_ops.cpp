/*
 * function implementations for various operations
 * to be conducted on the trees
 */
#include "tree_ops.h"
#include "constants.h"
#include "removal.h"
#include "tree_ops_helpers.h"
#include <stdio.h>

/*
Name: insert_AVL_data
Process: inserts data into our AVL tree
Function input/parameters: wkgPtr, inNodePtr
Function output/parameters: NONE
Function output/returned: wkgPtr
Device input/file: NONE
Device output/file: NONE
Dependencies: insert_AVL_data (RECURSIVE), find_subtree_height(), printf,
right_rotation, left_rotation,
*/
PasswordType *insert_AVL_data(PasswordType *wkgPtr,
                              PasswordType *inNodePtr) {
    // initialize variables
    int heightDifference, leftSubTreeHeight, rightSubTreeHeight;

    // check for wkgPtr not null
    if (wkgPtr != NULL) {
        // check to see in insertion data is smaller than current node data
        if (inNodePtr->rank < wkgPtr->rank) {
            // recurse to the left
            wkgPtr->leftChildPtr =
                insert_AVL_data(wkgPtr->leftChildPtr, inNodePtr);
        }

        // otherwise, check to see in insertiondata is larger than current
        // node
        else if (inNodePtr->rank > wkgPtr->rank) {
            // recurse to the right
            wkgPtr->rightChildPtr =
                insert_AVL_data(wkgPtr->rightChildPtr, inNodePtr);
        }

        // get difference of height between subtrees
        // get height of left subtree
        leftSubTreeHeight = find_subtree_height(wkgPtr->leftChildPtr);

        // get height of right subtree
        rightSubTreeHeight = find_subtree_height(wkgPtr->rightChildPtr);

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
            wkgPtr = right_rotation(wkgPtr);
        }

        // check for right right case
        else if (heightDifference < -1 &&
                 inNodePtr->rank > wkgPtr->rightChildPtr->rank) {
            printf("\n    right right case\n");
            printf("\n      --rotating left on node with rank %d\n",
                   wkgPtr->rank);
            // left rotation to rebalance
            wkgPtr = left_rotation(wkgPtr);
        }

        // check for left right case
        else if (heightDifference > 1 &&
                 inNodePtr->rank > wkgPtr->leftChildPtr->rank) {
            printf("\n    left right case\n");
            printf("\n      --rotating left on node with rank %d\n",
                   wkgPtr->leftChildPtr->rank);
            // left, then right rotation to rebalance
            wkgPtr->leftChildPtr = left_rotation(wkgPtr->leftChildPtr);

            printf("\n      --rotating right on node with rank %d\n",
                   wkgPtr->rank);
            wkgPtr = right_rotation(wkgPtr);
        }

        // check for right left case
        else if (heightDifference < -1 &&
                 inNodePtr->rank < wkgPtr->rightChildPtr->rank) {
            printf("\n    right left case\n");
            printf("\n      --rotating right on node with rank %d\n",
                   wkgPtr->rightChildPtr->rank);
            // right then left rotation to rebalance
            wkgPtr->rightChildPtr = right_rotation(wkgPtr->rightChildPtr);

            printf("\n      --rotating left on node with rank %d\n",
                   wkgPtr->rank);
            wkgPtr = left_rotation(wkgPtr);
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
Name: removeItem
Process: searches for item to be removed, if item is present then helper
function is called to remove it. Otherwise, a message is displayed to the
console indicating the item is not present. Function input/parameters:
rootPtr of tree, pointer to data that should be removed Function
output/parameters: none Function output/returned: updated rootPtr Device
input/file: none Device output/monitor: none Dependencies:  printf,
removeItemHelper, search
*/
PasswordType *remove_item(PasswordType *rootPtr,
                          PasswordType *toRemovePtr) {
    // initialize variables
    PasswordType *temp;
    // call search function
    temp = search(rootPtr, toRemovePtr);
    // check to see if the pointer assigned to the search call is not null
    if (temp != NULL) {
        // call removeItemHelper to remove the data from the tree
        rootPtr = remove_item_helper(rootPtr, toRemovePtr);
    }

    // otherwise, assume search returned null
    else {
        // display message to console indicating data is not present
        printf("Data is not present!");
    }
    return rootPtr;
}

/*
Name: displayTreeInOrder
Process: recursively writes binary search tree data to output file using
inorder traversal. Function input/parameters: working pointer for
recursion, file name Function output/parameters: none Function
output/returned: none Device input/file:none Device output/file: file with
BST data written to it Dependencies: fprintf, displayTreeInOrder LNR (LEFT,
NODE, RIGHT) in order traversal
*/
void display_in_order(PasswordType *wkgPtr, FILE *outputFile) {
    // check for working ptr not null
    if (wkgPtr != NULL) {
        // recursive call to the left
        display_in_order(wkgPtr->leftChildPtr, outputFile);
        // write data from current node to file in format: rank, password
        fprintf(outputFile, "%d, %I64llu\n", wkgPtr->rank,
                wkgPtr->password);
        // recursive call to the right
        display_in_order(wkgPtr->rightChildPtr, outputFile);
    }
    // void, no return
}

/*
Name: left_rotation
Process: rotates our tree to the left by reassigning the parent; right
child to a temp ptr Function input/parameters: localPtr Function
output/parameters:NONE Function output/returned: newParentPtr Device
input/file: NONE Device output/file: NONE Dependencies: NONE
*/
PasswordType *left_rotation(PasswordType *localPtr) {
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

/*
Name: right_rotation
Process: rotates our tree to the right by reassigning the parent; left
child to a temp ptr Function input/parameters: localPtr Function
output/parameters:NONE Function output/returned: newParentPtr Device
input/file: NONE Device output/file: NONE Dependencies: NONE
*/
PasswordType *right_rotation(PasswordType *localPtr) {
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
