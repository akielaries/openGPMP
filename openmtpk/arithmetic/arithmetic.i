/* openMTPK Arithmetic Module */

%module arithmetic
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>
%include "std_string.i"

%{
    #include "../../include/arithmetic/arith_ops.hpp"
    using namespace mtpk;
%}

%include "../../include/arithmetic/arith_ops.hpp"

