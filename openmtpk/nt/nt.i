/* 
*/

%include "std_string.i"
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%module nt

%{
    #include "../../include/arithmetic.hpp"
    #include "../../include/nt/primes.hpp"
    #include "../../include/nt/logarithms.hpp"
    #include "../../include/nt/factorization.hpp"
    #include "../../include/nt/rc4.hpp"
    #include "../../include/nt/cipher.hpp"
    using namespace mtpk;
%}

%include "../../include/arithmetic.hpp"
%include "../../include/nt/primes.hpp"
%include "../../include/nt/logarithms.hpp"
%include "../../include/nt/factorization.hpp"
%include "../../include/nt/rc4.hpp"
%include "../../include/nt/cipher.hpp"

