/* SWIG Interface file */

/* %module = sepcifies a module to use, 
will include headers within */
%module test_module
%{
    /* MODULE HEADER FILE */
    #include "include/test_module.hpp"
    extern double var_foo;
%}

/* EXPLICITLY list functions and variables to include */ 
long long int fact(long long int n1);
int my_mod(int m, int n);
extern double var_foo;

