/* openGPMP Calculus Module */

%module calculus 
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%include "std_string.i"

%{
    #include "../../include/calculus/differential.hpp"
    using namespace gpmp;
%}

%include "../../include/calculus/differential.hpp"

