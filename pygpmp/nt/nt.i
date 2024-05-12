/* Defining number theory module methods to be wrapped using SWIG
*/

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%module nt

%{
    #include "../../include/openGPMP/arithmetic.hpp"
    #include "../../include/openGPMP/nt/prime_test.hpp"
    #include "../../include/openGPMP/nt/prime_gen.hpp"
    #include "../../include/openGPMP/nt/logarithms.hpp"
    #include "../../include/openGPMP/nt/factorization.hpp"
    #include "../../include/openGPMP/nt/rc4.hpp"
    #include "../../include/openGPMP/nt/cipher.hpp"
    using namespace gpmp;
%}

%include "../../include/openGPMP/arithmetic.hpp"
%include "../../include/openGPMP/nt/prime_test.hpp"
%include "../../include/openGPMP/nt/prime_gen.hpp"
%include "../../include/openGPMP/nt/logarithms.hpp"
%include "../../include/openGPMP/nt/factorization.hpp"
%include "../../include/openGPMP/nt/rc4.hpp"
%include "../../include/openGPMP/nt/cipher.hpp"

