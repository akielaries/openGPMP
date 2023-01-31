/*
 * function definitions for removing items from
 * our tree
 */

#ifndef REMOVAL_H
#define REMOVAL_H

PasswordType *remove_from_max(PasswordType *parentPtr, PasswordType *childPtr);
PasswordType *remove_item_helper(PasswordType *wkgPtr, PasswordType *toRemovePtr);
PasswordType *clear_tree(PasswordType *wkgPtr);

#endif

