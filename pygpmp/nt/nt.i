/* Defining number theory module methods to be wrapped using SWIG
*/

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%module nt

%{
    #include "../../include/arithmetic.hpp"
    #include "../../include/nt/prime_test.hpp"
    #include "../../include/nt/prime_gen.hpp"
    #include "../../include/nt/logarithms.hpp"
    #include "../../include/nt/factorization.hpp"
    #include "../../include/nt/rc4.hpp"
    #include "../../include/nt/cipher.hpp"
    using namespace gpmp;
%}

%include "../../include/arithmetic.hpp"
%include "../../include/nt/prime_test.hpp"
%include "../../include/nt/prime_gen.hpp"
%include "../../include/nt/logarithms.hpp"
%include "../../include/nt/factorization.hpp"
%include "../../include/nt/rc4.hpp"
%include "../../include/nt/cipher.hpp"

