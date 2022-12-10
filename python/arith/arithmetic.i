/* SWIG Interface file */

/* %module = sepcifies a module to use, 
will include headers within */

%module arithmetic
%{
    /* MODULE HEADER FILE */
    #include "../../include/arithmetic/arith.hpp"
%}

/* EXPLICITLY list functions and variables to include */
%include "../../include/arithmetic/arith.hpp"

