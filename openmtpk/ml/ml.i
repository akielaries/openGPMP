/* openMTPK Machine Learning Module */

%module ml
%include <std_vector.i>
%include <typemaps.i>
%include <stdint.i>

%{
    #include "../../include/ml/linreg.hpp"
    using namespace mtpk;
%}

%include "../../include/ml/linreg.hpp"

