/* SWIG Interface file */

/* %module = sepcifies a module to use, 
will include headers within */
%module test_module
%{
    /* MODULE HEADER FILE */
    #include "test_module.hpp"
%}

/* EXPLICITLY list functions and variables to include */
long long int fact(long long int n1);
int my_mod(int m, int n);

