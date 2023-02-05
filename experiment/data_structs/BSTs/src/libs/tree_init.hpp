/*
 * function definitions for inserting data into the tree
 */

#ifndef TREEINIT_H
#define TREEINIT_H

PasswordType *import_data(int size);
PasswordType *init_node_from_data(int rankInput,
                                  unsigned long long int passInput);
void set_node_data_from_node(PasswordType *destNode,
                             PasswordType *srcNode);

#endif
