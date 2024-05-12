/* openGPMP Machine Learning Module */

%module ml
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%{
    #include "../../include/openGPMP/ml/linreg.hpp"
    using namespace gpmp;
%}

%include "../../include/openGPMP/ml/linreg.hpp"

