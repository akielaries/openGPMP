/*
 * function declarations of tree operation helpers
 */

#ifndef TREEOPSHELPERS_H
#define TREEOPSHELPERS_H

int get_balance_factor(PasswordType *localPtr);
PasswordType *rebalance_tree(PasswordType *localPtr);
int get_max(int valOne, int valTwo);
int find_subtree_height(PasswordType *localPtr);
PasswordType *find_largest_leaf_node(PasswordType *wkgPtr);
PasswordType *find_smallest_leaf_node(PasswordType *wkgPtr);

#endif
