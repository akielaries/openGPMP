/*
 *  function implementation of all functions assisting tree operations
 */
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "tree_ops_helpers.h"
#include "tree_ops.h"

/*
Name: getBalanceFactor
Process: calculates the height difference of a given node's subtrees
Function input/parameters: localPtr
Function output/parameters: none
Function output/returned: height difference between the localPtr's subtrees (int)
Device input/file: none
Device output/monitor: none
Dependencies: findSubTreeHeight
*/
int get_balance_factor(PasswordType *localPtr) {
    // initialize variables

    if (localPtr == NULL)
        return 0;

    // find sub tree height for left and right
    // calculate balance factor (the difference)
    // return balance factor
    return find_subtree_height(localPtr->leftChildPtr) 
        - find_subtree_height(localPtr->rightChildPtr);
}

/*
Name: rebalanceTree
Process: Checks if tree needs to be rebalanced at the node passed in. If it does,
         the appropriate rotation steps are taken to rebalance the tree.
Function input/parameters: pointer to node to rebalance (localPtr)
Function output/parameters: none
Function output/returned: updated localPtr
Device input/file: none
Device output/monitor: none
Dependencies: getBalanceFactor
*/
PasswordType *rebalance_tree(PasswordType *localPtr) {
    // initialize variables
    int currentNodeHeightDifference;
    int leftChildHeightDifference;

    // determine if a rebalance is necessary
        // function: getBalanceFactor
    currentNodeHeightDifference = get_balance_factor(localPtr);

    // check for a left side imbalance  (cNHD is > 1)
    if (currentNodeHeightDifference > 1) {
        // get balance factor of current node's (localPtr) left child
        leftChildHeightDifference = get_balance_factor(localPtr->leftChildPtr);

        // check for a left left case (balance factor >=0)
        if (get_balance_factor(localPtr->
                    leftChildPtr->leftChildPtr) >= 0) {
            // rotate to resolve the tree (rightRotation)
                // function: rightRotation
            right_rotation(localPtr->leftChildPtr->leftChildPtr);
        }

        // otherwise, assume left right case
        else {
            // rotate as necessary to resolve tree
            left_rotation(localPtr->leftChildPtr->leftChildPtr);
        }
    }

    // otherwise, check for a right side imbalance (cNHD < -1)
    else if (currentNodeHeightDifference < -1) {
        // get balance factor for currentNode's right child
        get_balance_factor(localPtr->rightChildPtr);
        
        // check for right right case (balance factor is <=0)
        if (get_balance_factor(localPtr->
                    rightChildPtr->rightChildPtr) <= 0) {
            //  rotate to rebalance
            right_rotation(localPtr->rightChildPtr->rightChildPtr);
        }

        // otherwise, assume right - left case
        else {
            // rotate to rebalance
            left_rotation(localPtr->rightChildPtr->rightChildPtr);
        }
    }
    return localPtr;
}

int get_max(int valOne, int valTwo) {
    // initialize variables
    int largerVal = valOne;
    // check to see if valTwo is larger than one
    if(valTwo > valOne) {
        // reassign largerVal for return
        largerVal = valTwo;
    }
    // return the larger value
    return largerVal;
}

int find_subtree_height(PasswordType *localPtr) {
    // initialize variables
    int leftHeight, rightHeight;
    // check for localPtr not null
    if(localPtr != NULL) {
        // find height of left subtree
        leftHeight = find_subtree_height(localPtr->leftChildPtr);
        // find height of right subtree
        rightHeight = find_subtree_height(localPtr->rightChildPtr);
        // return 1 + the max height of either subtree
        return 1 + get_max(leftHeight, rightHeight);
    }
    // return -1 in the case that localPtr is null
    return -1;
}
/*
Name: findLargestLeafNode
Process: searches the tree for the largest leaf node, returns a pointer to node.
Function input/parameters: wkgPtr, which is the current node in the tree
Function output/parameters: none
Function output/returned: pointer to largest leaf node
Device input/file: none
Device output/monitor: none
Dependencies: findLargestLeafNode
*/
PasswordType *find_largest_leaf_node(PasswordType *wkgPtr) {
    // initialize variables
    PasswordType *currentNode = wkgPtr;
    PasswordType *largestLeaf = NULL;

    // check to see if current node is a leaf
    if (currentNode->leftChildPtr == NULL && currentNode->rightChildPtr == NULL) {
        // assign ptr for return
        largestLeaf = currentNode;
    }
    // otherwise
    else {
        // check to see if there is a right child
        if (currentNode->rightChildPtr != NULL) {
            // return: recursion with right child
            return find_largest_leaf_node(currentNode->rightChildPtr);
        }

        // otherwise, check to see if there is a left child node
        else {
            // return: recursion with left child
            return find_largest_leaf_node(currentNode->leftChildPtr);
        }
    }
    return largestLeaf;
}

/*
Name: findSmallestLeafNode
Process: searches the tree for the smallest leaf node, returns a pointer to node.
Function input/parameters: working pointer, current node in the tree
Function output/parameters: none
Function output/returned: pointer to smallest leaf node
Device input/file: none
Device output/monitor: none
Dependencies: findSmallestLeafNode
*/
PasswordType *find_smallest_leaf_node(PasswordType *wkgPtr) {
    // initialize variables
    PasswordType *currentNode = wkgPtr;
    PasswordType *smallestLeaf = NULL;

    // check if current node is leaf
    if (currentNode->leftChildPtr == NULL 
            && currentNode->rightChildPtr == NULL) {
        smallestLeaf = currentNode;
    }

    // otherwise
    else {
        // check to see if there is a left child (reversing above)
        if (currentNode->leftChildPtr != NULL) {
            return find_smallest_leaf_node(currentNode->leftChildPtr);
        }
        else {
            return find_smallest_leaf_node(currentNode->rightChildPtr);
        }
    }
    return smallestLeaf;
}

