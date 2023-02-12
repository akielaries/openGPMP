/*
 *  constants used in program
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

// static const int MAX_CAPACITY = 150001;
// const int MAX_NODES = 150000;

// data structure, BST node
typedef struct PasswordTypeStruct {
    int rank;
    unsigned long long int password;
    struct PasswordTypeStruct *leftChildPtr;
    struct PasswordTypeStruct *rightChildPtr;
} PasswordType;

#endif
