/* SWIG Interface file */

/* %module = sepcifies a module to use, 
will include headers within */

%module number_theory
%{
    /* MODULE HEADER FILE */
    #include "../../include/number_theory/primes.hpp"
%}

%include "../../include/number_theory/primes.hpp"

