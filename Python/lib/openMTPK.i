/* CORE openMTPK PYTHON API SWIG INTERFACE FILE */

/* FIGURE OUT CLASS TEMPLATES AND DEFININD SPECIFIC TYPES
 * FOR ARITHMETIC CLASS */
%module openMTPK
%include "std_string.i"
%{
    /*#include "../../include/arithmetic/arith.hpp"
    */
    #include "../../include/number_theory/primes.hpp"
    #include "../../include/number_theory/rc4.hpp"
    #include "../../include/number_theory/cipher.hpp"
%}

/*
%include "../../include/arithmetic/arith.hpp"
*/
%include "../../include/number_theory/primes.hpp"
%include "../../include/number_theory/rc4.hpp"
%include "../../include/number_theory/cipher.hpp"

