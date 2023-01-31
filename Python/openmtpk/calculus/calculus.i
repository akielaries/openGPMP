/* openMTPK Calculus Module */

%module calculus 
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%include "std_string.i"

%{
    #include "../../../include/calculus/deriv.hpp"
    using namespace mtpk;
%}

%include "../../../include/calculus/deriv.hpp"

