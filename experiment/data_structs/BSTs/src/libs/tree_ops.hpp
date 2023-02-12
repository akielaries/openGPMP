/*
 * function definitions for tree operations
 */

#ifndef TREEOPS_H
#define TREEOPS_H

PasswordType *insert_AVL_data(PasswordType *wkgPtr,
                              PasswordType *inNodePtr);
PasswordType *search(PasswordType *wkgPtr, PasswordType *toRemovePtr);
PasswordType *remove_item(PasswordType *rootPtr,
                          PasswordType *toRemovePtr);
void          display_in_order(PasswordType *wkgPtr, FILE *outputFile);
PasswordType *left_rotation(PasswordType *localPtr);
PasswordType *right_rotation(PasswordType *localPtr);

#endif
