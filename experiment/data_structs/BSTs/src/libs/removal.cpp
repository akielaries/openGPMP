/*
 * function implementations of removing and clearing the tree and
 * its data
 */
#include "removal.h"
#include "constants.h"
#include "tree_init.h"
#include "tree_ops_helpers.h"
#include <stdlib.h>

/*
Name: removeFromMax
Process: recursively traverses for max node. When found, unlinks node from
tree and returns it. Function input/parameters: pointer to parent and child
nodes Function output/parameters: none Function output/returned: pointer to
unlinked node Device input/file: none Device output/monitor: none
Dependencies: removeFromMax
*/
PasswordType *remove_from_max(PasswordType *parentPtr,
                              PasswordType *childPtr) {
    // check to see if the child has a right child
    if (childPtr->rightChildPtr != NULL) {
        // call removeFromMax with the child as the parent parameter, and
        // the
        //  child's right child as the child parameter
        return remove_from_max(childPtr, childPtr->rightChildPtr);
    }
    // unlink right most node from the tree
    parentPtr->rightChildPtr = childPtr->leftChildPtr;
    // return pointer to unlinked node
    return childPtr;
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
PasswordType *remove_item_helper(PasswordType *wkgPtr,
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
                remove_item_helper(wkgPtr->leftChildPtr, toRemovePtr);
        }
        // otherwise, check to see if removal data is larger than the data
        // at the current node
        else if (toRemovePtr->rank > wkgPtr->rank) {
            // recurse to the right
            wkgPtr->rightChildPtr =
                remove_item_helper(wkgPtr->rightChildPtr, toRemovePtr);
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
                    temp = remove_from_max(
                        wkgPtr, wkgPtr->leftChildPtr->rightChildPtr);
                    // copy data from removeFromMax into current node
                    // function: setNodeDataFromData
                    // setNodeDataFromNode(wkgPtr,
                    // wkgPtr->leftChildPtr->rightChildPtr);
                    set_node_data_from_node(wkgPtr, temp);
                    // free the node that was unlinked (tempPtr)
                    free(temp);
                }
                // otherwise, current node's left child does not have a
                // right child
                else {
                    // copy left child into current node
                    set_node_data_from_node(wkgPtr, wkgPtr->leftChildPtr);
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
            rebalance_tree(wkgPtr);
        }
    }
    return wkgPtr;
}

/*
Name: removeLeafNode
Process: removes a leaf node from the tree, frees the removed leaf node
from memory Function input/parameters: wkgPtr (current node in tree),
                           searchRank (int, rank of the node that should be
removed) Function output/parameters: none Function output/returned: wkgPtr
for recursion Device input/file: none Device output/monitor: none
Dependencies: free
*/
PasswordType *remove_leaf_node(PasswordType *wkgPtr, int searchRank) {
    // initialize variables
    PasswordType *currentNode = wkgPtr;

    // check if we are pointing to null
    if (currentNode == NULL)
        return currentNode;

    // check if search rank is less than current
    if (searchRank < currentNode->rank)
        currentNode->leftChildPtr =
            remove_leaf_node(currentNode->leftChildPtr, searchRank);

    // otherwise check search rank less than current rank
    else if (searchRank > currentNode->rank)
        currentNode->rightChildPtr =
            remove_leaf_node(currentNode->rightChildPtr, searchRank);

    // otherwise
    else {
        // check for node with one or zero children then free
        // // for left
        if (currentNode->leftChildPtr == NULL) {
            PasswordType *tempPtr = currentNode->rightChildPtr;
            free(currentNode);
            return tempPtr;
        }

        // for right
        else if (currentNode->rightChildPtr == NULL) {
            PasswordType *tempPtr = currentNode->leftChildPtr;
            free(currentNode);
            return tempPtr;
        }
        // get inorder next
        PasswordType *tempPtr =
            find_smallest_leaf_node(currentNode->rightChildPtr);
        currentNode->rank = tempPtr->rank;
        currentNode->rightChildPtr =
            remove_leaf_node(currentNode->rightChildPtr, tempPtr->rank);
    }
    return currentNode;
}

/*
Name: clearBST
Process: recursively clears the tree.
Function input/parameters: working pointer for recursion
Function output/parameters: none
Function output/returned: NULL
Device input/file: none
Device output/monitor: none
Dependencies: free, clearBST (recursive)
deletes using post order LRN (LEFT, RIGHT, NODE)
*/
PasswordType *clear_BST(PasswordType *wkgPtr) {
    // recursive call to left and right
    if (wkgPtr != NULL) {
        // recursively call clear left side
        clear_BST(wkgPtr->leftChildPtr);
        // recursively call clear right side
        clear_BST(wkgPtr->rightChildPtr);
        // free wkgPtr
        free(wkgPtr);
    }
    return NULL;
}
