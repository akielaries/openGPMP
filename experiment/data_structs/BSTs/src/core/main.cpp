// header files
#include "../libs/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../libs/export_data.h"
#include "../libs/removal.h"
#include "../libs/tree_init.h"
#include "../libs/tree_ops.h"
#include "../libs/tree_ops_helpers.h"

// DEFINES
const int MAX_NODES = 150000;

// main driver
int main() {
    // initialize variables
    int           size;
    PasswordType *rootPtr = NULL;
    PasswordType  tempNode;
    FILE *        outputFilePtr;

    // prompt for size
    printf("Enter the number of values to be sorted: ");
    scanf("%d", &size);

    // check for acceptable size input
    if (size >= 1 && size <= MAX_NODES) {
        // build the AVL tree
        rootPtr = import_data(size);

        // check for rootPtr not null
        if (rootPtr != NULL) {
            printf("\nStarting rootPtr: %d\n", rootPtr->rank);

            // remove some nodes
            tempNode.rank = 79681;

            printf("\nRemoving %d\n", tempNode.rank);

            rootPtr = remove_item(rootPtr, &tempNode);

            printf("\nRank at root node after removal is %d\n",
                   rootPtr->rank);

            // remove some nodes
            tempNode.rank = 45267;

            printf("\nRemoving %d\n", tempNode.rank);

            rootPtr = remove_item(rootPtr, &tempNode);

            printf("\nRank at root node after removal is %d\n",
                   rootPtr->rank);

            // remove some nodes
            tempNode.rank = 157255;

            printf("\nRemoving %d\n", tempNode.rank);

            rootPtr = remove_item(rootPtr, &tempNode);

            printf("\nRank at root node after removal is %d\n",
                   rootPtr->rank);

            int heightDiff = find_subtree_height(rootPtr->leftChildPtr) -
                             find_subtree_height(rootPtr->rightChildPtr);

            printf("\nHeight difference of root node subtrees after "
                   "removals: %d\n",
                   heightDiff);

            // open an output file to write to
            outputFilePtr = fopen("../reports/AVL_Tree_1.csv", "w+");

            // write tree to file
            display_in_order(rootPtr, outputFilePtr);

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
