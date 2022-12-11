/* CORE RM-pkg PYTHON API SWIG INTERFACE FILE */

%module RM_pkg
%include "std_string.i"
%{
    #include "../../include/arithmetic/arith.hpp"
    #include "../../include/number_theory/primes.hpp"
    #include "../../include/number_theory/rc4.hpp"
    #include "../../include/number_theory/cipher.hpp"
%}
%include stl.i
%include <stl.i>


%include "../../include/arithmetic/arith.hpp"
%include "../../include/number_theory/primes.hpp"
%include "../../include/number_theory/rc4.hpp"
%include "../../include/number_theory/cipher.hpp"

