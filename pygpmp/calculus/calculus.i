/* openGPMP Calculus Module */

%module calculus 
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%include "std_string.i"

%{
    #include "../../include/openGPMP/calculus/differential.hpp"
    using namespace gpmp;
%}

%include "../../include/openGPMP/calculus/differential.hpp"

